#include "ffmpeg.h"

FFmpeg::FFmpeg( QObject *parent) :
    QObject(parent)
{
    mInputPlayProcess = new QProcess(this);
    mOutputPlayProcess = new QProcess(this);
    mTranscodingProcess = new QProcess(this);
    connect(mTranscodingProcess, SIGNAL(started()), this, SLOT(processStarted()));
    connect(mTranscodingProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(readyReadStandardOutput()));
    connect(mTranscodingProcess, SIGNAL(finished(int)), this, SLOT(encodingFinished()));
}

FFmpeg::~FFmpeg()
{

}

void FFmpeg::processStarted()
{
    emit encode_started();
}

void FFmpeg::encode(QString inputfile,QString outputfile)
{
    QString program = "C:/Users/Zach/Development/ffmpeg-20150124-git-1f13348-win64-static/bin/ffmpeg.exe";
    encode_fileName = outputfile;
    QStringList arguments;

    arguments.clear();
    arguments << "-v" << "9" << "-loglevel" << "99" //<< "-re"
    << "-i" << inputfile

    << "-f" << "mpegts"
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
    << "-threads" << "0"
    << outputfile;

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
        qDebug("encoding successful");
        emit transcode_status(1,"Transcoding Status: Successful!");
    }
    else
    {
        qDebug("encoding failed");
        emit transcode_status(0,"Transcoding Status: Failed!");
    }
}

void FFmpeg::ffplay(QString inputfile)
{
    QString program = "C://Users/Zach/Development/ffmpeg-20150124-git-1f13348-win64-static/bin/ffplay.exe";
    QStringList arguments;
    arguments << inputfile;
    mInputPlayProcess->start(program, arguments);
}
