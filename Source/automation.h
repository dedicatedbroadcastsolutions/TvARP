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
#include "mux_control.h"
#include "fix_pcr.h"
#include "vlc_enc.h"
//#include "vlc/vlc.h"            // Must include VLC core first (From VLC .zip version 1.1.0)
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
    ~Automation();
    void run_schedule();
    void load_schedule(QString schfile);
    QList<QString> check_schedule();
    void load_config();
    int comport;
    bool visible;
    QTimer *timer;
    int state,isOpen;

    QString audio_dev ;
    QString video_dev ;
    QList<int> channels;

    int mux_out_port ;
public slots:
    // mux control slots
    void send_eas_config( QList<int> channel_list );
    void revert_eas_config( QList<int> channel_list );
    void ad_splice_insert( QList<int> channel_list );
    void ad_splice_return_to_network( QList<int> channel_list );
    void process_mux_debug(QString data);
    void init_mux_control();
    void restart_mux_control();
    void restart_eas_engine();
    void init_ring_detect();
    void close_ring_detect();
    void handleError();
    void check_eas_ring();
    void stream_eas_message();
    void send_eas_message();
    void init_vlc();
    void restart_vlc();
    void start_vlc();
    void check_time();
    void video_state(int);
    void print_log(QString log);
    void log_channel(int channel,QDateTime DateTime);
    void is_open(bool);
    void log_playback(QString message,QString file,QDateTime DateTime);
signals:
    void event_log_output(QString);
    void play();
    void openFile(QString);
    void get_video_state();
    void mux_eas_log(QString);
    void eas_ring();
private:
    Mux_Control *d2mux;
    QSerialPort *serial;
    bool eas_test;
    bool eas_live;
    fix_pcr *process_pcr;
    QTimer *check_timer;
    VLC_ENC *vlc_enc;
};

#endif // AUTOMATION_H
