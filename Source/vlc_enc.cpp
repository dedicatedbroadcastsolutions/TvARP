#include "vlc_enc.h"
#include <windows.h>
VLC_ENC::VLC_ENC(QString video_device, QString audio_device, QObject *parent) :
    QObject(parent)
{
    pmtPid = "0x40";
    pcrPid = "0x44";
    vidPid = "0x44";
    audPid = "0x45";
    // CONFIG Bitrates for Output (Video and Audio)
    vb = "2550";
    ab = "192";       // in kbps; vb Video bitrate; ab Audio bitrate
    winTitle = "Local Vid (-2 Sec) PreView";
    winX     = "570";
    winY = "30";
    winWidth = "240";
    winHeight="180";  // Window Location 3

    vdev    = video_device.toStdString();
    adev    = audio_device.toStdString();

    vidSize	 = "720x480";							// Valid "Video Resolution Mode" of Video Capture Device

    setArgs_init();							     // Initialize libVLC to "conversion parameters" set by Args (Arguments)
    qDebug("VLC Initialised");
}

VLC_ENC::~VLC_ENC()
{
    qDebug("vlc stop destructor");
    libvlc_media_player_stop (mp);
    Sleep(750);
    libvlc_media_release (m);					// Free the media (m)
    Sleep(500);
    libvlc_media_player_release (mp);			// Free the media player (mp)
    Sleep(500);
    libvlc_release (inst);						// Free the libvlc instance (inst)
}

void VLC_ENC::start()
{
    /// -----Start VLC Play
        //playLocalVlcState = (int)libvlc_media_get_state (m);

        libvlc_media_player_play (mp);
        //-----Wait for VLC to reach "Play" Status = 3 (after "startVlcPlay()" is executed
        //while (playLocalVlcState != 3)
        //{											               // Wait for Play to Start (playLocalVlcState == 3)
        //    playLocalVlcState = (int)libvlc_media_get_state (m);
        //}
        //qDebug("started vlc");
    /// End Play code
    qDebug("vlc started");
}
void VLC_ENC::setArgs_init()
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
