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
    explicit Worker();
    ~Worker();
    bool loop;

  public slots:
  void send_datagrams(QHostAddress stream_addr, qint16 stream_port, qint64 timer_freq , BufferList datagram_buffer);

signals:
  void done_streaming();

  private:
    void save_file(BufferList datagram_buffer);
    QUdpSocket  *udp_streaming_socket;
    int datagram_index;
    int socket_state;
    QElapsedTimer elapsed_timer;
};

class stream : public QObject
{
    Q_OBJECT

    QThread workerThread;
  public:
    explicit stream(QHostAddress stream_addr, qint16 stream_port, int kBitRate, int pktsPerDgram,int pkt_size, QObject *parent);
    ~stream();

  public slots:
    void send_udp_packet();
    void make_udp_packet(QByteArray packet);
    void done_with_worker();
  signals:
    void start_stream(QHostAddress stream_addr, qint16 stream_port,  qint64 timer_freq , BufferList datagram_buffer);
    void done_with_stream();
  private:
    QHostAddress        ip_stream_address;
    qint16              ip_stream_port;

    BufferList  datagram_buffer;
    QByteArray  datagram, packet;
    Worker *worker;
    qint64 timer_freq;
    int packet_index , KbitRate , pkts_PerDgram , packet_size , dgram_size;
};
#endif // STREAM_H
