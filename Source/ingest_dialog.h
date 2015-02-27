// ingest_dialog.h

#ifndef DIALOG_H
#define DIALOG_H
#include "ffmpeg.h"
#include <QDialog>
#include <QProcess>
#include <QFile>
#include <QTextEdit>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:

public:

private slots:
     void on_startButton_clicked();
     void display_stdout(QString ffmpeg_stdout);
     void processStarted();
     void encodingFinished(QString transcode_status);
     void enable_output_play_button(bool status);
     void on_fileOpenButton_clicked();
     void on_playInputButton_clicked();
     void on_playOutputButton_clicked();

private:
    Ui::Dialog *ui;
    FFmpeg *ffmpeg;
    QString mOutputString;

};

#endif // DIALOG_H
