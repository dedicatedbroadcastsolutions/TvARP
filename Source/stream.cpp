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
#include <QReadWriteLock>
#include "stream.h"
#include "windows.h"
/// ========================================================================================================
stream::stream(QObject *parent) :
    QObject(parent)
{
    log("stream constructor");
    qRegisterMetaType<QHostAddress>("QHostAddress");
    qRegisterMetaType<BufferList>("BufferList");
    //qDebug()<< "Thread ID "<< QThread::currentThreadId();

    worker = new Worker(1234);
    worker->moveToThread(&workerThread);
    workerThread.start(QThread::TimeCriticalPriority);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater,Qt::QueuedConnection);
    connect(this, &stream::start_streaming , worker, &Worker::start_stream,Qt::QueuedConnection );
    connect(worker,SIGNAL(done_streaming()),this,SLOT(done_with_worker()),Qt::QueuedConnection);
    connect(worker,SIGNAL(work_status(QString)),this,SLOT(worker_status(QString)),Qt::QueuedConnection);
    connect(this,SIGNAL(start_stream_loop()),worker,SLOT(start_loop()),Qt::QueuedConnection);
    connect(worker,SIGNAL(busy(int,QString)),this,SLOT(process_busy(int,QString)),Qt::QueuedConnection);
    connect(worker,SIGNAL(streaming(int,QString)),this,SLOT(cancel_cue(int,QString)),Qt::QueuedConnection);
    connect(this,SIGNAL(cue_streaming(int,QString)),worker,SLOT(cue_stream(int,QString)),Qt::QueuedConnection);
    connect(worker,SIGNAL(finished_file(int)),this,SLOT(finished_stream(int)));
    connect(worker,SIGNAL(failed_to_cue_file(QString)),this,SLOT(failed_to_cue(QString)));
    emit start_stream_loop();
    log("finished log constructor");
}
// need to fix cue command blocking stream
// need to fix occasional deck change on cue command.
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

void stream::failed_to_cue(QString filename)
{
    emit failed_to_open(filename);
}

void stream::finished_stream(int port)
{
    emit done_with_file( port);
}

void stream::cancel_cue(int ip_port, QString filename)
{
    switch ( ip_port )
    {
        case 1:
            ip1_cue.clear();
            break;
        case 2:
            ip2_cue.clear();
            break;
        case 3:
            ip3_cue.clear();
            break;
        case 4:
            ip4_cue.clear();
            break;
    }
    emit stream_started(ip_port,filename);
}

void stream::process_busy( int ip_port,  QString source_filename )
{
    qDebug("busy");
    switch ( ip_port )
    {
        case 1:
            if(ip1_cue==source_filename||ip1_cue.isEmpty())
            {
                QTimer::singleShot(5000,this,SLOT(cue_file()));
                ip1_cue = source_filename;
            }
            break;
        case 2:
            if(ip2_cue==source_filename||ip2_cue.isEmpty())
            {
                QTimer::singleShot(5000,this,SLOT(cue_file()));
                ip2_cue = source_filename;
            }
            break;
        case 3:
            if(ip3_cue==source_filename||ip3_cue.isEmpty())
            {
                QTimer::singleShot(5000,this,SLOT(cue_file()));
                ip3_cue = source_filename;
            }
            break;
        case 4:
            if(ip4_cue==source_filename||ip4_cue.isEmpty())
            {
                QTimer::singleShot(5000,this,SLOT(cue_file()));
                ip4_cue = source_filename;
            }
            break;
    }

}
void stream::cue_file()
{
    qDebug("trying again to cue file");
    if(!ip1_cue.isEmpty())
        stream_cue(1,ip1_cue);
    if(!ip2_cue.isEmpty())
        stream_cue(2,ip2_cue);
    if(!ip3_cue.isEmpty())
        stream_cue(3,ip3_cue);
    if(!ip4_cue.isEmpty())
        stream_cue(4,ip4_cue);
}

void stream::stream_start(int ip_port )
{
    qDebug("stream_start");
    log("Start Streaming");
    emit start_streaming( ip_port);
}

void stream::stream_cue(int ip_port, QString source_filename)
{
    qDebug() << "Cue " << source_filename << "on port " << ip_port;
    log("cued file" + source_filename + " on port " + QString::number(ip_port));
    emit cue_streaming(ip_port,source_filename);
}

void stream::done_with_worker()
{
    emit done_with_stream();
    log("done with stream signal sent");
}

void stream::worker_status(QString string)
{
    emit status(string);
}

void stream::log(QString logdata)
{
    emit status( (QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss:zzz ") + logdata + "\n") ) ;
}

Worker::Worker(quint16 port)
{

    packet_size = 188;
    pkts_per_dgm = 7;  // must be between 1 and 7 packets per datagram
    quit = false;
}

Worker::~Worker()
{
    log("Closing Stream Socket");
    log("worker destructor finished");
    udp_streaming_socket->close();
}

void Worker::start_loop()
{
    int bind_state;
    udp_streaming_socket = new QUdpSocket(this);
    bind_state = udp_streaming_socket->bind(QHostAddress("192.168.0.166"),1234,QAbstractSocket::DontShareAddress);

    if(bind_state != true)
    {
        qDebug("failed to bind");
        log("Failed to bind, change IP address to 192.168.0.166");
    }
    //qDebug()<< "Loop Thread ID "<< QThread::currentThreadId();
    QHostAddress ip1_address,ip2_address,ip3_address,ip4_address;
    quint16 ip1_port,ip2_port,ip3_port,ip4_port;
    ip1_port = 1234;
    ip2_port = 1234;
    ip3_port = 1234;
    ip4_port = 1234;

    set_packet_period(3000000);

    ip1_address.setAddress( "239.0.0.220");
    ip2_address.setAddress("239.0.0.225");
    ip3_address.setAddress("239.0.0.230");
    ip4_address.setAddress("239.0.0.230");

    ip1 = false;
    ip2 = false;
    ip3 = false;
    ip4 = false;

    ip1a = false;
    ip2a = false;
    ip3a = false;
    ip4a = false;
    cue1a = false;  cue1b = false;
    cue2a = false;  cue2b = false;
    cue3a = false;  cue3b = false;
    cue4a = false;  cue4b = false;
    eas = false;
    if(bind_state==true)
        log("Ready to Stream");
    elapsed_timer.start();
    while(!quit)
    {

        while(elapsed_timer.nsecsElapsed() <= timer_period)
        {
            if( elapsed_timer.nsecsElapsed() <= one_third_of_timer_period )
                QCoreApplication::processEvents(QEventLoop::AllEvents,1);
            if( elapsed_timer.nsecsElapsed() <= one_third_of_timer_period )
                QThread::usleep( sleep_time );
        }
        if(ip1)
        {
            if(!ip1a&&cue1a&&!cue1b)
                ip1a = true;
            if(ip1a && cue1a)
            {   // Deck A
                datagram_1a = read_datagram(readfile_1a);
                if(!datagram_1a.isEmpty())
                {
                    udp_streaming_socket->writeDatagram( datagram_1a.data() , datagram_1a.size() ,ip1_address , ip1_port);
                    udp_streaming_socket->waitForBytesWritten();
                }
                else
                {
                    // send signal to trigger deck b after delay
                    qDebug("closing file on 1a");
                    emit finished_file(1);
                    readfile_1a.close();
                    ip1a=false;
                    cue1a = false;
                }
            }
            if(!ip1a && cue1b)
            {   // Deck B
                datagram_1b = read_datagram(readfile_1b);
                if(!datagram_1b.isEmpty())
                {
                    udp_streaming_socket->writeDatagram( datagram_1b.data() , datagram_1b.size() ,ip1_address , ip1_port);
                    udp_streaming_socket->waitForBytesWritten();
                }
                else
                {
                    // send signal to trigger deck a after delay
                    qDebug("closing file on 1b");
                    emit finished_file(1);
                    readfile_1b.close();
                    ip1a=true;
                    cue1b = false;
                }
            }
            if(!cue1a&&!cue1b)
                ip1 = false;
        }
        if(ip2)
        {
            if(!ip2a&&cue2a&&!cue2b)
                ip2a = true;
            if(ip2a && cue2a)
            {
                    datagram_2a = read_datagram(readfile_2a);
                    if(!datagram_2a.isEmpty())
                    {
                        udp_streaming_socket->writeDatagram( datagram_2a.data() , datagram_2a.size() ,ip2_address , ip2_port);
                        udp_streaming_socket->waitForBytesWritten();
                    }
                    else
                    {
                        qDebug("closing file on 2a");
                        emit finished_file(2);
                        readfile_2a.close();
                        ip2a=false;
                        cue2a = false;
                    }

            }
            if(!ip2a && cue2a)
            {
                    datagram_2b = read_datagram(readfile_2b);
                    if(!datagram_2b.isEmpty())
                    {
                        udp_streaming_socket->writeDatagram( datagram_2b.data() , datagram_2b.size() ,ip2_address , ip2_port);
                        udp_streaming_socket->waitForBytesWritten();
                    }
                    else
                    {
                        qDebug("closing file on 2b");
                        emit finished_file(2);
                        readfile_2b.close();
                        ip2a=true;
                        cue2a = false;
                    }
            }
            if(!cue2a&&!cue2b)
                ip2 = false;
        }
        if(ip3)
        {
          //  qDebug("IP3 is true");
            if(!ip3a&&cue3a&&!cue3b)
                ip3a = true;
            if(ip3a && cue3a)
            {
                    datagram_3a = read_datagram(readfile_3a);
                    if(!datagram_3a.isEmpty())
                    {
                        udp_streaming_socket->writeDatagram( datagram_3a.data() , datagram_3a.size() ,ip3_address , ip3_port);
                        udp_streaming_socket->waitForBytesWritten();
                    }
                    else
                    {
                        qDebug("closing file on 3a");
                        emit finished_file(3);
                        readfile_3a.close();
                        ip3a=false;
                        cue3a = false;
                    }

            }
            if(!ip3a && cue3b)
            {
                    datagram_3b = read_datagram(readfile_3b);
                    if(!datagram_3b.isEmpty())
                    {
                        udp_streaming_socket->writeDatagram( datagram_3b.data() , datagram_3b.size() ,ip3_address , ip3_port);
                        udp_streaming_socket->waitForBytesWritten();
                    }
                    else
                    {
                        qDebug("closing file on 3b");
                        emit finished_file(3);
                        readfile_3b.close();
                        ip3a=true;
                        cue3b = false;
                    }
            }
            if(!cue3a&&!cue3b)
                ip3 = false;
        }
        if(ip4)
        {
            if(!ip4a&&cue4a&&!cue4b)
                ip4a = true;
            if(ip4a && cue4a)
            {
                    datagram_4a = read_datagram(readfile_4a);
                    if(!datagram_4a.isEmpty())
                    {
                        udp_streaming_socket->writeDatagram( datagram_4a.data() , datagram_4a.size() ,ip4_address , ip4_port);
                        udp_streaming_socket->waitForBytesWritten();
                    }
                    else
                    {
                        qDebug("closing file on 4a");
                        emit finished_file(4);
                        readfile_4a.close();
                        ip4a=false;
                        cue4a = false;
                    }

            }
            if(!ip4a && cue4b)
            {
                    datagram_4b = read_datagram(readfile_4b);
                    if(!datagram_4b.isEmpty())
                    {
                        udp_streaming_socket->writeDatagram( datagram_4b.data() , datagram_4b.size() ,ip4_address , ip4_port);
                        udp_streaming_socket->waitForBytesWritten();
                    }
                    else
                    {
                        qDebug("closing file on 4b");
                        emit finished_file(4);
                        readfile_4b.close();
                        ip4a=true;
                        cue4b = false;
                    }
            }
            if(!cue4a&&!cue4b)
                ip4 = false;
        }
        elapsed_timer.restart();
    }
    udp_streaming_socket->close();
}

QByteArray Worker::read_datagram(QFile &readfile)
{
    int bytes_read=0;
    char packet [pkts_per_dgm*packet_size];
    QByteArray datagram;
    datagram.clear();

    for(int i=1; i<=pkts_per_dgm;i++)
    {
        bytes_read = readfile.read(packet,packet_size);
        if(bytes_read<=0)
        {
            log("reached end of file");
            datagram.clear();
            return datagram;
        }
        datagram.append( QByteArray( (char*) packet ,packet_size) );
    }
    return datagram;
}

void Worker::set_packet_period(int bitrate)
{
    if(bitrate!=0)
    {
        timer_period = 8*packet_size*pkts_per_dgm; // 8 bits per byte, ms between packets.
        timer_period = timer_period*1000000000;
        timer_period = timer_period/(bitrate);
        one_third_of_timer_period = timer_period/3;
        sleep_time = timer_period/3000;
        //qDebug() << timer_period;
    }
    else
        timer_period = 0;
}

bool Worker::stream_init(QString source_filename , QFile &readfile)
{
    readfile.setFileName(source_filename);
    /*
    int i=0;
    while(!readfile.open(QIODevice::ReadOnly))
    {
        QThread::msleep(100);
        qDebug("can't open file");
        if(i<=10)
            i++;
        else
        {
            break;
        }
    }
    readfile.close();
    */
    //QThread::sleep(5);
    if( readfile.open(QFile::ReadOnly) )
    {
        readfile.seek(0);
        log("opened file on " + readfile.fileName());
        return true;
    }
    else
    {
        log("failed to open file to stream");
        qDebug("failed to open stream");
        return false;
    }
}

void Worker::start_stream(int ip_num )
{
    qDebug()<< "Starting stream on IP: " << ip_num;
    switch ( ip_num )
    {
        case 1:
            if(cue1a||cue1b)
                ip1 = true;
        break;
        case 2:
            if(cue2a||cue2b)
                ip2 = true;
        break;
        case 3:
            if(cue3a||cue3b)
                ip3 = true;
        break;
        case 4:
            if(cue4a||cue4b)
                ip4 = true;
        break;
    }
}

void Worker::cue_stream(int ip_num, QString source_filename)
{
    qDebug() << "cueing stream on " << ip_num;
    switch ( ip_num )
    {
        case 1:
            if(!cue1a)
            {
                if( stream_init(source_filename,readfile_1a) )
                {
                    emit streaming(ip_num,source_filename);
                    qDebug("cueing stream on 1a");
                    eas = true;
                    cue1a = true;
                }
                else
                {
                    emit failed_to_cue_file(source_filename);
                    qDebug("failed to stream");
                }
            }
            else if(!cue1b)
            {
                if( stream_init(source_filename,readfile_1b) )
                {
                    qDebug("cueing stream on 1b");
                    emit streaming(ip_num,source_filename);
                    eas = true;
                    cue1b = true;
                }
                else
                {
                    emit failed_to_cue_file(source_filename);
                    qDebug("failed to stream");
                }
            }
            else
            {
                qDebug("worker busy");
                emit busy(ip_num,source_filename);
            }
            break;
        case 2:
            if(!cue2a)
            {
                if( stream_init(source_filename,readfile_2a) )
                {
                    emit streaming(ip_num,source_filename);
                    qDebug("cueing stream on 2a");
                    cue2a = true;
                }
                else
                {
                    emit failed_to_cue_file(source_filename);
                    qDebug("failed to stream");
                }
            }
            else if(!cue2b)
            {
                if( stream_init(source_filename,readfile_2b) )
                {
                    emit streaming(ip_num,source_filename);
                    qDebug("cueing stream on 2b");
                    cue2b = true;
                }
                else
                {
                    emit failed_to_cue_file(source_filename);
                    qDebug("failed to stream");
                }
            }
            else
            {
                qDebug("worker busy");
                emit busy(ip_num,source_filename);
            }
            break;
        case 3:
            if(!cue3a)
            {
                if( stream_init(source_filename,readfile_3a) )
                {
                    emit streaming(ip_num,source_filename);
                    qDebug("cueing stream on 3a");
                    cue3a = true;
                }
                else
                {
                    emit failed_to_cue_file(source_filename);
                    qDebug("failed to stream");
                }
            }
            else if(!cue3b)
            {
                if( stream_init(source_filename,readfile_3b) )
                {
                    emit streaming(ip_num,source_filename);
                    qDebug("cueing stream on 3b");
                    cue3b = true;
                }
                else
                {
                    emit failed_to_cue_file(source_filename);
                    qDebug("failed to stream");
                }
            }
            else
            {
                qDebug("worker busy");
                emit busy(ip_num,source_filename);
            }
            break;
        case 4:
            if(!cue4a)
            {
                if( stream_init(source_filename,readfile_4a) )
                {
                    emit streaming(ip_num,source_filename);
                    qDebug("cueing stream on 4a");
                    cue4a = true;
                }
                else
                {
                    emit failed_to_cue_file(source_filename);
                    qDebug("failed to stream");
                }
            }
            else if(!cue4b)
            {
                if( stream_init(source_filename,readfile_4b) )
                {
                    emit streaming(ip_num,source_filename);
                    qDebug("cueing stream on 4b");
                    cue4b = true;
                }
                else
                {
                    emit failed_to_cue_file(source_filename);
                    qDebug("failed to stream");
                }
            }
            else
            {
                qDebug("worker busy");
                emit busy(ip_num,source_filename);
            }
            break;
    }

}

void Worker::log(QString logdata)
{
    emit work_status( (QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss:zzz ") + logdata + "\n") ) ;
}
