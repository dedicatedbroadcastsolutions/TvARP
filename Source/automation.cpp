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
/// Initialize settings
QSettings settings("ZCybercomputing", "TVARP");

//  Automation Functions
/// ========================================================================================================
Automation::Automation(QObject *parent) :
    QObject(parent)
{
    state=0;
    isOpen=0;
    show_vmon=false;

    mpeg_stream = new stream(this);
    connect(mpeg_stream,SIGNAL(status(QString)),this,SLOT(streaming_status(QString)));
    check_timer= new QTimer(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(check_time()));
    timer->start(1);
    connect(check_timer, SIGNAL(timeout()), this, SLOT(check_eas_ring()));  // connect timer to check_eas_ring()
    connect(this, SIGNAL(eas_ring()), this, SLOT(send_eas_message()));       // connect eas_ring() to send_eas_message()
    ffmpeg = new FFmpeg(this);
    connect(ffmpeg,SIGNAL(ffmpeg_stdout(QString)),this,SLOT(encoder_output(QString)));
    connect(ffmpeg,SIGNAL(ffmpeg_status(QString)),this,SLOT(streaming_status(QString)));
    connect(ffmpeg,SIGNAL(ffplay_stdout(QString)),this,SLOT(streaming_status(QString)));
    connect(ffmpeg,SIGNAL(ffmpeg_finished(bool )),this,SLOT(encoder_finished(bool)));
    connect(ffmpeg,SIGNAL(transcode_stdout_display(QString)),this,SLOT(ingest_display(QString)));
    connect(ffmpeg,SIGNAL(analysis_stdout_display(QString)),this,SLOT(ingest_display(QString)));
    connect(ffmpeg,SIGNAL(transcode_finished()),this,SLOT(transcode_finished()));
   // ad_ts = new TS_Info(this);

   // connect(ad_ts      ,SIGNAL(status(QString)),this,SLOT(streaming_status(QString)));

    init_mux_control();
    init_ring_detect();
    connect(this,SIGNAL(mux_eas_log(QString)),this,SLOT(save_log(QString)));
    connect(this,SIGNAL(stream_status(QString)),this,SLOT(save_log(QString)));
    connect(this,SIGNAL(eas_status(QString)),this,SLOT(save_log(QString)));
    connect(this,SIGNAL(openFile(int,QString)),this,SLOT(cue_stream(int,QString)));
    connect(this,SIGNAL(play(int)),this,SLOT(start_stream(int)));
    connect(mpeg_stream,SIGNAL(done_with_file(int)),this,SLOT(done_with_file(int)));
    //load_sch= new QTimer(this);
    //connect(load_sch, SIGNAL(timeout()),this,SLOT(load_schedule()));
    //load_sch->setInterval(1000);
    //load_sch->start();

    watcher.addPath("C:/Remote/insert.sch");
    QObject::connect(&watcher, SIGNAL(fileChanged(QString)), this, SLOT(load_schedule(QString)));
    load_schedule("C:/Remote/insert.sch");
    video_watch_dir = "C:/Remote/Videos";
    watcher.addPath(video_watch_dir);
    QObject::connect(&watcher, SIGNAL(directoryChanged(QString)),this,SLOT(check_ingest_dir(QString)));

    id_channels.clear();
    id_channels.append(1);
    id_channels.append(2);
    id_channels.append(3);
    id_channels.append(4);
    id_channels.append(5);
    id_channels.append(6);
    id_channels.append(7);
    eas_nc = false;
    eas_ready = false;
    eas_np = false;
    station_id_loaded=false;
    station_id_played=false;
}

Automation::~Automation()
{
    kill_ts_info();
    if(!share_comport)
        if( serial->isOpen() )
            close_ring_detect();
}

void Automation::done_with_file(int port)
{
    ad_splice_return_to_network(ad_channels,7,7);
}

void Automation::kill_ffmpeg()
{
    if(ffmpeg!=NULL)
    ffmpeg->kill_encoder();
}

void Automation::kill_ts_info()
{
  //  if(ad_ts!=NULL)
    //    ad_ts->kill=true;
}

void Automation::transcode_finished()
{
    emit ingest_finished();
}

void Automation::get_bitrate(QString filename)
{
    qDebug("automation, asking ffmpeg about bitrate");
    emit bitrate( ffmpeg->file_info(filename) );
    qDebug("automation sent bitrate signal");
}

void Automation::encoder_output(QString output)
{
    emit encoder_display(output);
}

void Automation::encoder_finished( bool state)
{
    if(!state)
        kill_ffmpeg();
    emit encoder_done();
}

void Automation::ingest_display(QString string)
{
    emit ingest_disp(string);
}

void Automation::cue_station_id()
{
        QString id_file;
        d2mux->eas_insert(id_channels);
        id_file = settings.value("ID File").toString();
        qDebug() << "playing station id: " << id_file;
        cue_stream(1,id_file);
}

void Automation::start_station_id()
{
    qDebug("Starting STation ID File");
        start_stream(1);
}

void Automation::ingest_cancel()
{
    qDebug("Need to send quit command");
}

void Automation::done_streaming(int ip_port)
{

}

void Automation::set_id_channels(QList<int> ch)
{
    id_channels.clear();
    id_channels = ch;
}

void Automation::close_ring_detect()
{
    check_timer->stop();
    if(!share_comport)
        serial->close();
}

void Automation::restart_eas_engine()
{
    if(eas_ready||eas_nc||eas_np)
        log_eas("Restarting EAS Engine");
    close_ring_detect();
    kill_ts_info();
    kill_ffmpeg();
    init_ring_detect();
}

void Automation::start_stream(int ip_port)
{
    qDebug("automation is starting the stream");
    mpeg_stream->stream_start(ip_port);
}

void Automation::cue_stream(int ip_port, QString sourcefile)
{
    qDebug("automation is cueing the stream");
    mpeg_stream->stream_cue(ip_port,sourcefile);
}

void Automation::clear_stream(int ip_port)
{

}

void Automation::init_ring_detect()
{
    eas_nc = false;
    //log_eas("Initialising Ring Detect");
    ring_init = 0;
    if(settings.value( "eas comport" ).toString().contains(settings.value("Mux Debug Comport").toString(),Qt::CaseInsensitive))
    {

        log_eas("sharing comport");
        qDebug("comport is the same");
        share_comport = true;
    }
    else
        share_comport = false;

    QString port_num = settings.value( "eas comport" ).toString();
    eas_channels.clear();
    eas_channels.append(1);
    eas_channels.append(2);
    eas_channels.append(3);
    eas_channels.append(4);
    eas_channels.append(5);
    eas_channels.append(6);
    eas_channels.append(7);

    eas_live=false;
    eas_test=false;

    if(!share_comport)
    {
        serial = new QSerialPort(this);
        connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError()));
        serial->setPortName(port_num);
        serial->open(QIODevice::ReadOnly);
        if(!serial->isOpen())
        {
            log_eas("could not open port");
            eas_np = true;
        }
    }
    else
    {
        qDebug("New code goes here");
    }
    check_timer->start(1);                                               // create timer with 1 ms resolution
}

void Automation::set_eas_channels(QList<int> ch)
{
    eas_channels.clear();
    eas_channels = ch;
}

void Automation::handleError()
{
    int error;
    if(serial->isOpen())
    {
        error = serial->error();
        if(!share_comport&& !error==0)
        {
            switch ( error )
            {
                case 3:
                    log_eas("eas ring error opening port");
                    break;
                default:
                    log_eas("eas ring error: " + serial->errorString() + QString::number( error ));

            }
        }
    }
}

void Automation::check_eas_ring()
{

if(!share_comport)
{
    if(ring_init <= 10)
    {
        if(serial->isOpen())
        {
            if((serial->pinoutSignals() & QSerialPort::RingIndicatorSignal))  // if eas is connected
            {
                ring_init++;
            }
            else
            {
                if(!eas_nc)
                {
                    log_eas("Ring not connected");
                    eas_nc=true;
                }
            }
        }
        //else
            //log_eas("Port not connected");
    }
    else
    {
        if(serial->isOpen())
        {
            if(!eas_ready)
            {
                eas_ready = true;
                log_eas("EAS Ring Connected Initialised");
            }
            if ( !(serial->pinoutSignals() & QSerialPort::RingIndicatorSignal) && !eas_live )
            {
                eas_live=true;
                log_eas("sensed ring");
                emit eas_ring();
            }
            else
            {
                if( (serial->pinoutSignals() & QSerialPort::RingIndicatorSignal) && eas_live )
                {
                    eas_live=false;
                    log_eas("Stop Encoder");
                    kill_ffmpeg();
                }
            }
        }
    }
 }
else
{
    bool ring;
    ring = d2mux->check_ring();
    if(ring_init <= 10)
    {
        if(ring)
            ring_init++;
    }
    else
    {
        if ( !(ring) && !eas_live )
        {
            eas_live=true;
            log_eas("sensed ring");
            emit eas_ring();
        }
        else
        {
            if( (ring) && eas_live )
            {
                eas_live=false;
                log_eas("Stop Encoder");
                kill_ffmpeg();
            }
        }
    }
}
}

void Automation::send_eas_message()
{
    log_eas("Start EAS Encode");
    capture_eas_message();
}

void Automation::send_eas_config( QList<int> channel_list )
{
    set_eas_channels(channel_list);
    d2mux->eas_insert(channel_list);
    log_eas("sent eas insert");
}

void Automation::revert_eas_config( QList<int> channel_list )
{
    set_eas_channels(channel_list);
    d2mux->revert_eas_config(channel_list);
}

void Automation::ad_splice_insert( QList<int> channel_list ,int ad_port,int ad_prog)
{
    d2mux->program_splice( channel_list ,ad_port,ad_prog);
}

void Automation::ad_splice_return_to_network( QList<int> channel_list ,int ad_port,int ad_prog)
{
    d2mux->return_from_splice( channel_list ,ad_port,ad_prog);
}
void Automation::check_ingest_dir(QString ingest_dir)
{
    QDir ingest_folder;
    QStringList files;
    ingest_folder.setCurrent(ingest_dir);
    QStringList filters;
    filters << "*.ts" << "*.ps" << ".*m2ts" << ".*mxf" << ".*mov" << ".*avi" << ".*flv" << ".*mpg" << ".*mpeg";
    files = ingest_folder.entryList(filters);
    qDebug() << "New file has arrived" << files;

}

void Automation::ingest_program(QString inputfile)
{
    QFileInfo input_info(inputfile);
    QString outputfile;
    outputfile = "Local Video/" + input_info.baseName() + ".ts";
    outputfile = QFileInfo(outputfile).absoluteFilePath();
    qDebug() << inputfile << outputfile;
    ffmpeg->Transcode(inputfile,outputfile);
    //msleep(2000);
    //ffmpeg->file_info(outputfile);
}

void Automation::capture_eas_message( )
{
    QString inputfile,outputfile;

    send_eas_config(eas_channels);

    inputfile = "./Video/ew050812-004403SD-h264lb.mov";
    inputfile = QFileInfo(inputfile).absoluteFilePath();

    outputfile = "./EAS Video/eas_";
    outputfile.append(QDateTime::currentDateTime().toString( "yyyy_MM_dd_hh_mm_ss_zzz" ));
    outputfile.append(".ts");
    outputfile = QFileInfo(outputfile).absoluteFilePath();
    log_eas("Starting Encoder");

    ffmpeg->encode(inputfile,outputfile,
                   settings.value("eas test file").toBool(),
                   settings.value("eas crossbar enable").toBool(),
                   settings.value("eas crossbar pin").toInt(),settings.value("eas video device").toString(),
                   settings.value("eas audio device").toString() , -31 );
    stream_eas( outputfile);
}

void Automation::stream_eas(QString sourcefile)
{
    QFile easfile;
    easfile.setFileName(sourcefile);
    int i=0;
    while(!easfile.open(QIODevice::ReadOnly))
    {
        msleep(500);
        qDebug("can't open file");
        if(i<=500000)
            i++;
        else
        {
            break;
        }
    }
    easfile.close();
    cue_stream(1,sourcefile);
    msleep(500);
    start_stream(1);
}

void Automation::msleep(int msec)
{
    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed()<=msec)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,msec);
    }
}

void Automation::init_mux_control()
{  
    d2mux = new Mux_Control(QHostAddress( settings.value("Mux Control Address").toString() ) ,
                            settings.value("Mux Control Port").toInt(),
                            settings.value("Mux Debug Comport").toString() ,
                            settings.value("mux_output_port").toInt() ,this);
    connect(d2mux,SIGNAL(process_debug(QString)),this,SLOT(process_mux_debug(QString)));
    connect(d2mux,SIGNAL(mux_debug_status(QString)),this,SLOT(streaming_status(QString)));
}
void Automation::streaming_status(QString string)
{
    emit stream_status(string);
}

void Automation::restart_mux_control()
{
    d2mux->~Mux_Control();
    init_mux_control();
}

void Automation::process_mux_debug(QString data)
{
    emit mux_log(data);
    //if(!data.contains( QRegExp("arp")) )
        emit mux_eas_log(data);
}

// ================================================================
void Automation::run_schedule()
{

}
void Automation::set_sat_delay(qint64 delay)
{
    sat_delay = delay;
}

void Automation::check_time()
  {
    QDateTime current_time,sat_time;
    current_time = QDateTime::currentDateTime();
    sat_time = current_time.addMSecs(sat_delay);
    int station_id_Min = 0;
    if(!station_id_loaded)
        if(sat_time.time().minute()==(station_id_Min-1)&&sat_time.time().second()==45)
        {
            qDebug("Trying to cue id file");
            cue_station_id();
            station_id_loaded=true;
        }
    if(!station_id_played)
        if(sat_time.time().minute()==station_id_Min&&sat_time.time().second()==0)
        {
            qDebug("Playing ID File");
            start_station_id();
            station_id_played=true;
        }

    if(!schedule.empty()&&state==0)
    {        
        if(sat_time >= schedule[0].play_time)
        {
            emit play(schedule[0].ip_port);
            if(schedule[0].ip_port == 2)
            {
                ad_channels = schedule[0].channels;
                ad_splice_insert(ad_channels,7,7);
            }
         // Must be last
            schedule.removeAt(0);
        }
        else
            if(sat_time >= schedule[0].play_time.addSecs(-15)
                && !isOpen)
            {
                isOpen = 1;
                if(schedule[0].ip_port==1)
                    d2mux->eas_insert(schedule[0].channels);
                emit openFile(schedule[0].ip_port,schedule[0].play_cmd);
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

void Automation::log_eas(QString logdata)
{   
    emit eas_status( (QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss:zzz ") + logdata + "\n") ) ;
}

/// Log Function
void Automation::save_log(QString log)
{
    QFile file("Schedule_and_logs/TvARP.log");  // Open file in write append text mode
    if (!file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text))
        return;
    //initiate text stream, output and close file
    QTextStream out(&file);
    out << log;
    file.close();
}

void Automation::print_log(QString log)
 {
     QFile file("Schedule_and_logs/Switcher.log");  // Open file in write append text mode
     if (!file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text))
         return;
     //initiate text stream, output and close file
     QTextStream out(&file);
     out << "\n" << log <<"\n";
     file.close();
     emit event_log_output( log  + "\n");
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
    qDebug("Loading Schedule");
    //emit event_log_output("Schedule Loaded\n");
  //Declare Variables
    sch_entry load;
    QList<QString> line_input;
    QString ch;
    QByteArray file_play;
    bool *ok;
    QString file_name="";
    QString datetime="";
    QRegExp rx("....-..-.. ..:..:.. ..	..:..*");
    //rx.setPatternSyntax(QRegExp::Wildcard);
    int name_loc=0;

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
     {  if( rx.exactMatch(line_input[c]) ) // look for valid schedule line
        {}
        else
        {
            line_input.removeAt(c);
            c--;
        }
     }
  //Load Schedule from input

    for (int j=0; j< line_input.size();j++)
    {
        load.schedule_string = line_input[j];
        datetime = line_input[j];
        datetime.truncate(22);
        load.play_time = QDateTime::fromString(datetime,"yyyy-MM-dd hh:mm:ss AP");
                                                            // "2014-10-28 12:13:30 PM"
        file_name = line_input[j];
        file_name.remove(0,38);
        name_loc = file_name.indexOf("\t");
        file_name.truncate(name_loc);
        file_play=file_name.toLocal8Bit();
        load.play_cmd = file_play;
        ch = line_input[j].at(33);
        event_log_output("scheduled on channel" + ch);
        load.channels.append(ch.toInt(ok,10));
        load.ip_port = 2;

             schedule << load;
    }
    file.close();
  // Sort Schedule in chronological order.
    qStableSort(schedule);

  // Filter bad entries out
    for(int i=0;i<schedule.size();i++)
    {
        if(QDateTime::currentDateTime() > schedule[i].play_time )
        {
            cleaned_schedule = true;
            QString output=schedule[i].play_cmd;
            output+="scheduled at ";
            output+=schedule[i].play_time.toString();
            output+=" Removed: cannot schedule in past\n";
            emit event_log_output(output);
            schedule.removeAt(i);
            i--;
        }
        else
        {
          QFile file(schedule[i].play_cmd);
               if (!file.open(QIODevice::ReadOnly))
                {
                   cleaned_schedule = true;
                   QString output=schedule[i].play_cmd;
                   output+=" does not exist";
                   emit event_log_output(output + "\n");
                   schedule.removeAt(i);
                   i--;
                }
                file.close();
        }
    }
    QList<QString> schedule_string_list;
    schedule_string_list.clear();
    for(int i=0;i<schedule.size();i++)
    {
        schedule_string_list.append(schedule[i].schedule_string);
    }
    emit show_schedule(schedule_string_list);
    // Write cleaned schedule to file
    if(cleaned_schedule)
    {
        qDebug("Writing Schedule File");
        QFile write_file(schfile);
        if (write_file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&write_file);
            for(int i=0;i<schedule.size();i++)
            {
                out<< schedule[i].schedule_string << "\n\n";
            }
            write_file.close();
        }
        else
        {
            qDebug("Couldn't open schedule file for write");
        }
        cleaned_schedule = false;
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

void Automation::log_email(QString subject, QString message)
{
    Smtp* smtp = new Smtp(settings.value("uname").toString(), settings.value("pswd").toString(),
                          settings.value("Server").toString(), settings.value("port").toInt());
    //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

   // if( !file_attachments.isEmpty() )
    //    smtp->sendMail(settings.value("uname").toString(), settings.value("email to").toString(),
    //                   subject,message, file_attachments );
    //else
    smtp->sendMail(settings.value("uname").toString(), settings.value("email to").toString(),subject,message);
}
