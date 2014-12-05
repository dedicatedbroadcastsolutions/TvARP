#ifndef VLC_ENC_H
#define VLC_ENC_H
# include "vlc/vlc.h"
#include "QtCore"

class VLC_ENC : public QObject
{
    Q_OBJECT

  public:
    explicit VLC_ENC(QString video_device,QString audio_device, QObject *parent);
    ~VLC_ENC();

  public slots:
    void start();
    void setArgs_init();

  signals:

  private:
    /// VLC Variables
        int  playLocalVlcState;

     // "Initialize libVLC" Variables
        libvlc_instance_t     *inst;
        libvlc_media_player_t *mp;
        libvlc_media_t        *m;
        #define VLC_OUTPUT_FILE			"c:\\3ABN\\Z_vlcOutputFile.ts"
     // VLC Argument Initialisers
        // CONFIG PIDs
        std::string pmtPid ,  pcrPid ,  vidPid ,  audPid ;
        // CONFIG Bitrates for Output (Video and Audio)
        std::string vb ,  ab ;                  // in kbps; vb Video bitrate; ab Audio bitrate
        std::string winTitle;
        std::string winX , winY ,  winWidth , winHeight;  // Window Location 3

        std::string vdev;									// Set for USB Capture Device (Video)
        std::string vidSize;									// Valid "Video Resolution Mode" of Video Capture Device
        std::string adev;									// Set for USB Capture Device (Audio)
        std::string dshow_vdev;
        std::string dshow_adev;
        std::string dshow_size ;
        std::string vcodec	;
        std::string acodec;
        std::string transcodeChain;
        std::string vid_title;
        std::string video_x, video_y ;
        std::string width , height;
        std::string ts_pcr ;
        std::string ts_pid_pmt;
        std::string ts_pid_video , ts_pid_audio;
};


#endif // VLC_ENC
