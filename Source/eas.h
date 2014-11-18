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
#ifndef EAS_H
#define EAS_H

#include "QtCore"
#include <QSerialPort>
#include <string>
//#include "vlc/vlc.h"            // Must include VLC core first (From VLC .zip version 1.1.0)
//#include "fix_pcr.h"
#include "mux_control.h"
#include "stream.h"
//#include "qt_ffmpeg_enc.h"

class EAS : public QObject
{
    Q_OBJECT

  public:
    explicit EAS( QObject *parent = 0);
    ~EAS();
    bool eas_live;

  public slots:
    void send_eas_message();
    void check_eas_ring();
    void handleError();
    void process_serial_debug();
    void init_vlc_start_play();
    void setArgs_InitLibVlc();
    void stream_eas_message();
    void restart_timer();
    void send_stream_test();
  signals:
    void eas_ring();
    void send_eas_config(QList<int>);
    void start_send();
    void eas_log_output(QString);
  private:
    bool dev_machine;
    Mux_Control *d2mux;
  //  fix_pcr *process_pcr;
    QTimer *check_timer;
    QList<int> channels;
    QSerialPort *serial;
    stream *stream_video;
    //int  playLocalVlcState;
    // CONFIG PIDs
   // std::string pmtPid ,  pcrPid ,  vidPid,  audPid;

    // CONFIG Bitrates for Output (Video and Audio)
   // std::string vb,  ab ;                  // in kbps; vb Video bitrate; ab Audio bitrate

    //
    //std::string winTitle;
   // std::string winX , winY ,  winWidth , winHeight;  // Window Location 3

    // "Initialize libVLC" Variables
 //   libvlc_instance_t     *inst;
 //   libvlc_media_player_t *mp;
 //   libvlc_media_t        *m;
  //  #define VLC_OUTPUT_FILE			"c:\\3ABN\\Z_vlcOutputFile.ts"
  //  std::string vdev;									// Set for USB Capture Device (Video)
 //   std::string vidSize;									// Valid "Video Resolution Mode" of Video Capture Device
  //  std::string adev ;									// Set for USB Capture Device (Audio)
};

#endif // EAS_H
