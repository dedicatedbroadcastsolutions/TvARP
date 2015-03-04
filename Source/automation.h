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
#include "stream.h"
#include "ts_info.h"
#include "ffmpeg.h"
//#include "fix_pcr.h"
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
    bool show_vmon;
    QString audio_dev ;
    QString video_dev ;
    QList<int> channels;

    int mux_out_port ;
    TS_Info *ad_ts;
public slots:
    // mux control slots
    void send_eas_config( QList<int> channel_list );
    void revert_eas_config( QList<int> channel_list );
    void ad_splice_insert( QList<int> channel_list );
    void ad_splice_return_to_network( QList<int> channel_list );
    void process_mux_debug(QString data);
    void init_mux_control();
    void restart_mux_control();
    void kill_ffmpeg();
    void start_stream(QHostAddress stream_addr, quint16, QString sourcefile);
    void restart_eas_engine();
    void init_ring_detect();
    void close_ring_detect();
    void handleError();
    void check_eas_ring();
    void capture_eas_message();
    void send_eas_message();
    void check_time();
    void video_state(int);

    void is_open(bool);

    void encoder_output(QString output);
    void get_bitrate(QString filename);
    void streaming_status( QString string );
    void encoder_finished(bool state);
    void ingest_display(QString string);
    void ingest_program(QString inputfile);
    void kill_ts_info();
signals:
    void encoder_done();
    void init();
    void bitrate(int bitrate);
    void event_log_output(QString);
    void play();
    void openFile(QString);
    void get_video_state();
    void mux_eas_log(QString);
    void mux_log(QString);
    void eas_ring();
    void encoder_display(QString);
    void eas_status(QString);
    void stream_status(QString);
    void stream_eas(QHostAddress stream_addr, quint16, QString sourcefile);
    void ingest_disp(QString);

private:
    Mux_Control *d2mux;
    QSerialPort *serial;
    stream *mpeg_stream;
    FFmpeg *ffmpeg;
    bool eas_test;
    bool eas_live;
    QTimer *check_timer;
    int ring_init;
private slots:
    void log_eas(QString logdata);
    void print_log(QString log);
    void log_channel(int channel,QDateTime DateTime);
    void log_playback(QString message,QString file,QDateTime DateTime);
    void save_log(QString log);
};

#endif // AUTOMATION_H
