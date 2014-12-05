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
#ifndef MUX_CONTROL_H
#define MUX_CONTROL_H
#include "QtCore"
#include <QUdpSocket>
#include <QSerialPort>

class Mux_Control : public QObject
{
    Q_OBJECT
public:
    explicit Mux_Control(QHostAddress ctrl_addr, qint16 ctrl_port, QString comport, int out_port, QObject *parent = 0);
    ~Mux_Control();
    QHostAddress control_address;
    qint16 control_port;
    enum MessageType_t {easInsert, easStop, spliceStart, spliceStop};

public slots:
    void eas_insert(QList<int> channel_list);
    void return_from_eas( QList<int> channel_list);
    void program_splice( QList<int> channel_list );
    void return_from_splice( QList<int> channel_list );
    void handleError();
    void read_mux_debug();
signals:
    void process_debug(QString);
private slots:

private:
    QSerialPort *mux_debug;
    QFile mux_log;
    QTextStream mux_log_out;
    int output_port;
    int message_type;
    QList<int> channels;
    bool splice_active;
    bool eas_active ;
    QByteArray splice_start_datagram;
    QByteArray splice_stop_datagram;
    QByteArray eas_start_datagram;
    QByteArray eas_stop_datagram;
    QUdpSocket *udpSocket;
    QList< QList<int> > channel_map;

    // *************************** Look-up Table for ATSC Minor Channel Numbers and D2Mux ASI Ports **************************

    #define MAX_CHANNELS    12            // Max Index Value for minorChans Array
        int minorChans         [ 13 ] [9] =	  // Index is Minor Channel;        [          Stream                 ]
        // Array is [Mux TS Port In] [Sat Pgm #] [# PIDs to Insert] [Type 1] [PID #1] [Type 2] [PID #2] , [ AD Port ] , [ Add Program ]
                   {{      0        ,     0     ,        0         ,  0x02  ,  0x44  ,  0x81  ,  0x45   ,      7      ,       1         }    // Index 0 not used
                               ,{0,  1, 2, 0x02, 0x44, 0x81, 0x45, 7, 1}	  // ATSC Minor Channel 1   3ABN-EN	  English TV
                               ,{0, 75, 2, 0x02, 0x44, 0x81, 0x45, 7, 1}    // ATSC Minor Channel 2   3ABN-PR   Proclaim TV
                               ,{0,  2, 2, 0x02, 0x44, 0x81, 0x45, 7, 1}    // ATSC Minor Channel 3   3ABN-DD   Dare to Dream TV
                               ,{0,  3, 2, 0x02, 0x44, 0x81, 0x45, 7, 1}    // ATSC Minor Channel 4   3ABN-ES   Latino TV
                               ,{0,111, 1, 0x81, 0x45,   0 , 0   , 7, 1}    // ATSC Minor Channel 5   3ABN-RD   English Radio
                               ,{0,133, 1, 0x81, 0x45,   0 , 0   , 7, 1}    // ATSC Minor Channel 6   3ABN-LR   Latino Radio
                               ,{0,122, 1, 0x81, 0x45,   0 , 0   , 7, 1}    // ATSC Minor Channel 7   Radio74   Radio 74

                               ,{8,  1, 2, 0x02, 0x44, 0x81, 0x45, 7, 1}    // ATSC Minor Channel 8   Testing   Program Testing
                               ,{0,  201, 2, 0x02, 0x7D5, 0x81, 0xFA5, 1, 5}    // ATSC Minor Channel 9   Alternate map for channel 8
                               ,{8,  1, 2, 0x02, 0x44, 0x81, 0x45, 7, 1}    // ATSC Minor Channel 10  Future    Default to Test channel for now
                               ,{8,  1, 2, 0x02, 0x44, 0x81, 0x45, 7, 1}    // ATSC Minor Channel 11  Future    Default to Test channel for now
                               ,{8,  1, 2, 0x02, 0x44, 0x81, 0x45, 7, 1}    // ATSC Minor Channel 12  Future    Default to Test channel for now
                               };
        // ---------------  End Look-up Table for ATSC Minor Channel Numbers to D2Mux ASI Ports and Prog Number  ----------------
        // Insert Program Input on ASI-1 = 0, ASI-2 = 1,   IP-2 = 7, IP-3 = 8, IP-4 = 9
        // IP-1 is Reserved for EAS Replacement of Video Streams (Max = 8)
        // Insert Program

};
#endif // MUX_CONTROL_H


/// Message Header Format
    /// Splicing_API_Message
    /// {
    //     MessageType      1 byte
    //     Reserved         1 byte
    //     MessageSize      2 bytes  The size of the data( ) field being sent in bytes.
    //     data()           *         Defined by Splice Start Protocol
    /// }
    /// Eas_Insert_Data {
    //      ProgramCount                        16 bits
    ///     for (i=0; i<ProgramCount; i++) {
    //          PortNumber                      16 bits
    //          ProgramNumber                   16 bits
    //          Destinations                    8 bits
    //          Reserved                        24 bits
    ///     }
    //      PidCount                            16 bits
    ///     for (i=0; i<PidCount; i++) {
    //          StreamType                      8 bits
    //          Reserved                        11 bits
    //          ElementaryPid                   13 bits
    ///     }
    /// }

     /// Eas_Stop_Data {
     //     ProgramCount                        16 bits
     ///    for (i=0; i<ProgramCount; i++) {
     //         PortNumber                      16 bits
     //         ProgramNumber                   16 bits
     ///    }
     //     PidCount                            16 bits
     ///    for (i=0; i<PidCount; i++) {
     //         StreamType                      8 bits
     //         Reserved                        11 bits
     //         ElementaryPid                   13 bits
    ///     }
    /// }




/// Splice Start Protocol
    // SpliceCount                          16 bits
    /// for (i=0; i<SpliceCount; i++) {
    //    Splice Channel                    8  bits
    //     NetworkPortNumber                16 bits
    //     NetworkProgramNumber             16 bits
    //     AdPortNumber                     16 bits
    //     AdProgramNumber                  16 bits
    //     AdPidCount                       8  bits
    ///     for (i=0; i<AdPidCount; i++) {
    //         StreamType                   8  bits
    //         Reserved                     11 bits
    //         ElementaryPid                13 bits
    ///     }
    /// }
/// Splice Stop Protocol
    /// Splice_Stop {
   //  SpliceCount                          16 bits
     ///for (i=0; i<SpliceCount; i++) {
        // NetworkPortNumber                16 bits
        // NetworkProgramNumber             16 bits
        // AdPortNumber                     16 bits
        // AdProgramNumber                  16 bits
///    }  }
