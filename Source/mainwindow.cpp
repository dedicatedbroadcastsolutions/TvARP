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
//#include "com_select.h"
//#include "live_controls.h"
//#include "sys_tray_icon.h"
//#include "schedule_program.h"


/// Global Variables
QString schfile="Schedule_and_logs/schedule.automation";
/// Initiate Thread
//Schedulethread schthread;


//QFileDialog::getOpenFileName(this,tr("Load a file"), "~", tr("Video Files (*.mpg *.mp4 *.flv *mov)"));

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int maxblock = 250;
    readSettings();

    automation = new Automation(this);
    eas_ch.clear();
    eas_ch.append(1);
    eas_ch.append(2);
    eas_ch.append(3);
    eas_ch.append(4);
    eas_ch.append(5);
    eas_ch.append(6);
    eas_ch.append(7);
    ui->mux_log_display->ensureCursorVisible();
    ui->mux_log_display->moveCursor(QTextCursor::End);
    ui->mux_log_display->verticalScrollBar()->setValue( ui->mux_log_display->verticalScrollBar()->maximum() );
    QTextDocument * doc = ui->mux_log_display->document();
    doc->setMaximumBlockCount(maxblock);
    connect(automation,SIGNAL(mux_eas_log(QString)),ui->mux_log_display,SLOT( insertPlainText(QString) ) );
    connect(automation,SIGNAL(mux_eas_log(QString)),ui->mux_log_display_2,SLOT( insertPlainText(QString) ) );
}

MainWindow::~MainWindow()
{
    delete ui;
    QFile file("Schedule_and_logs/running.config");
    if (!file.open(QIODevice::WriteOnly))
        return;
    QTextStream out(&file);
        out << 0;
    file.close();
}

void MainWindow::on_actionStart_Minimized_toggled(bool visible)
{
    settings.setValue("visible", visible);
}

void MainWindow::readSettings()
{

    ui->actionStart_Minimized->setChecked(settings.value("visible").toBool());

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
    qDebug()<< "video = " <<settings.value("eas video device") << "audio = " << settings.value("eas audio device");
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

    if ( mux_scroll_maximum == ui->mux_log_display->verticalScrollBar()->value() )
    {
        ui->mux_log_display->moveCursor(QTextCursor::End);
        ui->mux_log_display->verticalScrollBar()->setValue( ui->mux_log_display->verticalScrollBar()->maximum() );
    }
    mux_scroll_maximum = ui->mux_log_display->verticalScrollBar()->maximum();
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

void MainWindow::on_mux_advanced_toggled(bool checked)
{
    ui->set_mux_defaults->setEnabled(checked);
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

void MainWindow::send_eas_config()
{
    automation->send_eas_config(eas_ch);
}

void MainWindow::on_revert_eas_config_clicked()
{
    automation->revert_eas_config(eas_ch);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ad_ch.clear();
    ad_ch.append(index);
}

void MainWindow::ad_insert()
{
    automation->ad_splice_insert(ad_ch);
}

void MainWindow::on_ad_return_to_network_clicked()
{
    automation->ad_splice_return_to_network(ad_ch);
}

void MainWindow::on_test_eas_clicked()
{
    automation->start_stream();
}
