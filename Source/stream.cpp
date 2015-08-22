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
    log("stream constructor");
    qRegisterMetaType<QHostAddress>("QHostAddress");
    qRegisterMetaType<BufferList>("BufferList");

    worker = new Worker;

    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &stream::start_streaming , worker, &Worker::start_stream );
    connect(worker,SIGNAL(done_streaming()),this,SLOT(done_with_worker()));
    connect(worker,SIGNAL(find_bitrate(QString)),this,SLOT(find_bitrate(QString)),Qt::DirectConnection);
    connect(worker,SIGNAL(work_status(QString)),this,SLOT(worker_status(QString)));
    worker->moveToThread(&workerThread);
    workerThread.start(QThread::TimeCriticalPriority);

    log("finished log constructor");
}

stream::~stream()
{
    log("stopping stream");
    if(worker!=NULL)
    {
        worker->quit = true;
        workerThread.quit();
        workerThread.wait();
    }
    log("Stream destructor finished");
}

void stream::stream_start( QHostAddress stream_addr, quint16 stream_port, QString source_filename )
{
    log("Start Streaming");
    emit start_streaming( stream_addr , stream_port , source_filename);
}

void stream::done_with_worker()
{
    emit done_with_stream();
    log("done with stream signal sent");
}

void stream::find_bitrate(QString filename)
{
    qDebug("2 find bitrate ");
    log("set bitrate to 4000000");
    set_bitrate(4000000);
    //qDebug("4 get bitrate leaves stream");
    //emit get_bitrate(filename);    // blocks until automation slot returns after setting bitrate

    qDebug("returning to worker stream function");

}

void stream::worker_status(QString string)
{
    emit status(string);
}

void stream::set_bitrate(int bitrate)
{
    qDebug()<< "Set worker bitrate to " << bitrate;
    worker->set_packet_period(bitrate);
}

void stream::log(QString logdata)
{
    emit status( (QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss:zzz ") + logdata + "\n") ) ;
}

Worker::Worker()
{
    packet_size = 188;
    pkts_per_dgm = 7;  // must be between 1 and 7 packets per datagram
    quit = false;
}

Worker::~Worker()
{
    log("Closing Stream Socket");
    log("worker destructor finished");
}

void Worker::read_datagram()
{
    datagram.clear();
    for(int i=1; i<=pkts_per_dgm;i++)
    {
        bytes_read = readfile.read(packet,packet_size);
        //qDebug()<< "bytes read "<< bytes_read << readfile.pos();
        if(bytes_read<=0)
        {
            log("reached end of file");
            return;
        }
        datagram.append( QByteArray( (char*) packet ,packet_size) );
    }
}

void Worker::set_packet_period(int bitrate)
{
    if(bitrate!=0)
    {
        timer_period = 8*packet_size*pkts_per_dgm; // 8 bits per byte, ms between packets.
        timer_period = timer_period*1000000000;
        timer_period = timer_period/(bitrate);
        one_third_of_timer_period = timer_period/4;
        sleep_time = timer_period/3000;
        //qDebug() << timer_period;
    }
    else
        timer_period = 0;
}

bool Worker::stream_init(QString source_filename)
{
    readfile.setFileName(source_filename);
    qDebug("first step, find bitrate");
    emit find_bitrate(source_filename);  // blocks until stream class connection returns
    qDebug("Last step, bitrate found");

    while(!readfile.open(QIODevice::ReadOnly))
    {
        QThread::msleep(100);
    }
    readfile.close();
    QThread::sleep(5);
    if( readfile.open(QFile::ReadOnly) )
    {
        readfile.seek(0);
        return true;
    }
    else
    {
        log("failed to open file to stream");
        return false;
    }
}

void Worker::start_stream(QHostAddress stream_addr, quint16 stream_port, QString source_filename)
{
        if( stream_init(source_filename) )  // get bitrate from stream and block until file is ready to stream.

        {
            log("initialised stream, opening socket");
            if( timer_period == 0)
            {
                log("stream failed");
                return;
            }
            udp_streaming_socket = new QUdpSocket(this);
            qDebug()<< "Streaming to " << stream_addr;
            read_datagram();
            elapsed_timer.start();
            log("starting stream (worker)");
           // qDebug()<< "datagram " << !datagram.isEmpty() << !quit;
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
                //qDebug()<< socket_state;
                if(socket_state!=(188*pkts_per_dgm))
                {
                    qDebug("error, trying to resend");
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
            log("finished stream");
        }
}

void Worker::log(QString logdata)
{
    emit work_status( (QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss:zzz ") + logdata + "\n") ) ;
}
