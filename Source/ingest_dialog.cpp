// dialog.cpp

#include "ingest_dialog.h"
#include "ui_ingest_dialog.h"
#include <QDebug>
#include <QString>
#include <QProcess>
#include <QScrollBar>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QUdpSocket>
 #include <QElapsedTimer>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // Play button for output - initially disabled
    ui->playOutputButton->setEnabled(false);

    ffmpeg = new FFmpeg(this);
    connect(ffmpeg,SIGNAL(ffmpeg_stdout(QString)),this,SLOT(display_stdout(QString)));
    connect(ffmpeg,SIGNAL(transcode_status(int,QString)),this,SLOT(encodingFinished(int,QString)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::processStarted()
{
    qDebug() << "processStarted()";
}

// conversion start
void Dialog::on_startButton_clicked()
{
    QString inputfile,outputfile;
    inputfile = ui->fromLineEdit->text();
    outputfile = ui->toLineEdit->text();

    if(inputfile.isEmpty()) {
        qDebug() << "No input";
        QMessageBox::information(this,
                     tr("ffmpeg"),tr("Input file not specified"));
        return;
    }
    if(outputfile.isEmpty()) {
        qDebug() << "No output";
        QMessageBox::information(this,
                     tr("ffmpeg"),tr("Output file not specified"));
        return;
    }
    if (QFile::exists(outputfile)) {
         if (QMessageBox::question(this, tr("ffmpeg"),
                    tr("There already exists a file called %1 in "
                    "the current directory. Overwrite?").arg(outputfile),
                    QMessageBox::Yes|QMessageBox::No, QMessageBox::No)
             == QMessageBox::No)
             return;
         QFile::remove(outputfile);
         while(QFile::exists(outputfile)) {
             qDebug() << "output file still there";
         }
     }

    ffmpeg->encode(inputfile,outputfile);
}

void Dialog::display_stdout(QString ffmpeg_stdout)
{
    mOutputString.append(ffmpeg_stdout);
    ui->textEdit->setText(mOutputString);
    // put the slider at the bottom
    ui->textEdit->verticalScrollBar()
            ->setSliderPosition(
                ui->textEdit->verticalScrollBar()->maximum());
}

void Dialog::encodingFinished(int encode_status,QString transcode_status)
{
    ui->transcodingStatusLabel->setText(transcode_status);
    if (encode_status)
    {
        qDebug("encode_status is true");
        ui->playOutputButton->setEnabled(true);
    }
}

// Browse... button clicked - this is for input file
void Dialog::on_fileOpenButton_clicked()
{
    QString fileName =
        QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C:/TEST",
                tr("videoss (*.mp4 *.mov *.avi *.mpg *.ts)"));
    if (!fileName.isEmpty()) {
        ui->fromLineEdit->setText(fileName);
    }
}

void Dialog::on_playInputButton_clicked()
{
    QString input = ui->fromLineEdit->text();
    ffmpeg->ffplay(input);
}

void Dialog::on_playOutputButton_clicked()
{
    QString output = ui->toLineEdit->text();
    ffmpeg->ffplay(output);
}
