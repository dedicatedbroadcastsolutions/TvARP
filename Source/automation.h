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
#ifndef AUTOMATION_H
#define AUTOMATION_H
#include "QtCore"
//#include "video_window.h"
//#include "switcher.h"
struct sch_entry
{
    bool operator<(const sch_entry& other) const {
        return play_time < other.play_time; // sort by play_time
    }
    QByteArray play_cmd;
    QDateTime play_time;
};

class Automation : public QObject
{
    Q_OBJECT
public:
    explicit Automation(QObject *parent = 0);
    void run_schedule();
    void load_schedule(QString schfile);
    QList<QString> check_schedule();
    void load_config();
    int comport;
    bool visible;
    QTimer *timer;
    int state,isOpen;
public slots:
    void check_time();
    void video_state(int);
    void print_log(QString log);
    void log_channel(int channel,QDateTime DateTime);
    void is_open(bool);
    void log_playback(QString message,QString file,QDateTime DateTime);
signals:
    void event_log_output(QString new_event);
    void play();
    void openFile(QString);
    void get_video_state();

private:


};

#endif // AUTOMATION_H
