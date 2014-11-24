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
#include "eas.h"
#include "windows.h"
EAS::EAS(QObject *parent) :
    QObject(parent)
{
    pmtPid = "0x40";  pcrPid = "0x44";  vidPid = "0x44";  audPid = "0x45";

    // CONFIG Bitrates for Output (Video and Audio)
    vb = "2550";  ab = "192";                  // in kbps; vb Video bitrate; ab Audio bitrate

    //
    winTitle = "Local Vid (-2 Sec) PreView";
    winX     = "570"; winY = "30";  winWidth = "240"; winHeight="180";  // Window Location 3




    dev_machine=false;
  ///  vdev     = "USB 2861 Device";					// Set for Capture Device (Video) Windows XP/Vista
    vdev   = "WDM 2861 Capture";					// Set for Capture Device (Video) Windows 7
 ///   vidSize	 = "720x480";							// Valid "Video Resolution Mode" of Video Capture Device
       vidSize	 = "720x480";
 ///   adev     = "USB Audio Device";			        // Set for Capture Device (Audio) Windows XP/Vista
    adev   = "Line (USB EMP Audio Device)";			// Set for Capture Device (Audio) Windows 7
    channels.clear();
    channels.append(1);
    channels.append(2);
    channels.append(3);
    channels.append(4);
    channels.append(5);
    channels.append(6);
    channels.append(7);
    qDebug()<< "eas thread id = " << QThread::currentThreadId();
    QHostAddress ctrl_addr;
    ctrl_addr.setAddress("192.168.0.150");
    qint16 ctrl_port = 0x4541;

    d2mux = new Mux_Control(ctrl_addr, ctrl_port,this);
    serial = new QSerialPort(this);

    eas_live=false;
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
                SLOT(handleError()));

    serial->setPortName("com6");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadOnly);

    check_timer= new QTimer(this);
    connect(check_timer, SIGNAL(timeout()), this, SLOT(check_eas_ring()));  // connect timer to check_eas_ring()
    connect(this, SIGNAL(eas_ring()), this, SLOT(send_eas_message()));       // connect eas_ring() to send_eas_message()
    setArgs_InitLibVlc();							     // Initialize libVLC to "conversion parameters" set by Args (Arguments)

    check_timer->start(1);                      // create timer with 1 ms resolution
   // init_vlc_start_play();
    //libvlc_media_player_stop (mp);				// Stop the media player (mp)
    qDebug("finished init eas");
}

EAS::~EAS()
{
    serial->close();
}

void EAS::handleError()
{
    qDebug()<< "serial port error" << serial->errorString() << serial->error();
}

void EAS::check_eas_ring()
{
    if(serial->isOpen())
    {
        if ( !(serial->pinoutSignals() & QSerialPort::RingIndicatorSignal) && !eas_live)
        {
            qDebug("sensed ring");
            emit eas_ring();
            eas_live=true;
        }
        else if((serial->pinoutSignals() & QSerialPort::RingIndicatorSignal) && eas_live)
        {
            // stop vlc capture
            eas_live=false;
            libvlc_media_player_stop (mp);				// Stop the media player (mp)
            stream_eas_message();
            check_timer->stop();
        }
    }
    else
        qDebug("port not open");
}

void EAS::send_stream_test()
{
    QHostAddress stream_addr;
    stream_addr.setAddress("239.0.0.230");
    qint16 stream_port = 1234;
    //#define K_BIT_RATE         4000           // 5000  4400 In kbps    //2875
    stream_video = new stream(stream_addr , stream_port , 4000 , 7 , 188 , this );
    char packet[188];
    int packets_read;
    qDebug(" opening file");
    QFile file("C:\\3ABN\\ffmpeg_4000k.ts");
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug("File not opened");
    }
    else
    {
        qDebug("sending stream to test");
        //for(int i=0;packets_read>0;i++)
        packets_read=1;
        while(packets_read>0)
        {
            //qDebug("sending packet");
            packets_read  = file.read(packet,188);
            stream_video->make_udp_packet( QByteArray((char*)packet,188) );
        }
        stream_video->send_udp_packet();
    }

}

void EAS::stream_eas_message()
{

    qDebug("starting stream");
   // process_pcr = new fix_pcr(this);
    //process_pcr->vlcFix_Send();
    qDebug()<< "stream_eas_message thread id = " << QThread::currentThreadId();
    process_pcr->vlcFix_Send(VLC_OUTPUT_FILE);
    connect(process_pcr,SIGNAL(kill_me()),process_pcr,SLOT(deleteLater()));
    if(!dev_machine)
    {
        connect(process_pcr,SIGNAL(kill_me()),this,SLOT(restart_timer()));
    }
}

void EAS::send_eas_message()
{
    qDebug("recieving EAS Message");
    if(!dev_machine)
    {
        init_vlc_start_play();

    }
    qDebug("started vlc");
    d2mux->eas_insert(channels);
    //emit send_eas_config(channels);
}
void EAS::restart_timer()
{
    check_timer->start(1);
}

void EAS::process_serial_debug()
{

}
void EAS::init_vlc_start_play()
{
    /// Play code
    qDebug("play vlc");
    /// -----Start VLC Play
        playLocalVlcState = (int)libvlc_media_get_state (m);
        qDebug("libvlc media state");
        qDebug()<< playLocalVlcState;
        qDebug("libvlc_media_player_play");
        libvlc_media_player_play (mp);											       //  Play to VLC_OUTPUT_FILE set in setArgs_InitLibVlc
        qDebug("here");
       // /-----Wait for VLC to reach "Play" Status = 3 (after "startVlcPlay()" is executed
        while (playLocalVlcState != 3)
        {											               // Wait for Play to Start (playLocalVlcState == 3)
            playLocalVlcState = (int)libvlc_media_get_state (m);
        }
    /// End Play code
}
void EAS::setArgs_InitLibVlc()
{
    std::string dshow_vdev  = ":dshow-vdev=" + vdev;											// Set for USB Capture Device (Video)
    std::string dshow_adev  = ":dshow-adev=" + adev;											// Set for USB Capture Device (Audio)
    std::string dshow_size  = ":dshow-size=" + vidSize;

    std::string vcodec		= "vcodec=mp2v,width=704,height=480,scale=1,fps=30,vb=" + vb;        // Set to fps=29.97 in vlc dlls v2.0x
    std::string acodec		= "acodec=a52,channels=2,samplerate=48000,ab="          + ab;
    std::string transcodeChain =	"--sout=#transcode{" +		//	--sout=#transcode{
                              vcodec + ","         +		//	vcodec=mp2v,vb=2550,width=704,height=480,scale=1,fps=30
                              acodec + "}"         +      //	acodec=a52,ab=192,channels=2,samplerate=48000}
                              ":duplicate{"        +		//	:duplicate{
                              "dst=file{"          +	    //  dst=file{
                              "mux=ts,"            +		//	mux=ts,   Output a Transport Stream
                              "dst=" + VLC_OUTPUT_FILE + "}," +  //  dst=c:\\3ABN\\vlcEASOutputFile.ts},
                              "dst=display}"	     ; 	 	//	dst=display}

    std::string vid_title  = "--video-title=" + winTitle;
    std::string video_x    = "--video-x="     + winX,       video_y  = "--video-y=" + winY;
    std::string width      = "--width="       + winWidth,   height   = "--height="  + winHeight;

    std::string ts_pcr       = "--sout-ts-pcr="       + pcrPid;
    std::string ts_pid_pmt   = "--sout-ts-pid-pmt="   + pmtPid;
    std::string ts_pid_video = "--sout-ts-pid-video=" + vidPid;
    std::string ts_pid_audio = "--sout-ts-pid-audio=" + audPid;

    const char * const aVlcArgs[] = {
          "--plugin-path=c:\\Downlink\\APPs\\plugins",
          "--no-video-title-show",                // Inhibit File Name Shown on VLC
          "--verbose=0",
          transcodeChain.c_str(),

          vid_title.c_str(),						// "--video-title = EAS Slates"
          video_x.c_str(),  video_y.c_str(),		// "--video-x=",  "--video-y=",
          width.c_str(),    height.c_str(),		// "--width="  ,  "--height=" ,

  //		ts_pcr.c_str(),							// "--sout-ts-pcr=0x44",
          ts_pid_pmt.c_str(),						// "--sout-ts-pid-pmt=0x40",
          ts_pid_video.c_str(),					// "--sout-ts-pid-video=0x44",
          ts_pid_audio.c_str(),					// "--sout-ts-pid-audio=0x45",
    };

          // Initialize VLC modules, should be done only once						// (Until Released)
          inst = libvlc_new (sizeof(aVlcArgs)/sizeof(aVlcArgs[0]), aVlcArgs);		// sizeof (vlc_args)/sizeof(vlc_args[0])

        ///  Create a new media item
          m = libvlc_media_new_path (inst, "dshow://");

       //    Create a media player playing environment
          mp = libvlc_media_player_new_from_media (m);

          libvlc_media_add_option (m, ":dshow//");
          libvlc_media_add_option (m, dshow_vdev.c_str());                         // dshow Video Device Name
          libvlc_media_add_option (m, dshow_size.c_str());                         // dshow Video Encode Size (720x480)
          libvlc_media_add_option (m, dshow_adev.c_str());                         // dshow Audio Device Name
    qDebug("set vlc init");
}
