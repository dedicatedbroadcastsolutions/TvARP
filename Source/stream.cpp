/*
***************************************************************************
*
* Author: Zach Swena
*
* Copyright (C) 2010, 2011, 2014 Zach Swena All Rights Reserved
*
* zcybercomputing@gmail.com
*
***************************************************************************
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation version 2 of the License.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
***************************************************************************
*
* This version of GPL is at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt
*
***************************************************************************
*/
#include "stream.h"
#include "windows.h"
/// ========================================================================================================
stream::stream(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType<QHostAddress>("QHostAddress");
    qRegisterMetaType<BufferList>("BufferList");

    worker = new Worker;

    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &stream::start_streaming , worker, &Worker::start_stream );
    connect(worker,SIGNAL(done_streaming()),this,SLOT(done_with_worker()));
    connect(worker,SIGNAL(ts_info(QString)),this,SLOT(ts_info(QString)),Qt::DirectConnection);
    connect(worker,SIGNAL(work_status(QString)),this,SLOT(worker_status(QString)));
    worker->moveToThread(&workerThread);
    workerThread.start(QThread::TimeCriticalPriority);
}

stream::~stream()
{
    emit status(QDateTime::currentDateTime().toString("yyyy:mm:dd:ss")+ "  " +"stopping stream\n");
    worker->quit = true;
    workerThread.quit();
    workerThread.wait();
    emit status(QDateTime::currentDateTime().toString("yyyy:mm:dd:ss")+ "  " +"Stream destructor finished\n");
}

void stream::stream_start( QHostAddress stream_addr, quint16 stream_port, QString source_filename )
{
    emit status(QDateTime::currentDateTime().toString("yyyy:mm:dd:ss")+ "  " +"Starting worker thread \n");
    emit start_streaming( stream_addr , stream_port , source_filename);
}

void stream::done_with_worker()
{
    emit done_with_stream();
    emit status(QDateTime::currentDateTime().toString("yyyy:mm:dd:ss")+ "  " +"done with stream signal sent\n");
}

void stream::ts_info(QString filename)
{
    emit get_ts_info(filename);    // blocks until automation slot returns after setting bitrate
}

void stream::worker_status(QString string)
{
    emit status(string);
}

void stream::set_kbitrate(int kbitrate)
{
    worker->set_packet_period(kbitrate);
}

Worker::Worker()
{
    packet_size = 188;
    pkts_per_dgm = 7;  // must be between 1 and 7 packets per datagram
    quit = false;
}

Worker::~Worker()
{
    emit work_status(QDateTime::currentDateTime().toString("yyyy:mm:dd:ss")+ "  " +"Closing Stream Socket\n");
    emit work_status(QDateTime::currentDateTime().toString("yyyy:mm:dd:ss")+ "  " +"worker destructor finished\n");
}

void Worker::read_datagram()
{
    datagram.clear();
    for(int i=1; i<=pkts_per_dgm;i++)
    {
        bytes_read = readfile.read(packet,packet_size);
        if(bytes_read<=0)
            return;
        datagram.append( QByteArray( (char*) packet ,packet_size) );
    }
}

void Worker::set_packet_period(int kbitrate)
{
    timer_period = 8*packet_size*pkts_per_dgm; // 8 bits per byte, ms between packets.
    timer_period = timer_period*1000000;
    timer_period = timer_period/(kbitrate);
    one_third_of_timer_period = timer_period/4;
    sleep_time = timer_period/3000;
}

bool Worker::stream_init(QString source_filename)
{
    readfile.setFileName(source_filename);
    emit ts_info(source_filename);  // blocks until stream class connection returns
    if( readfile.open(QFile::ReadOnly) )
    {
        return true;
    }
    else
        return false;
}

void Worker::start_stream(QHostAddress stream_addr, quint16 stream_port, QString source_filename)
{
        if( stream_init(source_filename) )  // get bitrate from stream and block until file is ready to stream.

        {
            udp_streaming_socket = new QUdpSocket(this);
            read_datagram();
            elapsed_timer.start();
            emit work_status(QDateTime::currentDateTime().toString("yyyy:mm:dd:ss")+ "  " +"starting stream\n");
            while( !datagram.isEmpty() && !quit)
            {
                while(elapsed_timer.nsecsElapsed() <= timer_period)
                {
                    if( elapsed_timer.nsecsElapsed() <= one_third_of_timer_period )
                        QThread::usleep( sleep_time );
                }
                socket_state = udp_streaming_socket->writeDatagram( datagram.data() , datagram.size() ,stream_addr , stream_port);
                udp_streaming_socket->waitForBytesWritten();

                elapsed_timer.restart();

                if(socket_state!=(188*pkts_per_dgm))
                {
                    while ( socket_state == -1 )
                    {
                        socket_state = udp_streaming_socket->writeDatagram( datagram.data() , datagram.size() ,stream_addr , stream_port);
                        udp_streaming_socket->waitForBytesWritten();
                        QThread::usleep(1);
                    }
                }
                emit datagram_sent(datagram);
                read_datagram();
            }
            readfile.close();
            udp_streaming_socket->close();
        }
        emit work_status(QDateTime::currentDateTime().toString("yyyy:mm:dd:ss")+ "  " +"finished stream\n");
}
