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
    worker->moveToThread(&workerThread);
    workerThread.start(QThread::TimeCriticalPriority);
    qDebug("Finished stream constructor");

}

stream::~stream()
{
    qDebug("stopping stream");
    //worker->loop=false;
    workerThread.quit();
    workerThread.wait();
    qDebug("Stream destructor finished");
}

void stream::start()
{
    qDebug()<< "start called";
    emit start_streaming();
}

void stream::done_with_worker()
{

    emit done_with_stream();
    qDebug("done with stream signal sent");
}

Worker::Worker()
{
    //loop=true;
    qDebug("Constructor");
}

Worker::~Worker()
{
    qDebug("Closing Socket");
    //udp_streaming_socket->close();
    qDebug("worker destructor finished");
}
void Worker::start_stream()
{
    qDebug("streaming");
    QFile readfile;
    readfile.setFileName("C:/Users/Zach/Development/build-ffmpeg-Desktop_Qt_5_3_MinGW_32bit-Debug/encode_test.ts");
    QFile savefile;
    savefile.setFileName("C:/Users/Zach/Development/build-ffmpeg-Desktop_Qt_5_3_MinGW_32bit-Debug/out_test.ts");
    char packet [188];
    int bytes_read=0;
    QByteArray packet_buffer;
    int socket_state;
    QUdpSocket *udp_streaming_socket;
    QHostAddress stream_addr;
    stream_addr.setAddress("239.0.0.230");
    quint16 stream_port = 1234;
    QElapsedTimer elapsed_timer;
    qint64 timer_freq;
    timer_freq = 8*188*8; // 8 bits per byte, ms between packets.
    timer_freq = timer_freq*1000000;
    timer_freq = timer_freq/(4000);

    quint64 time1,time2,bitrate;

    udp_streaming_socket = new QUdpSocket(this);

    if( readfile.open(QFile::ReadOnly) )
    {
        if( savefile.open(QFile::WriteOnly) )
        {

            bytes_read = readfile.read(packet,188);
            elapsed_timer.start();
            while( bytes_read > 0 )
            {
                packet_buffer = QByteArray( (char*) packet ,188);
                while(elapsed_timer.nsecsElapsed() <= timer_freq)
                {
                    QThread::usleep(1);
                    // spin until time to send next packet
                }
               // time1 = elapsed_timer.nsecsElapsed();
                elapsed_timer.restart();
                socket_state = udp_streaming_socket->writeDatagram( packet_buffer.data() , packet_buffer.size() ,stream_addr , stream_port);
                udp_streaming_socket->waitForBytesWritten();
                //bitrate = 12032000000/time1;
               // qDebug()<<bitrate;
                if(socket_state<=0)
                {
                    qDebug()<< "Socket error "<< udp_streaming_socket->error();
                }
                savefile.write( packet_buffer );

                bytes_read = readfile.read(packet,188);
            }
            savefile.close();
            qDebug("Done writing file");
        }
        readfile.close();
    }

    udp_streaming_socket->close();
    qDebug("done with function");
}
