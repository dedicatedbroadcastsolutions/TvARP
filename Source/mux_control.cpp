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
#include "mux_control.h"

/// ========================================================================================================
Mux_Control::Mux_Control(QHostAddress ctrl_addr, qint16 ctrl_port, QString comport, int out_port , QObject *parent) :
    QObject(parent)
{
    qDebug("mux constructor");
    mux_log.setFileName("./Schedule_and_logs/mux_log.txt");
    //qDebug()<< "mux debug port " << comport << "mux ctrl port "<< ctrl_port << "mux ctrl addr " << ctrl_addr << "mux output port" << out_port;
    splice_active = 0;
    eas_active = 0;
    udpSocket = new QUdpSocket(this);
    control_address = ctrl_addr ;
    control_port = ctrl_port;
    output_port = out_port;
    mux_debug = new QSerialPort(this);
    connect(mux_debug, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError()));
    connect(mux_debug, SIGNAL(readyRead()),this, SLOT(read_mux_debug()));

    mux_debug->setPortName(comport);
    mux_debug->setBaudRate(QSerialPort::Baud115200);
    mux_debug->setDataBits(QSerialPort::Data8);
    mux_debug->setParity(QSerialPort::NoParity);
    mux_debug->setStopBits(QSerialPort::OneStop);
    mux_debug->setFlowControl(QSerialPort::HardwareControl);
    mux_debug->open(QIODevice::ReadOnly);
}

Mux_Control::~Mux_Control()
{
    qDebug("mux destructor");
    // remove duplicate entries from channels
    QSet<int> ch_set;
    ch_set = channels.toSet();
    channels = QList<int>::fromSet(ch_set);
    if(splice_active&&channels.size()>0)
    {
        emit mux_debug_status( ("returning to network \n" ));
        return_from_splice( channels );
    }
    udpSocket->close();
    emit mux_debug_status( ("mux control destructor \n" ));
}

void Mux_Control::read_mux_debug()
{
   // qDebug("reading mux data from serial port");
    QString data;
    data = mux_debug->readAll();
    if ( mux_log.open( QFile::WriteOnly | QFile::Append ) )
    {
        mux_log_out.setDevice(&mux_log);
        mux_log_out << data;
        mux_log.close();
    }
     data = data.remove( QRegExp("\\r") );
     emit process_debug(data);
}

void Mux_Control::handleError()
{
    emit mux_debug_status( "mux debug port error" + mux_debug->errorString() + QString::number(mux_debug->error()) + "\n" ) ;
}

void Mux_Control::eas_insert( QList<int> channel_list)
{
    qDebug("eas insert");
    emit mux_debug_status( "eas insert on " + QString::number( channel_list[channel_list.size()-1 ] )  + "\n") ;
    eas_active = 1;
    // remove duplicate entries from channel_list
    QSet<int> ch_set;
    ch_set = channel_list.toSet();
    channel_list = QList<int>::fromSet(ch_set);
    qSort(channel_list);
    // record spliced channels for destructor
    channels.append(channel_list);

    // Declare Variables.
    int channel;
    int netPort;
    int ProgramCount;
    unsigned char ProgramCountHigh;
    unsigned char ProgramCountLow;
    unsigned char netPortHigh;
    unsigned char netPortLow;
    int netProg;
    int messageSize=0;
    unsigned char messageSizeHigh;
    unsigned char messageSizeLow;
    unsigned char netProgHigh;
    unsigned char netProgLow;
    int easPidCount;
    unsigned char StreamType;
    int Pid;
    unsigned char PidHigh;
    unsigned char PidLow;
    unsigned char easPidHigh;
    unsigned char easPidLow;

    eas_start_datagram.clear();      // clear array contents for new datagram
/// Message Header
 // MessageType – An integer value that indicates what message type is being sent.
 // Message Type = "Splice_Start" or "Splice_Stop
    message_type = 0x01;
    eas_start_datagram.append( (char)message_type  );
 // Reserved Byte.
    eas_start_datagram.append( (char)0xff );
 // MessageSize – The size of the data( ) field being sent in bytes.
 // Ensure to only embed up to 12 subchannels.
    if( channel_list.size()<=MAX_CHANNELS)
    {
        ProgramCount = channel_list.size();
    }
    else
    {
        ProgramCount = 12;
    }

    int stream_number=0;
    for (int index = 0; index < channel_list.size() && index <= MAX_CHANNELS ; index++)
    {
        stream_number +=  minorChans[channel_list[index]][2];  // number of PIDs per channel
    }

  //  qDebug()<< "Program Count = "<<ProgramCount << "stream num =" << stream_number;
    messageSize = (2 + ProgramCount*8 + 2 + 2*4);

   // qDebug()<<"message size = "<<messageSize << "Datagram size should be = "<< messageSize+4;
    messageSizeHigh = (messageSize >> 8) & 0xff;
    messageSizeLow  = (messageSize     ) & 0xff;
    eas_start_datagram.append( (char)messageSizeHigh );
    eas_start_datagram.append( (char)messageSizeLow  );
/// done with header.

 // ProgramCount – Number of programs to receive EAS message injection.
    ProgramCountHigh = (ProgramCount >> 8) & 0xff;
    ProgramCountLow  = (ProgramCount     ) & 0xff;
    eas_start_datagram.append(ProgramCountHigh);
    eas_start_datagram.append(ProgramCountLow);

    for (int index = 0; index < ProgramCount ; index++) // till end of channel list or max channels
    {                                                                                     // so as not to overflow on minorChans index
        channel = channel_list[index];
     // PortNumber – Input port of program to receive EAS message injection.
        netPort    = minorChans[channel][0];           // ATSC Minor Channel Selection Look-up Table (Array)
        netPortHigh  = (netPort >> 8) & 0xff ;
        netPortLow   = (netPort     ) & 0xff ;
        eas_start_datagram.append(netPortHigh);
        eas_start_datagram.append(netPortLow);

     // ProgramNumber – Input program number of program to receive EAS message injection.
        netProg    = minorChans[channel][1];
        netProgHigh  = (netProg >> 8) & 0xff  ;
        netProgLow   = (netProg     ) & 0xff  ;
        eas_start_datagram.append(netProgHigh);
        eas_start_datagram.append(netProgLow );

     // Destinations – Destinations of program to receive EAS message injection.
     // Each bit in byte represents a destination.  Bit 0 = Port 0 (ASI-1), Bit 1 = Port 1 (ASI-2), Bit 2 = GigE 1, etc.  Destinations can be ORed together in byte.
        ///eas_start_datagram.append( (char)0x10 );
        eas_start_datagram.append( (char) 0x01 << output_port );   // // 0x10 Send on port IP-1    0x1 Send on port ASI-1
        //                                                                                        00000001
        emit mux_debug_status("Insert EAS on port " + QString::number(output_port)  + "\n");
    //qDebug()<< "output port" << (char) 0x01 << output_port;
     // Reserved – Reserved for future use.     24 bits
        eas_start_datagram.append( (char)0xff );
        eas_start_datagram.append( (char)0xff );
        eas_start_datagram.append( (char)0xff );
    }

 // PidCount – Number of elementary streams in EAS message.
   // easPidCount = minorChans[channel][2];   // First Index is "minor (Channel)"; Second Index is "Number of Ad Source PIDs"
    easPidCount =2;
    easPidHigh  = (easPidCount >> 8) & 0xff  ;
    easPidLow   = (easPidCount     ) & 0xff  ;
    eas_start_datagram.append( (char)easPidHigh );
    eas_start_datagram.append( (char)easPidLow );

    for (int stream_index=0; stream_index<easPidCount; stream_index++)
    {
       // qDebug() << "eas on stream " << stream_index;
     // StreamType – Stream type of elementary stream.
        StreamType  = minorChans[1][2*stream_index+3];// Set in #defines
        eas_start_datagram.append( (char)StreamType   );    // Put Audio PID Info into udp_send_buffer
       // qDebug()<< "Stream Type"<<StreamType;

     // Reserved – Reserved for future use.
        eas_start_datagram.append( (char)0xff          );   // Reserved Byte

     // ElementaryPid – Specifies the PID of the elementary stream.
        Pid      = minorChans[1][2*stream_index+4];   // Set in #defines
       // qDebug()<< "pid "<< Pid;
        PidHigh  = ( Pid >> 8) | 0xe0;                      // Hi 3 bits = 1s (Reserved bits)
        PidLow    = ( Pid     ) & 0xff;
        eas_start_datagram.append( (char)PidHigh );         // Vid PID Hi 3 bits = 1s (Reserved Bits)
        eas_start_datagram.append( (char)PidLow  );
    }
   // qDebug()<< "Datagram size =" << eas_start_datagram.size();
    udpSocket->writeDatagram(eas_start_datagram.data(), eas_start_datagram.size(),control_address , control_port);
}

void Mux_Control::revert_eas_config(QList<int> channel_list)
{


    // remove duplicate entries from channel_list
    QSet<int> ch_set;
    ch_set = channel_list.toSet();
    channel_list = QList<int>::fromSet(ch_set);
    qSort(channel_list);
    // record spliced channels for destructor
    channels.append(channel_list);

    // Declare Variables.
    int channel;
    int netPort;
    int ProgramCount;
    unsigned char ProgramCountHigh;
    unsigned char ProgramCountLow;
    unsigned char netPortHigh;
    unsigned char netPortLow;
    int netProg;
    int messageSize=0;
    unsigned char messageSizeHigh;
    unsigned char messageSizeLow;
    unsigned char netProgHigh;
    unsigned char netProgLow;
    int easPidCount;
    unsigned char StreamType;
    int Pid;
    unsigned char PidHigh;
    unsigned char PidLow;
    unsigned char easPidHigh;
    unsigned char easPidLow;

    eas_stop_datagram.clear();      // clear array contents for new datagram
/// Message Header
 // MessageType – An integer value that indicates what message type is being sent.
 // Message Type = "Splice_Start" or "Splice_Stop
    message_type = 0x02;
    eas_stop_datagram.append( (char)message_type  );
 // Reserved Byte.
    eas_stop_datagram.append( (char)0xff );
 // MessageSize – The size of the data( ) field being sent in bytes.
 // Ensure to only embed up to 12 subchannels.
    if( channel_list.size()<=MAX_CHANNELS)
    {
        ProgramCount = channel_list.size();
    }
    else
    {
        ProgramCount = 12;
    }

    int stream_number=0;
    for (int index = 0; index < channel_list.size() && index <= MAX_CHANNELS ; index++)
    {
        stream_number +=  minorChans[channel_list[index]][2];  // number of PIDs per channel
    }

   // qDebug()<< "Program Count = "<<ProgramCount << "stream num =" << stream_number;
    messageSize = (2 + ProgramCount*4 + 2 + 2*4);;

   // qDebug()<<"message size = "<<messageSize << "Datagram size should be = "<< messageSize+4;
    messageSizeHigh = (messageSize >> 8) & 0xff;
    messageSizeLow  = (messageSize     ) & 0xff;
    eas_stop_datagram.append( (char)messageSizeHigh );
    eas_stop_datagram.append( (char)messageSizeLow  );
/// done with header.

 // ProgramCount – Number of programs to receive EAS message injection.
    ProgramCountHigh = (ProgramCount >> 8) & 0xff;
    ProgramCountLow  = (ProgramCount     ) & 0xff;
    eas_stop_datagram.append(ProgramCountHigh);
    eas_stop_datagram.append(ProgramCountLow);

    for (int index = 0; index < ProgramCount ; index++) // till end of channel list or max channels
    {                                                                                     // so as not to overflow on minorChans index
        channel = channel_list[index];
     // PortNumber – Input port of program to receive EAS message injection.
        netPort    = minorChans[channel][0];           // ATSC Minor Channel Selection Look-up Table (Array)
        netPortHigh  = (netPort >> 8) & 0xff ;
        netPortLow   = (netPort     ) & 0xff ;
        eas_stop_datagram.append(netPortHigh);
        eas_stop_datagram.append(netPortLow);

     // ProgramNumber – Input program number of program to receive EAS message injection.
        netProg    = minorChans[channel][1];
        netProgHigh  = (netProg >> 8) & 0xff  ;
        netProgLow   = (netProg     ) & 0xff  ;
        eas_stop_datagram.append(netProgHigh);
        eas_stop_datagram.append(netProgLow );
    }

 // PidCount – Number of elementary streams in EAS message.
   // easPidCount = minorChans[channel][2];   // First Index is "minor (Channel)"; Second Index is "Number of Ad Source PIDs"
    easPidCount =2;
    easPidHigh  = (easPidCount >> 8) & 0xff  ;
    easPidLow   = (easPidCount     ) & 0xff  ;
    eas_stop_datagram.append( (char)easPidHigh );
    eas_stop_datagram.append( (char)easPidLow );

    for (int stream_index=0; stream_index<easPidCount; stream_index++)
    {
       // qDebug() << "eas on stream " << stream_index;
     // StreamType – Stream type of elementary stream.
        StreamType  = minorChans[1][2*stream_index+3];// Set in #defines
        eas_stop_datagram.append( (char)StreamType   );    // Put Audio PID Info into udp_send_buffer
        //qDebug()<< "Stream Type"<<StreamType;

     // Reserved – Reserved for future use.
        eas_stop_datagram.append( (char)0xff          );   // Reserved Byte

     // ElementaryPid – Specifies the PID of the elementary stream.
        Pid      = minorChans[1][2*stream_index+4];   // Set in #defines
       // qDebug()<< "pid "<< Pid;
        PidHigh  = ( Pid >> 8) | 0xe0;                      // Hi 3 bits = 1s (Reserved bits)
        PidLow    = ( Pid     ) & 0xff;
        eas_stop_datagram.append( (char)PidHigh );         // Vid PID Hi 3 bits = 1s (Reserved Bits)
        eas_stop_datagram.append( (char)PidLow  );
    }
    //qDebug()<< "Datagram size =" << eas_stop_datagram.size();
    udpSocket->writeDatagram(eas_stop_datagram.data(), eas_stop_datagram.size(),control_address , control_port);
    eas_active = 0;
}

void Mux_Control::program_splice( QList<int> channel_list )
{
    splice_active = 1;
    // remove duplicate entries from channel_list
    channels.clear();
    QSet<int> ch_set;
    ch_set = channel_list.toSet();
    channel_list = QList<int>::fromSet(ch_set);
    qSort(channel_list);
    // record spliced channels for destructor
    channels.append(channel_list);

    // Declare Variables.
    int channel;
    unsigned char spliceChan;
    int netPort;
    unsigned char spliceCountHigh;
    unsigned char spliceCountLow;
    int spliceCount;
    unsigned char netPortHigh;
    unsigned char netPortLow;
    int netProg;
    int messageSize;
    unsigned char messageSizeHigh;
    unsigned char messageSizeLow;
    unsigned char netProgHigh;
    unsigned char netProgLow;
    int adPort ;
    unsigned char adPortHigh;
    unsigned char adPortLow;
    int adProg;
    unsigned char adProgHigh;
    unsigned char adProgLow;
    int adPidCount;
    unsigned char StreamType;
    int Pid;
    unsigned char PidHigh;
    unsigned char PidLow;
    qDebug()<< "Program splice on " << channels;
    splice_start_datagram.clear();      // clear array contents for new datagram
/// Message Header
 // MessageType – An integer value that indicates what message type is being sent.
 // Message Type = "Splice_Start" or "Splice_Stop
    message_type = 0x03;
    splice_start_datagram.append( (char)message_type  );
 // Reserved Byte.
    splice_start_datagram.append( (char)0xff );
 // MessageSize – The size of the data( ) field being sent in bytes.
 // Ensure to only embed up to 12 subchannels.
    if( channel_list.size()<=MAX_CHANNELS)
    {
        spliceCount = channel_list.size();
    }
    else
    {
        spliceCount = 12;
    }

    int stream_number=0;
    for (int index = 0; index < channel_list.size() && index <= MAX_CHANNELS ; index++)
    {
        stream_number +=  minorChans[channel_list[index]][2];  // number of PIDs per channel
    }

    messageSize = 4+(2 + spliceCount*(10+ stream_number*4));;
    messageSizeHigh = (messageSize >> 8) & 0xff;
    messageSizeLow  = (messageSize     ) & 0xff;
    splice_start_datagram.append( (char)messageSizeHigh );
    splice_start_datagram.append( (char)messageSizeLow  );
/// done with header.
 // SpliceCount – Number of programs to splice.
    spliceCountHigh = (spliceCount >> 8) & 0xff;
    spliceCountLow  = (spliceCount     ) & 0xff;
    splice_start_datagram.append(spliceCountHigh);
    splice_start_datagram.append(spliceCountLow);

    for (int index = 0; index < channel_list.size() && index <= MAX_CHANNELS ; index++) // till end of channel list or max channels
    {                                                                                     // so as not to overflow on minorChans index
     // Splice Channel – First Splice Module is Splice Channel 0.
     // Splice Channel increments by 1 for each other splice module, when implemented.
        spliceChan = index;
        splice_start_datagram.append((char)spliceChan);

        channel = channel_list[index];
     // NetworkPortNumber – Input port of network program.  (port on mux)
        netPort    = minorChans[channel][0];           // ATSC Minor Channel Selection Look-up Table (Array)
        netPortHigh  = (netPort >> 8) & 0xff ;
        netPortLow   = (netPort     ) & 0xff ;
        splice_start_datagram.append(netPortHigh);
        splice_start_datagram.append(netPortLow);

     // NetworkProgramNumber – Input program number of network program.
        netProg    = minorChans[channel][1];
        netProgHigh  = (netProg >> 8) & 0xff ;
        netProgLow   = (netProg     ) & 0xff ;
        splice_start_datagram.append(netProgHigh);
        splice_start_datagram.append(netProgLow);

     // AdPortNumber – Input port of insertion program.
        adPort     = minorChans[channel][7];
        //adPort     = AD_PORT;
      //  qDebug()<< "ad port = "<< adPort;
        adPortHigh   = (adPort >> 8) & 0xff ;
        adPortLow    = (adPort     ) & 0xff ;
        splice_start_datagram.append(adPortHigh);
        splice_start_datagram.append(adPortLow);

     // AdProgramNumber – Input program number of ad program.
        adProg     = minorChans[channel][8];
        //adProg       = AD_PROG;
       // qDebug()<< "ad prog = "<< adProg;
        adProgHigh   = (adProg >> 8) & 0xff ;
        adProgLow    = (adProg     ) & 0xff ;
        splice_start_datagram.append(adProgHigh);
        splice_start_datagram.append(adProgLow);

     // AdPidCount – Number of PIDs in Ad program.
        adPidCount = minorChans[channel][2];   // First Index is "minor (Channel)"; Second Index is "Number of Ad Source PIDs"
        splice_start_datagram.append( (char)adPidCount );

        for (int stream_index=0; stream_index<adPidCount; stream_index++)
        {
         // StreamType – Stream type of elementary stream.
            StreamType  = minorChans[channel][2*stream_index+3];             // Set in #defines
            splice_start_datagram.append( (char)StreamType   );           // Put Audio PID Info into udp_send_buffer
           // qDebug()<< "splice Stream type = " << StreamType;
         // Reserved – Reserved for future use.
            splice_start_datagram.append( (char)0xff          );				  // Reserved Byte

         // ElementaryPid – Specifies the PID of the elementary stream.
            Pid      = minorChans[channel][2*stream_index+4];                     // Set in #defines
            PidHigh  = ( Pid >> 8) | 0xe0;        // Hi 3 bits = 1s (Reserved bits)
            PidLow    = ( Pid     ) & 0xff;
            splice_start_datagram.append( (char)PidHigh    );			  // Vid PID Hi 3 bits = 1s (Reserved Bits)
            splice_start_datagram.append( (char)PidLow     );
            //qDebug()<< "Splice PID = " << Pid;
        }
   }
   udpSocket->writeDatagram(splice_start_datagram.data(), splice_start_datagram.size(),control_address , control_port);
}

void Mux_Control::return_from_splice( QList<int> channel_list )
{
    splice_active = 0;
    // remove duplicate entries from channel_list
    QSet<int> ch_set;
    ch_set = channel_list.toSet();
    channel_list = QList<int>::fromSet(ch_set);
    qSort(channel_list);
/// Remove channels from this splice.
    for (int in = 0; in<channel_list.size();in++)
    {
        channels.removeAll(channel_list[in]);
    }
///
    int channel;
    int netPort;
    unsigned char spliceCountHigh;
    unsigned char spliceCountLow;
    int spliceCount;
    unsigned char netPortHigh;
    unsigned char netPortLow;
    int netProg;
    int messageSize;
    unsigned char messageSizeHigh;
    unsigned char messageSizeLow;
    unsigned char netProgHigh;
    unsigned char netProgLow;
    int adPort ;
    unsigned char adPortHigh;
    unsigned char adPortLow;
    int adProg;
    unsigned char adProgHigh;
    unsigned char adProgLow;
    splice_stop_datagram.clear();      // clear array contents for new datagram

/// Message Header
 // Message Type = "Splice_Stop 0x04"
    message_type = 0x04;
    splice_stop_datagram.append( (char)message_type  );

 // Reserved Byte.
    splice_stop_datagram.append( (char)0xff );

 // MessageSize – The size of the data( ) field being sent in bytes.
    // Ensure to only embed up to 12 subchannels.
    if( channel_list.size()<=MAX_CHANNELS)
    {
        spliceCount = channel_list.size();
    }
    else
    {
        spliceCount = 12;
    }
    messageSize = 4+2+spliceCount*8;
    messageSizeHigh = (messageSize >> 8) & 0xff;
    messageSizeLow  = (messageSize     ) & 0xff;
    splice_stop_datagram.append( (char)messageSizeHigh );
    splice_stop_datagram.append( (char)messageSizeLow  );
/// done with header.

    // SpliceCount – Number of programs to splice.
       spliceCountHigh = (spliceCount >> 8) & 0xff;
       spliceCountLow  = (spliceCount     ) & 0xff;
       splice_stop_datagram.append(spliceCountHigh);
       splice_stop_datagram.append(spliceCountLow);

    for (int index = 0; index < spliceCount ; index++) // till end of channel list or max channels
    {
           channel = channel_list[index];

        // NetworkPortNumber – Input port of network program.  (port on mux)
           netPort    = minorChans[channel][0];           // ATSC Minor Channel Selection Look-up Table (Array)
           netPortHigh  = (netPort >> 8) & 0xff ;
           netPortLow   = (netPort     ) & 0xff ;
           splice_stop_datagram.append(netPortHigh);
           splice_stop_datagram.append(netPortLow);

        // NetworkProgramNumber – Input program number of network program.
           netProg    = minorChans[channel][1];
           netProgHigh  = (netProg >> 8) & 0xff ;
           netProgLow   = (netProg     ) & 0xff ;
           splice_stop_datagram.append(netProgHigh);
           splice_stop_datagram.append(netProgLow);

        // AdPortNumber – Input port of insertion program.
           adPort     = minorChans[channel][7];
           //adPort     = AD_PORT;
           //qDebug()<< "ad port = "<< adPort;
           adPortHigh   = (adPort >> 8) & 0xff ;
           adPortLow    = (adPort     ) & 0xff ;
           splice_stop_datagram.append(adPortHigh);
           splice_stop_datagram.append(adPortLow);

        // AdProgramNumber – Input program number of ad program.
           adProg     = minorChans[channel][8];
           //adProg     = AD_PROG;
           //qDebug()<< "ad prog = "<< adProg;
           adProgHigh   = (adProg >> 8) & 0xff ;
           adProgLow    = (adProg     ) & 0xff ;
           splice_stop_datagram.append(adProgHigh);
           splice_stop_datagram.append(adProgLow);
    }
    udpSocket->writeDatagram(splice_stop_datagram.data(), splice_stop_datagram.size(),control_address , control_port);
}
