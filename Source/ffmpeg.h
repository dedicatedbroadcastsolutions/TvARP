#ifndef FFmpeg_H
#define FFmpeg_H

#include <QtCore>
#include <QMessageBox>


class FFmpeg : public QObject
{
    Q_OBJECT

  public:
    explicit FFmpeg( QObject *parent);
    ~FFmpeg();

  public slots:
    void encode(QString inputfile, QString outputfile, bool capture, bool crossbar, int crossbar_pin, QString vdev, QString adev, int dialnorm);
    void ffplay(QString inputfile);
    int file_info(QString inputfile);
    void Transcode(QString infile,QString outfile);
    void kill();
    void close();
    void close_encoder();
    void kill_encoder();
  signals:
    void ffmpeg_finished( bool );
    void ffmpeg_status( QString );
    void ffmpeg_stdout(QString);
    void encode_started();
    void ffplay_stdout(QString);
    void analysis_stdout_display(QString);
    void transcode_stdout_display(QString);

  private slots:
     void readyReadStandardOutput();
     void processStarted();
     void ffplay_processStarted();
     void readyread_ffplay();
     void playFinished();
     void encodingFinished();
     void analysis_started();
     void analysis_finished();
     void analysis_stdout();
     void transcode_stdout(QString);
     void log(QString logdata);
     void log_ffmpeg_stdout(QString logdata);
     void transcode_processStarted();
     void readyread_transcode();
     void TranscodeFinished();
  private:
    QProcess *mEncodingProcess;
    QProcess *mTranscodingProcess;
    QProcess *mInputPlayProcess;
    QProcess *mFileInfoProcess;
    QString mOutputString;
    QString encode_fileName;
    bool encoding;
    int FileInfo_bitrate;

};


#endif // FFmpeg_H
