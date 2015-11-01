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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int maxblock = 250;
    readSettings();

    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

    automation = new Automation(this);
    ad_ch.clear();
    ad_ch.append(ui->comboBox->currentIndex()+1);
    eas_ch.clear();
    eas_ch.append(1);
    eas_ch.append(2);
    eas_ch.append(3);
    eas_ch.append(4);
    eas_ch.append(5);
    eas_ch.append(6);
    eas_ch.append(7);
    id_ch.clear();
    id_ch.append(1);
    id_ch.append(2);
    id_ch.append(3);
    id_ch.append(4);
    id_ch.append(5);
    id_ch.append(6);
    id_ch.append(7);
    ui->mux_log_display->ensureCursorVisible();
    ui->mux_log_display->moveCursor(QTextCursor::End);
    ui->mux_log_display->verticalScrollBar()->setValue( ui->mux_log_display->verticalScrollBar()->maximum() );

    ui->mux_log_display_2->ensureCursorVisible();
    ui->mux_log_display_2->moveCursor(QTextCursor::End);
    ui->mux_log_display_2->verticalScrollBar()->setValue( ui->mux_log_display_2->verticalScrollBar()->maximum() );

    ui->event_log_display->ensureCursorVisible();
    ui->event_log_display->moveCursor(QTextCursor::End);
    ui->event_log_display->verticalScrollBar()->setValue( ui->event_log_display->verticalScrollBar()->maximum() );

    ui->encoder_display->ensureCursorVisible();
    ui->encoder_display->moveCursor(QTextCursor::End);
    ui->encoder_display->verticalScrollBar()->setValue( ui->encoder_display->verticalScrollBar()->maximum() );
    connect(automation,SIGNAL(encoder_display(QString)),ui->encoder_display,SLOT(insertPlainText(QString)));


    ui->eas_detect->ensureCursorVisible();
    ui->eas_detect->moveCursor(QTextCursor::End);
    ui->eas_detect->verticalScrollBar()->setValue( ui->eas_detect->verticalScrollBar()->maximum() );
    connect(automation,SIGNAL(eas_status(QString)),ui->stream_status_display,SLOT(insertPlainText(QString)));

    ui->ingest_display->ensureCursorVisible();
    ui->ingest_display->moveCursor(QTextCursor::End);
    ui->ingest_display->verticalScrollBar()->setValue( ui->ingest_display->verticalScrollBar()->maximum() );
    connect(automation,SIGNAL(ingest_disp(QString)),ui->ingest_display,SLOT(insertPlainText(QString)));

    ui->stream_status_display->ensureCursorVisible();
    ui->stream_status_display->moveCursor(QTextCursor::End);
    ui->stream_status_display->verticalScrollBar()->setValue( ui->stream_status_display->verticalScrollBar()->maximum() );

    QTextDocument * doc = ui->mux_log_display->document();
    doc->setMaximumBlockCount(maxblock);
    connect(automation,SIGNAL(mux_eas_log(QString)),ui->mux_log_display,SLOT( insertPlainText(QString) ) );
    connect(automation,SIGNAL(mux_log(QString)),ui->mux_log_display_2,SLOT( insertPlainText(QString) ) );
    connect(automation,SIGNAL(event_log_output(QString)),ui->event_log_display,SLOT(insertPlainText(QString)));
    connect(automation,SIGNAL(stream_status(QString)),ui->stream_status_display,SLOT(insertPlainText(QString)));
    automation->restart_eas_engine();
    ///automation->restart_mux_control();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::browse()
{
    file_attachments.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        file_attachments = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, file_attachments)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}

void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !file_attachments.isEmpty() )
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), file_attachments );
    else
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}


void MainWindow::on_actionStart_Minimized_toggled(bool visible)
{
    settings.setValue("visible", visible);
}

void MainWindow::readSettings()
{


    ui->actionStart_Minimized->setChecked(settings.value("visible").toBool());

    if( settings.contains("ID File"))
        ui->station_id_filename->setText(settings.value("ID File").toString());
    else
        ui->station_id_filename->setText("station_id.ts");

    if( settings.contains("mux_output_port") )
        ui->mux_out_port->setCurrentIndex(settings.value("mux_output_port").toInt());
    else
        settings.setValue("mux_output_port", ui->mux_out_port->currentIndex() );

    if( settings.contains("Mux Control Address") )
        ui->mux_ctrl_addr->setText( settings.value("Mux Control Address").toString() );
    else
        settings.setValue("Mux Control Address", ui->mux_ctrl_addr->text() );

    if( settings.contains("Mux Control Port") )
        ui->mux_ctrl_port->setValue( settings.value("Mux Control Port").toInt() );
    else
        settings.setValue("Mux Control Port", ui->mux_ctrl_port->value());

    if( settings.contains("Mux Debug Comport") )
        ui->mux_debug_comport->setCurrentText( settings.value("Mux Debug Comport").toString() );
    else
        settings.setValue("Mux Debug Comport", ui->mux_debug_comport->currentText());

    if( settings.contains("eas crossbar enable") )
        ui->crossbar_enable->setChecked( settings.value("eas crossbar enable").toBool() );
    else
    settings.setValue( "eas crossbar enable" , ui->crossbar_enable->isChecked());

    if( settings.contains("eas crossbar pin") )
        ui->crossbar_pin->setValue( settings.value("eas crossbar pin").toInt() );
    else
    settings.setValue( "eas crossbar pin" , ui->crossbar_pin->value());

    if( settings.contains("eas test file") )
        ui->capture->setChecked( settings.value("eas test file").toBool() );
    else
    settings.setValue( "eas test file" , ui->capture->isChecked());

    if(settings.contains("eas video device"))
    {
        int index = ui->eas_video_device->findText( settings.value( "eas video device" ).toString() );
        if(index >=0)
        {
            ui->eas_video_device->setCurrentIndex(index);
        }
        else
        {
            ui->eas_video_device->addItem( settings.value( "eas video device" ).toString() );
            ui->eas_video_device->setCurrentIndex( ui->eas_video_device->count()-1 );
        }
    }
    if(settings.contains("eas audio device"))
    {

        int index = ui->eas_audio_device->findText( settings.value( "eas audio device" ).toString() );
        if(index >=0)
        {
            ui->eas_audio_device->setCurrentIndex(index);
        }
        else
        {
            ui->eas_audio_device->addItem( settings.value( "eas audio device" ).toString() );
            ui->eas_audio_device->setCurrentIndex( ui->eas_audio_device->count()-1 );
        }
    }

    if(settings.contains("eas comport"))
    {

        int index = ui->eas_comport->findText( settings.value( "eas comport" ).toString() );
        if(index >=0)
        {
            ui->eas_comport->setCurrentIndex(index);
        }
        else
        {
            ui->eas_comport->addItem( settings.value( "eas comport" ).toString() );
            ui->eas_comport->setCurrentIndex( ui->eas_comport->count()-1 );
        }
    }
}
void MainWindow::store_mux_settings()
{
    settings.setValue("mux_output_port", ui->mux_out_port->currentIndex() );
    settings.setValue("Mux Control Address", ui->mux_ctrl_addr->text() );
    settings.setValue("Mux Control Port", ui->mux_ctrl_port->value());
    settings.setValue("Mux Debug Comport", ui->mux_debug_comport->currentText());
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_restart_eas_clicked()
{
    settings.setValue( "eas video device",ui->eas_video_device->currentText() );
    settings.setValue( "eas audio device",ui->eas_audio_device->currentText() );
    settings.setValue( "eas comport" , ui->eas_comport->currentText());
    settings.setValue( "eas crossbar enable" , ui->crossbar_enable->isChecked());
    settings.setValue( "eas crossbar pin" , ui->crossbar_pin->value());
    settings.setValue( "eas test file" , ui->capture->isChecked());
    if(ui->test_eas->isChecked())
        ui->test_eas->click();
    else
        automation->restart_eas_engine();
}

void MainWindow::on_mux_log_display_textChanged()
{

    if ( mux_scroll_maximum == ui->mux_log_display->verticalScrollBar()->value() )
    {
        ui->mux_log_display->moveCursor(QTextCursor::End);
        ui->mux_log_display->verticalScrollBar()->setValue( ui->mux_log_display->verticalScrollBar()->maximum() );
    }
    mux_scroll_maximum = ui->mux_log_display->verticalScrollBar()->maximum();
}

void MainWindow::on_mux_log_display_2_textChanged()
{

    if ( mux_scroll_2_maximum == ui->mux_log_display_2->verticalScrollBar()->value() )
    {
        ui->mux_log_display_2->moveCursor(QTextCursor::End);
        ui->mux_log_display_2->verticalScrollBar()->setValue( ui->mux_log_display_2->verticalScrollBar()->maximum() );
    }
    mux_scroll_2_maximum = ui->mux_log_display_2->verticalScrollBar()->maximum();
}

void MainWindow::on_encoder_display_textChanged()
{

    if ( encoder_scroll_maximum == ui->encoder_display->verticalScrollBar()->value() )
    {
        ui->encoder_display->moveCursor(QTextCursor::End);
        ui->encoder_display->verticalScrollBar()->setValue( ui->encoder_display->verticalScrollBar()->maximum() );
    }
    encoder_scroll_maximum = ui->encoder_display->verticalScrollBar()->maximum();
}

void MainWindow::on_eas_detect_textChanged()
{

    if ( eas_status_scroll_maximum == ui->eas_detect->verticalScrollBar()->value() )
    {
        ui->eas_detect->moveCursor(QTextCursor::End);
        ui->eas_detect->verticalScrollBar()->setValue( ui->eas_detect->verticalScrollBar()->maximum() );
    }
    eas_status_scroll_maximum = ui->eas_detect->verticalScrollBar()->maximum();
}

void MainWindow::on_stream_status_display_textChanged()
{
    if ( stream_status_scroll_maximum == ui->stream_status_display->verticalScrollBar()->value() )
    {
        ui->stream_status_display->moveCursor(QTextCursor::End);
        ui->stream_status_display->verticalScrollBar()->setValue( ui->stream_status_display->verticalScrollBar()->maximum() );
    }
    stream_status_scroll_maximum = ui->stream_status_display->verticalScrollBar()->maximum();
}

void MainWindow::on_ingest_display_textChanged()
{
    if ( ingest_status_scroll_maximum == ui->ingest_display->verticalScrollBar()->value() )
    {
        ui->ingest_display->moveCursor(QTextCursor::End);
        ui->ingest_display->verticalScrollBar()->setValue( ui->ingest_display->verticalScrollBar()->maximum() );
    }
    ingest_status_scroll_maximum = ui->ingest_display->verticalScrollBar()->maximum();
}

void MainWindow::on_update_mux_settings_clicked()
{
    store_mux_settings();
    automation->restart_mux_control();
}

void MainWindow::on_restore_mux_defaults_clicked()
{
    if( settings.contains("default mux_output_port") )
        ui->mux_out_port->setCurrentIndex(settings.value("default mux_output_port").toInt());

    if( settings.contains("default Mux Control Address") )
        ui->mux_ctrl_addr->setText( settings.value("default Mux Control Address").toString() );

    if( settings.contains("default Mux Control Port") )
        ui->mux_ctrl_port->setValue( settings.value("default Mux Control Port").toInt() );

    if( settings.contains("default Mux Debug Comport") )
        ui->mux_debug_comport->setCurrentText( settings.value("default Mux Debug Comport").toString() );
}

void MainWindow::on_set_mux_defaults_clicked()
{
    settings.setValue("default mux_output_port", ui->mux_out_port->currentIndex() );
    settings.setValue("default Mux Control Address", ui->mux_ctrl_addr->text() );
    settings.setValue("default Mux Control Port", ui->mux_ctrl_port->value());
    settings.setValue("default Mux Debug Comport", ui->mux_debug_comport->currentText());
}

void MainWindow::on_ch1_clicked(bool checked)
{
    if(!eas_ch.contains(1)&&checked)
        eas_ch.append(1);
    if (!checked)
        eas_ch.removeAll(1);
}

void MainWindow::on_ch2_clicked(bool checked)
{
    if(!eas_ch.contains(2)&&checked)
        eas_ch.append(2);
    if (!checked)
        eas_ch.removeAll(2);
}

void MainWindow::on_ch3_clicked(bool checked)
{
    if(!eas_ch.contains(3)&&checked)
        eas_ch.append(3);
    if (!checked)
        eas_ch.removeAll(3);
}

void MainWindow::on_ch4_clicked(bool checked)
{
    if(!eas_ch.contains(4)&&checked)
        eas_ch.append(4);
    if (!checked)
        eas_ch.removeAll(4);
}

void MainWindow::on_ch5_clicked(bool checked)
{
    if(!eas_ch.contains(5)&&checked)
        eas_ch.append(5);
    if (!checked)
        eas_ch.removeAll(5);
}

void MainWindow::on_ch6_clicked(bool checked)
{
    if(!eas_ch.contains(6)&&checked)
        eas_ch.append(6);
    if (!checked)
        eas_ch.removeAll(6);
}

void MainWindow::on_ch7_clicked(bool checked)
{
    if(!eas_ch.contains(7)&&checked)
        eas_ch.append(7);
    if (!checked)
        eas_ch.removeAll(7);
}

void MainWindow::on_ch8_clicked(bool checked)
{
    if(!eas_ch.contains(8)&&checked)
        eas_ch.append(8);
    if (!checked)
        eas_ch.removeAll(8);
}

void MainWindow::on_mux_advanced_toggled(bool checked)
{
    ui->set_mux_defaults->setEnabled(checked);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ad_ch.clear();
    ad_ch.append(index+1);
}

void MainWindow::send_eas_config()
{
    automation->send_eas_config(eas_ch);
}

void MainWindow::on_revert_eas_config_clicked()
{
    qDebug("sending revert command");
    automation->revert_eas_config(eas_ch);
}

void MainWindow::on_ad_insert_clicked()
{
    automation->ad_splice_insert(ad_ch);
}

void MainWindow::on_ad_return_to_network_clicked()
{
    automation->ad_splice_return_to_network(ad_ch);
}

//void MainWindow::on_show_vmon_clicked(bool checked)
//{
//    automation->show_vmon = checked;
//}

void MainWindow::on_send_eas_config_clicked()
{
    qDebug("sending config command");
    send_eas_config();
}

void MainWindow::on_test_eas_clicked(bool checked)
{
    if(!checked)
    {
        ui->test_eas->setText("Test EAS Stream");
        automation->restart_eas_engine();
    }
    else
    {
        automation->restart_eas_engine();
        automation->capture_eas_message();
        ui->test_eas->setText("Stop Test");
    }
}

void MainWindow::on_ingest_clicked(bool checked)
{
    if(!checked)
    {
        automation->ingest_program(ui->ingest_file->text());
    }
    else
    {
        // stop ingest process and clean up files
    }

}

void MainWindow::on_inputfile_browse_clicked()
{
    QString fileName =
        QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "Local Video",
                tr("Video (*.mp4 *.mov *.avi *.mpg *.ts);;All files (*.*)"));
    if (!fileName.isEmpty()) {
        ui->ingest_file->setText(fileName);
    }
}

void MainWindow::on_test_station_ID_clicked()
{
    automation->set_id_channels(id_ch);
    automation->station_id();
}

void MainWindow::on_station_id_filename_textChanged(const QString &arg1)
{
    QString filename;
    filename = arg1;
    settings.setValue("ID File", filename );
}

void MainWindow::on_inputfile_browse_2_clicked()
{
    QString fileName =
        QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "Video",
                tr("Local Video (*.ts);"));
    if (!fileName.isEmpty()) {
        ui->test_filename->setText(fileName);
    }
}

void MainWindow::on_cue_test_stream_clicked()
{
    QString fname;
    int ip_port;
    ip_port = ui->test_ip_port->currentIndex()+1;
    fname = ui->test_filename->text();
    automation->cue_stream(ip_port,fname);
}

void MainWindow::on_start_stream_clicked()
{
    int ip_port;
    ip_port = ui->test_ip_port->currentIndex()+1;
    automation->start_stream(ip_port);
}

void MainWindow::on_id_ch1_clicked(bool checked)
{
    if(!id_ch.contains(1)&&checked)
        id_ch.append(1);
    if (!checked)
        id_ch.removeAll(1);
}

void MainWindow::on_id_ch2_clicked(bool checked)
{
    if(!id_ch.contains(2)&&checked)
        id_ch.append(2);
    if (!checked)
        id_ch.removeAll(2);
}

void MainWindow::on_id_ch3_clicked(bool checked)
{
    if(!id_ch.contains(3)&&checked)
        id_ch.append(3);
    if (!checked)
        id_ch.removeAll(3);
}

void MainWindow::on_id_ch4_clicked(bool checked)
{
    if(!id_ch.contains(4)&&checked)
        id_ch.append(4);
    if (!checked)
        id_ch.removeAll(4);
}

void MainWindow::on_id_ch5_clicked(bool checked)
{
    if(!id_ch.contains(5)&&checked)
        id_ch.append(5);
    if (!checked)
        id_ch.removeAll(5);
}

void MainWindow::on_id_ch6_clicked(bool checked)
{
    if(!id_ch.contains(6)&&checked)
        id_ch.append(6);
    if (!checked)
        id_ch.removeAll(6);
}

void MainWindow::on_id_ch7_clicked(bool checked)
{
    if(!id_ch.contains(7)&&checked)
        id_ch.append(7);
    if (!checked)
        id_ch.removeAll(7);
}

void MainWindow::on_id_ch8_clicked(bool checked)
{
    if(!id_ch.contains(8)&&checked)
        id_ch.append(8);
    if (!checked)
        id_ch.removeAll(8);
}

void MainWindow::on_send_ID_config_clicked()
{
    automation->send_eas_config(id_ch);
}

void MainWindow::on_revert_ID_config_clicked()
{
    automation->revert_eas_config(id_ch);
}

void MainWindow::on_id_browse_clicked()
{
    QString fileName =
        QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "Local Video",
                tr("Video (*.mp4 *.mov *.avi *.mpg *.ts);;All files (*.*)"));
    if (!fileName.isEmpty()) {
        ui->station_id_filename->setText(fileName);
    }
}

void MainWindow::on_ip_config_clicked()
{

}
