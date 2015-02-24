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
#include "automation.h"
#include "QtCore"
/// Initialize settings and Switcher on Comport
QSettings settings("ZCybercomputing", "TVARP");

/// Declare Global Variables
   QList <sch_entry> schedule;  // List that contains the event schedule
   // extern class video_window video;
    //  Switcher *switcher = new Switcher();
// Switcher *switcher=new Switcher(settings.value("COM").toInt());
//  Automation Functions
/// ========================================================================================================
Automation::Automation(QObject *parent) :
    QObject(parent)
{
    state=0;
    isOpen=0;

    mpeg_stream = new stream(this);
    connect(mpeg_stream,SIGNAL(status(QString)),this,SLOT(streaming_status(QString)));
    connect(mpeg_stream,SIGNAL(get_ts_info(QString)),this,SLOT(get_ts_info(QString)),Qt::DirectConnection);
    connect(this,SIGNAL(bitrate(int)),mpeg_stream,SLOT(set_kbitrate(int)),Qt::DirectConnection);

    ffmpeg = new FFmpeg(this);
    connect(ffmpeg,SIGNAL(ffmpeg_stdout(QString)),this,SLOT(encoder_output(QString)));
    video_dev = settings.value( "eas video device" ).toString();
    audio_dev = settings.value( "eas audio device" ).toString();
    ad_ts = new TS_Info(this);


    connect(ad_ts      ,SIGNAL(status(QString)),this,SLOT(streaming_status(QString)));

    init_mux_control();
    init_ring_detect();
}

Automation::~Automation()
{
    if( serial->isOpen() )
        close_ring_detect();
}

void Automation::get_ts_info(QString filename)
{
    emit bitrate(ad_ts->process_file(filename).kbitrate);  // blocks until bitrate in the worker thread is set.
}

void Automation::encoder_output(QString output)
{
    emit encoder_display(output);
}

void Automation::close_ring_detect()
{
    emit eas_status("Ring Detect Closed\n");
    serial->close();
}

void Automation::restart_eas_engine()
{
    emit eas_status("Restarting EAS Engine\n");
    close_ring_detect();
    init_ring_detect();
}

void Automation::start_stream(QHostAddress stream_addr,quint16 stream_port,QString sourcefile)
{
    mpeg_stream->stream_start(stream_addr,stream_port,sourcefile);
}

void Automation::init_ring_detect()
{
    emit eas_status("Initialising Ring Detect\n");
    ring_init = 0;
    QString port_num = settings.value( "eas comport" ).toString();
    channels.clear();
    channels.append(1);
    channels.append(2);
    channels.append(3);
    channels.append(4);
    channels.append(5);
    channels.append(6);
    channels.append(7);

    eas_live=false;
    eas_test=false;

    serial = new QSerialPort(this);
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
                SLOT(handleError()));
    serial->setPortName(port_num);
    serial->open(QIODevice::ReadOnly);

    check_timer= new QTimer(this);
    connect(check_timer, SIGNAL(timeout()), this, SLOT(check_eas_ring()));  // connect timer to check_eas_ring()
    connect(this, SIGNAL(eas_ring()), this, SLOT(send_eas_message()));       // connect eas_ring() to send_eas_message()
    connect(this,SIGNAL(stream_eas(QHostAddress,quint16,QString)),this,SLOT(start_stream(QHostAddress,quint16,QString)));
    check_timer->start(1);                                               // create timer with 1 ms resolution
    emit eas_status("finished eas init\n");

}

void Automation::handleError()
{
    emit eas_status( "serial port error" + serial->errorString() + QString::number( serial->error() ) + "\n" );
}

void Automation::check_eas_ring()
{

    if(ring_init <= 10)
    {
        if(serial->isOpen())
            if((serial->pinoutSignals() & QSerialPort::RingIndicatorSignal))  // if eas is connected
            {
                ring_init++;
            }
            else
            {
                emit eas_status("Ring not connected\n");
            }
        else
            emit eas_status("Port not connected\n");
    }
    else
    {
        if(serial->isOpen())
        {
            if ( !(serial->pinoutSignals() & QSerialPort::RingIndicatorSignal) && !eas_live )
            {
                emit eas_status("sensed ring\n");
                emit eas_ring();
                eas_live=true;
            }
            else if( (serial->pinoutSignals() & QSerialPort::RingIndicatorSignal) && eas_live )
            {
                emit eas_status("sensed end of ring\n");
                eas_live=false;
                /// Stop and destroy encoder
                //restart_encoder();
                capture_eas_message();
            }
        }
    }
}

void Automation::send_eas_message()
{
    emit eas_status("recieving EAS Message\n");
    //start_encoder();
    send_eas_config(channels);
}

void Automation::send_eas_config( QList<int> channel_list )
{
    d2mux->eas_insert(channel_list);
    emit eas_status("sent eas insert\n");
}

void Automation::revert_eas_config( QList<int> channel_list )
{
    d2mux->revert_eas_config(channel_list);
}

void Automation::ad_splice_insert( QList<int> channel_list )
{
    d2mux->program_splice( channel_list );
}

void Automation::ad_splice_return_to_network( QList<int> channel_list )
{
    d2mux->return_from_splice( channel_list );
}

void Automation::capture_eas_message()
{
    QString inputfile,outputfile;
    QHostAddress stream_addr;
    quint16 stream_port;

    inputfile = "./Video/ew050812-004403SD-h264lb.mov";
    outputfile = "./EAS Video/";
    outputfile.append(QDateTime::currentDateTime().toString( "ss_dd_mm_yyyy" ));
    outputfile.append(".ts");
    outputfile = QFileInfo(outputfile).absoluteFilePath();
    inputfile = QFileInfo(inputfile).absoluteFilePath();
    stream_addr.setAddress("239.0.0.220");
    stream_port = 1234;
    emit stream_eas( stream_addr, stream_port, outputfile);
    ffmpeg->encode(inputfile,outputfile);
    ffmpeg->ffplay( "udp://@239.0.0.220:1234" );

}

void Automation::init_mux_control()
{  
    d2mux = new Mux_Control(QHostAddress( settings.value("Mux Control Address").toString() ) ,
                            settings.value("Mux Control Port").toInt(),
                            settings.value("Mux Debug Comport").toString() ,
                            settings.value("mux_output_port").toInt() ,this);
    connect(d2mux,SIGNAL(process_debug(QString)),this,SLOT(process_mux_debug(QString)));
}
void Automation::streaming_status(QString string)
{
    //qDebug() << "automation stream status " << string;
    emit stream_status(string);
}

void Automation::restart_mux_control()
{
    d2mux->~Mux_Control();
    init_mux_control();
}

void Automation::process_mux_debug(QString data)
{
    emit mux_eas_log(data);
}

// ================================================================
void Automation::run_schedule()
{
    for(int i=0;i<schedule.size();i++)
    {
        if(QDateTime::currentDateTime() > schedule[i].play_time )
        {
            emit event_log_output("Removing old date");
            emit event_log_output(schedule[i].play_time.toString());
            schedule.removeAt(i);
            i--;
        }
        else
        {
            QFile file(schedule[i].play_cmd);
                 if (!file.open(QIODevice::ReadOnly))
                 {
                     QString output=schedule[i].play_cmd;
                     output+=" does not exist";
                     emit event_log_output(output);
                     schedule.removeAt(i);
                     i--;
                 }
                 else
                    file.close();
        }
    }
    if(!schedule.empty())
    {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(check_time()));
    timer->start(1);
    }
    for(int i=0;i<schedule.size();i++)
    {
        QString output;
        output.append("Will play ");
        output.append(schedule[i].play_cmd);
        output.append(" at ");
        output.append(schedule[i].play_time.toString());
        emit event_log_output(output);
    }
}

void Automation::check_time()
  {
    if(!schedule.empty()&&state==0)
    {
        if(QDateTime::currentDateTime() >= schedule[0].play_time && isOpen)
        {
            //switcher->setVideoOutputChannel(settings.value("cptr").toInt());
            emit play();
         // Must be last
            schedule.removeAt(0);
        }
        else
            if(QDateTime::currentDateTime() >= schedule[0].play_time.addSecs(-15)
                && !isOpen)
            {
                emit openFile(schedule[0].play_cmd);
                //switcher->restart_comport();
            }
    }
  }

void Automation::video_state(int v)
{
    state=v;
}
void Automation::is_open(bool open)
{
    isOpen=open;
}

//======================================================================
void Automation::log_channel(int channel,QDateTime DateTime)
{
    QString log="Changed to input ";
    log+= QString::number(channel);
    log.append(" on ");
    log.append(DateTime.toString());
    this->print_log(log);
}
void Automation::log_playback(QString message,QString file,QDateTime DateTime)
{
    QString log=message;
    log+= file;
    log.append(" on ");
    log.append(DateTime.toString());
    this->print_log(log);
}
/// Log Function
void Automation::print_log(QString log)
 {
     QFile file("Schedule_and_logs/Switcher.log");  // Open file in write append text mode
     if (!file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text))
         return;
     //initiate text stream, output and close file
     QTextStream out(&file);
     out << "\n" << log <<"\n";
     file.close();
     emit event_log_output( log );
 }

//======================================================================
/// Output Schedule to GUI
QList<QString> Automation::check_schedule()
{
    QList<QString> schedulelist;
    for(int i=0;i<schedule.size();i++)
    {
        if(QDateTime::currentDateTime() > schedule[i].play_time )
        {
            schedule.removeAt(i);
            i--;
        }
    }

    for (int b=0; b < schedule.size(); b++)
    {
       QString stringout=schedule[b].play_cmd;
       stringout.append(" on ");
       stringout.append(schedule[b].play_time.toString());
       schedulelist.append(stringout);
    }

    return(schedulelist);
}

//======================================================================
/// Load Schedule From File
void Automation::load_schedule(QString schfile)
{
    emit event_log_output("Schedule Loaded");

  //Declare Variables
    sch_entry load;
    QList<QString> line_input;
    QByteArray file_play;
    QString file_name="";

  // Purge Existing Schedule
    schedule.clear();

  //Open File
    QFile file(schfile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {  return;  }

  //Read File
    QTextStream in(&file);
     for(int i=0; !in.atEnd(); i++)
      {  line_input << in.readLine();  }

  //Process File
     for (int c=0; c < line_input.size(); c++)
     {  if(line_input[c].contains("Filename:"))
         {}
         else
         {  if(line_input[c].contains("Date:"))
            {}
             else
             {  line_input.removeAt(c);
                c--;
             }
         }
     }
  //Load Schedule from input
    for (int j=0; j< line_input.size();j++)
    {
       if(line_input[j].contains("Filename:"))
       {
          file_name = line_input[j];
          file_name.replace(0, 10, "Videos/");
          file_play=file_name.toLocal8Bit();
       }
       else
       {
          if(line_input[j].contains("Date:"))
          {
             load.play_time = QDateTime::fromString(line_input[j],"'Date:'MM'-'dd','yyyy HH:mm:ss");
             load.play_cmd = file_play;                            //"Date:11-10,2010 13:01:02"
             schedule << load;
          }
       }
    }
    file.close();
  // Sort Schedule in chronological order.
    qStableSort(schedule);

  // Filter bad entries out
    for(int i=0;i<schedule.size();i++)
    {
        if(QDateTime::currentDateTime() > schedule[i].play_time )
        {
            schedule.removeAt(i);
            i--;
        }
        else
        {
          QFile file(schedule[i].play_cmd);
               if (!file.open(QIODevice::ReadOnly))
                {
                   QString output=schedule[i].play_cmd;
                   output+=" does not exist";
                   emit event_log_output(output);
                   schedule.removeAt(i);
                   i--;
                }
                file.close();
        }
    }
    // Write cleaned schedule to file
    QFile write_file("Schedule_and_logs/schedule.automation");
        if (write_file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&write_file);
            QString last,fname;
            for(int i=0;i<schedule.size();i++)
            {
                fname=schedule[i].play_cmd;
                fname.replace(0, 7, "");
             //  if(fname!=last)
                    out<< " Filename:" << fname <<"\n";
              // last=stringout;
                out << schedule[i].play_time.toString("'Date:'MM'-'dd','yyyy HH:mm:ss")<<"\n";
            }
            write_file.close();
        }

}
//======================================================================
/// ========================================================================================================

void Automation::load_config()
{
  //Declare Variables
    QList<QString> line_input;
    QString config_entry;
  //Open and Read File
    QFile file("Schedule_and_logs/automation.config");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {  return;  }
    QTextStream in(&file);
     for(int i=0; !in.atEnd(); i++)
      {  line_input << in.readLine();  }

  //Process File and load configuration
    for (int c=0; c < line_input.size(); c++)
    {
       if(line_input[c].contains("COMPORT ="))
       {
           config_entry = line_input[c];
           config_entry.remove(0, 9);
           comport=config_entry.toInt();
           //switcher->change_port(config_entry.toInt());
           settings.setValue("COM",config_entry.toInt());
       }
       if(line_input[c].contains("Computer Input ="))
       {
           config_entry = line_input[c];
           config_entry.remove(0, 16);
           settings.setValue("cptr",config_entry.toInt());
       }
       if(line_input[c].contains("Satellite Input ="))
       {
           config_entry = line_input[c];
           config_entry.remove(0, 17);
           settings.setValue("sat",config_entry.toInt());
       }
    }
    file.close();
}
