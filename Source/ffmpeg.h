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
    void encode(QString inputfile, QString outputfile, bool eas, bool crossbar, int crossbar_pin, QString vdev, QString adev);
    void ffplay(QString inputfile);
    void kill();
  signals:
    void ffmpeg_finished( bool );
    void ffmpeg_status( QString );
    void ffmpeg_stdout(QString);
    void encode_started();
    void ffplay_stdout(QString);
  private slots:
     void readyReadStandardOutput();
     void processStarted();
     void ffplay_processStarted();
     void readyread_ffplay();
     void playFinished();
     void encodingFinished();
     void log(QString logdata);
     void log_ffmpeg_stdout(QString logdata);
  private:
    QProcess *mTranscodingProcess;
    QProcess *mInputPlayProcess;
    QProcess *mOutputPlayProcess;
    QString mOutputString;
    QString encode_fileName;

};


#endif // FFmpeg_H
