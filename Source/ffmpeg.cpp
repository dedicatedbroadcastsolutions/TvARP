#include "ffmpeg.h"

FFmpeg::FFmpeg( QObject *parent) :
    QObject(parent)
{
    mInputPlayProcess = new QProcess(this);
    //mOutputPlayProcess = new QProcess(this);
    mTranscodingProcess = new QProcess(this);
    connect(mTranscodingProcess, SIGNAL(started()), this, SLOT(processStarted()));
    connect(mTranscodingProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(readyReadStandardOutput()));
    connect(mTranscodingProcess, SIGNAL(finished(int)), this, SLOT(encodingFinished()));

    connect(mInputPlayProcess, SIGNAL(started()), this, SLOT(ffplay_processStarted()));
    connect(mInputPlayProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(readyread_ffplay()));
    connect(mInputPlayProcess, SIGNAL(finished(int)), this, SLOT(playFinished()));
}

FFmpeg::~FFmpeg()
{
    kill();
}

void FFmpeg::playFinished()
{
    emit ffmpeg_status(QDateTime::currentDateTime().toString("yyyy:mm:dd:ss") + "  "+"play finished\n");
}

void FFmpeg::ffplay_processStarted()
{
    emit ffmpeg_status(QDateTime::currentDateTime().toString("yyyy:mm:dd:ss") + "  "+"ffplay process started\n");
}

void FFmpeg::readyread_ffplay()
{
    emit ffplay_stdout(mInputPlayProcess->readAllStandardOutput());
}

void FFmpeg::kill()
{
    mInputPlayProcess->kill();
    mInputPlayProcess->waitForFinished();
    mTranscodingProcess->kill();
    mTranscodingProcess->waitForFinished();
    qDebug("transcode processes finished");
}

void FFmpeg::processStarted()
{
    emit encode_started();
}

void FFmpeg::encode(QString inputfile,QString outputfile, bool test,bool crossbar,int crossbar_pin,QString vdev,QString adev)
{
    QString program;
    program = "./FFmpeg/bin/ffmpeg.exe";
    program = QFileInfo(program).absoluteFilePath();
    encode_fileName = outputfile;
    QStringList arguments;

    arguments.clear();
    //arguments << "-v" << "9" << "-loglevel" << "99" ;
    arguments  << "-re" << "-rtbufsize" << "100000k";

    if(!test)
    {
        arguments <<"-f" << "dshow" ;
        if(crossbar)
            arguments <<"-crossbar_video_input_pin_number" << QString::number(crossbar_pin);

        arguments << "-i" << ( "video=" + vdev + ":audio=" + adev );
    }
    else
        arguments << "-i" << inputfile;       // to read from a file

    arguments << "-f" << "mpegts"
    << "-muxrate" << "4000k"
    << "-mpegts_transport_stream_id" << "8471"
    << "-metadata" << "service_provider=\"K33EJ-D\""

    << "-vf" << "fps=29.97,scale=704x480"
    << "-vcodec" << "mpeg2video"
    << "-b:v" << "2000k"
    << "-pix_fmt" << "yuv420p"

    << "-acodec" <<"ac3"
    << "-af" << "pan=stereo|c0=c0|c1=c1"
    << "-ar" << "48000" << "-b:a" << "120k"

    << "-mpegts_pmt_start_pid" <<  "0x40"
    << "-mpegts_start_pid" << "0x44"
    << "-metadata" << "service_name=\"Local\""
    << "-mpegts_service_id" << "1"
    << "-mpegts_original_network_id" << "7654"
    << "-tables_version" << "10"
    << "-threads" << "1"
    << outputfile;

    qDebug()<< arguments;
    mTranscodingProcess->setProcessChannelMode(QProcess::MergedChannels);
    mTranscodingProcess->start(program, arguments);
}

void FFmpeg::readyReadStandardOutput()
{
    emit ffmpeg_stdout(mTranscodingProcess->readAllStandardOutput());
}

void FFmpeg::encodingFinished()
{
    if (QFile::exists(encode_fileName))
    {
        emit ffmpeg_finished( true );
        emit ffmpeg_status(QDateTime::currentDateTime().toString("yyyy:mm:dd:ss")+ "  " +"Transcoding Status: Successful! \n");
    }
    else
    {
        emit ffmpeg_finished( false );
        emit ffmpeg_status( QDateTime::currentDateTime().toString("yyyy:mm:dd:ss")+ "  " +"Transcoding Status: Failed! \n");
    }
}

void FFmpeg::ffplay(QString inputfile)
{
    QString program;
    program = "./FFmpeg/bin/ffplay.exe";
    program = QFileInfo(program).absoluteFilePath();
    QStringList arguments;
    //arguments << "video_size" << "172x120";

    arguments << inputfile;

    emit ffmpeg_status( (QDateTime::currentDateTime().toString("yyyy:mm:dd:ss") + "  "+ "FFplay " + inputfile + "\n" ));
    if(mInputPlayProcess->state()==0)
        mInputPlayProcess->start(program, arguments);
}
