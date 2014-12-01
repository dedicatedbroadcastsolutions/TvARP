#include "eas.h"
#include "windows.h"
EAS::EAS(QObject *parent) :
    QObject(parent)
{
    vdev     = "USB 2861 Device";					// Set for Capture Device (Video) Windows XP/Vista
    //vdev   = "WDM 2861 Capture";					// Set for Capture Device (Video) Windows 7
    //vdev     = ""
    vidSize	 = "720x480";							// Valid "Video Resolution Mode" of Video Capture Device
    adev     = "USB Audio Device";			        // Set for Capture Device (Audio) Windows XP/Vista
    //adev   = "Line (2- USB EMP Audio Device)";			// Set for Capture Device (Audio) Windows 7
    channels.clear();
    channels.append(1);
    channels.append(2);
    channels.append(3);
    channels.append(4);
    channels.append(5);
    channels.append(6);
    channels.append(7);

    QHostAddress ctrl_addr;
    ctrl_addr.setAddress("192.168.0.150");
    qint16 ctrl_port = 0x4541;

    d2mux = new Mux_Control(ctrl_addr, ctrl_port,this);
    serial = new QSerialPort(this);
    mux_debug = new QSerialPort(this);

    eas_live=false;
    eas_test=false;
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
                SLOT(handleError()));
    connect(mux_debug, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError()));
    connect(mux_debug, SIGNAL(readyRead()),this, SLOT(process_serial_debug()));

    serial->setPortName("com6");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::HardwareControl);
    serial->open(QIODevice::ReadOnly);


    mux_debug->setPortName("com3");
    mux_debug->setBaudRate(QSerialPort::Baud115200);
    mux_debug->setDataBits(QSerialPort::Data8);
    mux_debug->setParity(QSerialPort::NoParity);
    mux_debug->setStopBits(QSerialPort::OneStop);
    mux_debug->setFlowControl(QSerialPort::NoFlowControl);
    mux_debug->open(QIODevice::ReadOnly);

    check_timer= new QTimer(this);
    connect(check_timer, SIGNAL(timeout()), this, SLOT(check_eas_ring()));  // connect timer to check_eas_ring()
    connect(this, SIGNAL(eas_ring()), this, SLOT(send_eas_message()));       // connect eas_ring() to send_eas_message()
    check_timer->start(1);                                               // create timer with 1 ms resolution

    mux_log.setFileName("./Schedule_and_logs/mux_log.txt");
    qDebug("finished eas constructor");

    /// initialise VLC
        setArgs_InitLibVlc();							     // Initialize libVLC to "conversion parameters" set by Args (Arguments)

}

EAS::~EAS()
{
    serial->close();
    mux_debug->close();
}

void EAS::handleError()
{
    qDebug()<< "serial port error" << serial->errorString() << serial->error() << "\n"
            << "mux debug port error" << mux_debug->errorString() << mux_debug->error();
}

void EAS::fake_ring()
{
    if(eas_test)
        eas_test = false;
    else
        eas_test=true;
}

void EAS::check_eas_ring()
{

    if(serial->isOpen())
    {
        //qDebug() << serial->pinoutSignals();
        if ( !(serial->pinoutSignals() & QSerialPort::RingIndicatorSignal) && !eas_live )
        {
            qDebug("sensed ring");
            //qDebug() << (serial->pinoutSignals() & QSerialPort::RingIndicatorSignal);
            //qDebug() << serial->pinoutSignals();
            emit eas_ring();
            eas_live=true;
        }
        else if( (serial->pinoutSignals() & QSerialPort::RingIndicatorSignal) && eas_live )
        {
            // stop vlc capture
            qDebug("sensed end of ring");
           // qDebug() << serial->pinoutSignals();
            eas_live=false;
            /// Stop and destroy VLC
            vlc_stop_destroy_restart();
            stream_eas_message();
        }
    }
}

void EAS::stream_eas_message()
{
    qDebug("starting vlcFix");
    process_pcr = new fix_pcr(this);
    //process_pcr->vlcFix_Send();
    process_pcr->vlcFix_Send("c:\\3ABN\\Z_vlcOutputFile.ts");
    connect(process_pcr,SIGNAL(kill_me()),process_pcr,SLOT(deleteLater()));
    qDebug(" done with vlcFix");
}

void EAS::send_eas_message()
{
    qDebug("recieving EAS Message");
    init_vlc_start_play();

    d2mux->eas_insert(channels);
    qDebug("sent eas insert");
}

void EAS::process_serial_debug()
{
    //QFile data("output.txt");
    qDebug("logging mux data");
     if (mux_log.open(QFile::WriteOnly | QFile::Append)) {
         mux_log_out.setDevice(&mux_log);
         mux_log_out << mux_debug->readAll();
         mux_log.close();
     }
}

void EAS::vlc_stop_destroy_restart()
{
    libvlc_media_player_stop (mp);
    Sleep(500);
    libvlc_media_release (m);					// Free the media (m)
    Sleep(500);
    libvlc_media_player_release (mp);			// Free the media player (mp)
    Sleep(500);
    libvlc_release (inst);						// Free the libvlc instance (inst)
    qDebug("VLC Stopped, initialising again");
    /// initialise VLC
    setArgs_InitLibVlc();							     // Initialize libVLC to "conversion parameters" set by Args (Arguments)
}

void EAS::init_vlc_start_play()
{
    /// -----Start VLC Play
       // playLocalVlcState = (int)libvlc_media_get_state (m);

        libvlc_media_player_play (mp);
        //-----Wait for VLC to reach "Play" Status = 3 (after "startVlcPlay()" is executed
       // while (playLocalVlcState != 3)
       // {											               // Wait for Play to Start (playLocalVlcState == 3)
       //     playLocalVlcState = (int)libvlc_media_get_state (m);
       // }
        //qDebug("started vlc");
    /// End Play code
}
void EAS::setArgs_InitLibVlc()
{
    dshow_vdev  = ":dshow-vdev=" + vdev;											// Set for USB Capture Device (Video)
    dshow_adev  = ":dshow-adev=" + adev;											// Set for USB Capture Device (Audio)
    dshow_size  = ":dshow-size=" + vidSize;
    vcodec		= "vcodec=mp2v,width=704,height=480,scale=1,fps=30,vb=" + vb;        // Set to fps=29.97 in vlc dlls v2.0x
    acodec		= "acodec=a52,channels=2,samplerate=48000,ab="          + ab;
    transcodeChain =	"--sout=#transcode{" +		//	--sout=#transcode{
                              vcodec + ","         +		//	vcodec=mp2v,vb=2550,width=704,height=480,scale=1,fps=30
                              acodec + "}"         +      //	acodec=a52,ab=192,channels=2,samplerate=48000}
                              ":duplicate{"        +		//	:duplicate{
                              "dst=file{"          +	    //  dst=file{
                              "mux=ts,"            +		//	mux=ts,   Output a Transport Stream
                              "dst=" + VLC_OUTPUT_FILE + "}," +  //  dst=c:\\3ABN\\vlcEASOutputFile.ts},
                              "dst=display}"	     ; 	 	//	dst=display}

    vid_title  = "--video-title=" + winTitle;
    video_x    = "--video-x="     + winX;
    video_y  = "--video-y=" + winY;
    width      = "--width="       + winWidth;
    height   = "--height="  + winHeight;

    ts_pcr       = "--sout-ts-pcr="       + pcrPid;
    ts_pid_pmt   = "--sout-ts-pid-pmt="   + pmtPid;
    ts_pid_video = "--sout-ts-pid-video=" + vidPid;
    ts_pid_audio = "--sout-ts-pid-audio=" + audPid;

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

          "--sout-ts-dts-delay=100"				// No Comma on last string (line)
    };

  //  printf ("\n  --> %s, Array Size =  %d, Size [6] = %d\n", aVlcArgs[1], sizeof (aVlcArgs), sizeof (aVlcArgs[6]) );


  //------------------------------------------ INITIALIZE LIBVLC ----------------------------------------------------

          // Initialize VLC modules, should be done only once						// (Until Released)
          inst = libvlc_new (sizeof(aVlcArgs)/sizeof(aVlcArgs[0]), aVlcArgs);		// sizeof (vlc_args)/sizeof(vlc_args[0])

          /* Create a new media item */
  //		m = libvlc_media_new_path (inst, "c:\\Downlink\\ID\\ID.mpg");           // For testing
          m = libvlc_media_new_path (inst, "dshow://");

          /* Create a media player playing environment */
          mp = libvlc_media_player_new_from_media (m);

          libvlc_media_add_option (m, ":dshow//");
  //		libvlc_media_add_option (m, "c:\\Downlink\\ID\\ID.mpg");                 // Not Needed
          libvlc_media_add_option (m, dshow_vdev.c_str());                         // dshow Video Device Name
          libvlc_media_add_option (m, dshow_size.c_str());                         // dshow Video Encode Size (720x480)
          libvlc_media_add_option (m, dshow_adev.c_str());                         // dshow Audio Device Name
}
