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
