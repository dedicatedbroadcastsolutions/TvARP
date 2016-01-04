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
#include "smtp.h"
#include "mux_control.h"
#include "stream.h"
#include "ffmpeg.h"

struct sch_entry
{
    bool operator<(const sch_entry& other) const {
        return play_time < other.play_time; // sort by play_time
    }
    QByteArray play_cmd;
    QDateTime play_time;
    int ip_port;
    QList<int> channels;
    QString schedule_string;
};

class Automation : public QObject
{
    Q_OBJECT
public:
    explicit Automation(QObject *parent = 0);
    ~Automation();
    void run_schedule();
    void stream_file(QString ts_file,QHostAddress address,quint16 port);
    QList<QString> check_schedule();
    void load_config();
    int comport;
    bool share_comport;
    bool visible;
    QTimer *timer;
    int state,isOpen;
    bool show_vmon;
    QString audio_dev ;
    QString video_dev ;
    QList<int> eas_channels;
    QList<int> id_channels;
    QList<int> ad_channels;
    int mux_out_port ;
    //TS_Info *ad_ts;
public slots:
    // mux control slots

    void send_eas_config( QList<int> channel_list );
    void revert_eas_config( QList<int> channel_list );
    void ad_splice_insert(QList<int> channel_list , int ad_port, int ad_prog);
    void ad_splice_return_to_network( QList<int> channel_list ,int ad_port,int ad_prog);
    void process_mux_debug(QString data);
    void init_mux_control();
    void restart_mux_control();
    void kill_ffmpeg();
    void start_stream(int ip_port);
    void cue_stream(int ip_port,QString sourcefile);
    void restart_eas_engine();
    void init_ring_detect();
    void close_ring_detect();
    void handleError();
    void check_eas_ring();
    void capture_eas_message();
    void send_eas_message();
    void check_time();
    void video_state(int);
    void stream_eas(QString sourcefile);
    void is_open(bool);
    void set_eas_channels(QList<int> ch);
    void set_id_channels(QList<int> ch);
    void encoder_output(QString output);
    void get_bitrate(QString filename);
    void streaming_status( QString string );
    void encoder_finished(bool state);
    void ingest_display(QString string);
    void ingest_program(QString inputfile);
    void ingest_cancel();
    void kill_ts_info();
    void cue_station_id();
    void start_station_id();
    void load_schedule(QString schfile);
    void log_email(QString subject,QString message);
    void done_streaming(int ip_port);
    void done_with_file(int port);
    void msleep(int msec);
    void clear_stream(int ip_port);
    void transcode_finished();
    void check_ingest_dir(QString ingest_dir);
signals:
    void show_schedule(QList<QString>);
    void encoder_done();
    void init();
    void bitrate(int bitrate);
    void event_log_output(QString);
    void play(int port);
    void openFile(int , QString);
    void get_video_state();
    void mux_eas_log(QString);
    void mux_log(QString);
    void eas_ring();
    void encoder_display(QString);
    void eas_status(QString);
    void stream_status(QString);
    void ingest_disp(QString);
    void ingest_finished();

private:
    Mux_Control *d2mux;
    QSerialPort *serial;
    stream *mpeg_stream;
    FFmpeg *ffmpeg;
    bool eas_test;
    bool eas_live;
    QTimer *check_timer;
    QTimer *load_sch;
    QFileSystemWatcher watcher;
    int ring_init;
    QList <sch_entry> schedule;  // List that contains the event schedule
    bool ad;
    bool eas_nc;
    bool eas_ready;
    bool eas_np;
    bool cleaned_schedule;
    bool station_id_loaded,station_id_played;
    QString video_watch_dir;
private slots:
    void log_eas(QString logdata);
    void print_log(QString log);
    void log_channel(int channel,QDateTime DateTime);
    void log_playback(QString message,QString file,QDateTime DateTime);
    void save_log(QString log);

};

#endif // AUTOMATION_H
