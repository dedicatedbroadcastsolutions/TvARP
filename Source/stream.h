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
#ifndef STREAM_H
#define STREAM_H

#include "QtCore"
#include <QUdpSocket>
#include "QThread"

typedef QList< QByteArray > BufferList;

Q_DECLARE_METATYPE(BufferList)
Q_DECLARE_METATYPE(QHostAddress)

class Worker : public QObject
{
    Q_OBJECT

  public:
    explicit Worker(quint16 port);
    ~Worker();
    bool quit;
  public slots:
    void set_packet_period(int bitrate);
    void start_loop();
    void cue_stream(int ip_num,QString source_filename);
    void start_stream(int ip_num);
  signals:
    void done_streaming();
    void datagram_sent(QByteArray datagram);
    //void find_bitrate(QString filename);
    void work_status( QString );
    void streaming(int,QString);
    void busy(int ip_num, QString source_filename );
  private slots:

    QByteArray read_datagram(QFile &readfile);
    bool stream_init(QString source_filename , QFile &readfile);
    void log(QString logdata);

  private:
  // variables for reading datagrams from file
    QFile readfile_1a;
    QFile readfile_1b;
    QFile readfile_2a;
    QFile readfile_2b;
    QFile readfile_3a;
    QFile readfile_3b;
    QFile readfile_4a;
    QFile readfile_4b;
    int pkts_per_dgm;
    int packet_size;
    bool ip1, ip2, ip3, ip4;
  // variables for sending datagrams
    qint64 timer_period;
    QElapsedTimer elapsed_timer;
    QByteArray datagram_1a;
    QByteArray datagram_1b;
    QByteArray datagram_2a;
    QByteArray datagram_2b;
    QByteArray datagram_3a;
    QByteArray datagram_3b;
    QByteArray datagram_4a;
    QByteArray datagram_4b;
    bool ip1a, ip2a, ip3a, ip4a;
    bool ip1b, ip2b, ip3b, ip4b;
    bool eas;
    bool cue1a,cue1b,cue2a,cue2b,cue3a,cue3b,cue4a,cue4b;
    QUdpSocket *udp_streaming_socket;
    int socket_state;
    int sleep_time;
    int one_third_of_timer_period;
};

class stream : public QObject
{
    Q_OBJECT

    QThread workerThread;
  public:
    explicit stream(QObject *parent);
    ~stream();
    QString ip1_cue,ip2_cue,ip3_cue,ip4_cue;
  public slots:
    void done_with_worker();
    void worker_status(QString string);
    void process_busy(int ip_port, QString source_filename );
    void cancel_cue(int ip_port,QString filename);
    void cue_file();
    void stream_start(int ip_port);
    void stream_cue(int ip_port, QString source_filename);
  signals:
    void start_stream_loop();
    void done_with_stream();
    void start_streaming( int ip_port );
    void status( QString );
    void cue_streaming(int ip_port, QString source_filename);
  private:
    Worker *worker;

  private slots:
    void log(QString logdata);

};
#endif // STREAM_H
