#ifndef EAS_H
#define EAS_H

#include "QtCore"
#include <QSerialPort>
#include <string>
#include "vlc/vlc.h"            // Must include VLC core first (From VLC .zip version 1.1.0)
#include "fix_pcr.h"
#include "mux_control.h"

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
    void fake_ring();
  signals:
    void eas_ring();
    void send_eas_config(QList<int>);
    void start_send();
    void eas_log_output(QString);
  private:
    Mux_Control *d2mux;
    fix_pcr *process_pcr;
    QTimer *check_timer;
    QList<int> channels;
    QSerialPort *serial, *mux_debug;
    QFile mux_log;
    QTextStream mux_log_out;
    bool eas_test;
    int  playLocalVlcState;
    // CONFIG PIDs
    std::string pmtPid = "0x40",  pcrPid = "0x44",  vidPid = "0x44",  audPid = "0x45";
    // CONFIG Bitrates for Output (Video and Audio)
    std::string vb = "2550",  ab = "192";                  // in kbps; vb Video bitrate; ab Audio bitrate
    //
    std::string winTitle = "Local Vid (-2 Sec) PreView";
    std::string winX     = "570", winY = "30",  winWidth = "240", winHeight="180";  // Window Location 3
    // "Initialize libVLC" Variables
    libvlc_instance_t     *inst;
    libvlc_media_player_t *mp;
    libvlc_media_t        *m;
    #define VLC_OUTPUT_FILE			"c:\\3ABN\\Z_vlcOutputFile.ts"
    std::string vdev    = "";									// Set for USB Capture Device (Video)
    std::string vidSize = "";									// Valid "Video Resolution Mode" of Video Capture Device
    std::string adev    = "";									// Set for USB Capture Device (Audio)
};

#endif // EAS_H
