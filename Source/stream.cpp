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
stream::stream(QHostAddress stream_addr, qint16 stream_port, int kBitRate, QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType<QHostAddress>("QHostAddress");
    qRegisterMetaType<BufferList>("BufferList");

    KbitRate = kBitRate;
    ip_stream_address = stream_addr;
    ip_stream_port = stream_port;

    timer_freq = 8*188*8; // 8 bits per byte, ms between packets.
    timer_freq = timer_freq*1000000;
    timer_freq = timer_freq/(kBitRate);

    worker = new Worker;

    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &stream::start_stream , worker, &Worker::send_datagrams );
    connect(worker,SIGNAL(done_streaming()),this,SLOT(done_with_worker()));
    worker->moveToThread(&workerThread);
    workerThread.start(QThread::TimeCriticalPriority);

 // Prepare constants to build datagram.
    pkts_PerDgram = 8;
    packet_size   = 188;
    dgram_size    = 188*8;
    packet.fill('1',packet_size);
    datagram.clear();
    packet_index=0;
}

stream::~stream()
{
    qDebug("stopping stream");
    worker->loop=false;
    workerThread.quit();
    workerThread.wait();
    qDebug("Stream destructor finished");
}

void stream::make_udp_packet(QByteArray packet)
{
    if (packet_index < pkts_PerDgram)
    {
        datagram.append(packet);
        packet_index++;
        if(packet_index == pkts_PerDgram)
        {
            datagram_buffer.append( datagram );
            datagram.clear();
            packet_index=0;
        }
    }
}

void stream::send_udp_packet()
{
    start_stream( ip_stream_address, ip_stream_port , timer_freq ,datagram_buffer);
}

void stream::done_with_worker()
{

    emit done_with_stream();
    qDebug("done with stream signal sent");
}

Worker::Worker()
{
    loop=true;
    qDebug("Constructor");
}

Worker::~Worker()
{
    qDebug("Closing Socket");
    udp_streaming_socket->close();
    qDebug("worker destructor finished");
}
void Worker::send_datagrams(QHostAddress stream_addr, qint16 stream_port, qint64 timer_freq , BufferList datagram_buffer)
{
    udp_streaming_socket = new QUdpSocket(this);    // switch to QUdpSocket and remove winsock when Qt is patched
    datagram_index = 0;
    elapsed_timer.start();
    while(loop)
    {
        while(elapsed_timer.nsecsElapsed() <= timer_freq)
        {
            // spin until time to send next packet
        }
        if(datagram_buffer.size()<=datagram_index)
        {
            emit done_streaming();
            save_file(datagram_buffer);
            qDebug("done with stream");
            loop=false;
            break;
        }
        if(datagram_buffer.size()>datagram_index)
        {
            socket_state = udp_streaming_socket->writeDatagram(datagram_buffer.at(datagram_index).data(), datagram_buffer.at(datagram_index).size() ,stream_addr , stream_port);
            udp_streaming_socket->waitForBytesWritten();
            elapsed_timer.restart();     // start elapsed timer
            if(socket_state<=0)
            {
                qDebug()<< "Socket error "<< udp_streaming_socket->error();
            }
            datagram_index++;
        }
    }
    udp_streaming_socket->close();
}

void Worker::save_file(BufferList datagram_buffer)
{
    QFile file("c:\\3abn\\qudp_test.ts");
    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream out(&file);
        for(int i=0; i<datagram_buffer.size();i++)
            out.writeRawData(datagram_buffer.at(i).data(),datagram_buffer.at(i).size());
        file.close();
    }
}
