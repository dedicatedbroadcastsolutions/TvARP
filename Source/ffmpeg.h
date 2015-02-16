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
    void encode(QString inputfile,QString outputfile);
    void ffplay(QString inputfile);
  signals:
    void transcode_status( int , QString );
    void ffmpeg_stdout(QString);
    void encode_started();
  private slots:
     void readyReadStandardOutput();
     void processStarted();
     void encodingFinished();
  private:
    QProcess *mTranscodingProcess;
    QProcess *mInputPlayProcess;
    QProcess *mOutputPlayProcess;
    QString mOutputString;
    QString encode_fileName;

};


#endif // FFmpeg_H
