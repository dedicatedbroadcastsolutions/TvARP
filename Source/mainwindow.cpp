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

    ui->mux_log_display->ensureCursorVisible();
    ui->mux_log_display->moveCursor(QTextCursor::End);
    ui->mux_log_display->verticalScrollBar()->setValue( ui->mux_log_display->verticalScrollBar()->maximum() );
    QTextDocument * doc = ui->mux_log_display->document();
    doc->setMaximumBlockCount(maxblock);
    connect(automation,SIGNAL(mux_eas_log(QString)),ui->mux_log_display,SLOT( insertPlainText(QString) ) );
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
}


void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_restart_eas_clicked()
{

}

void MainWindow::on_pushButton_clicked()
{
    //eas->send_eas_message();
    //eas->fake_ring();
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

void MainWindow::on_update_mux_settings_clicked()
{
    settings.setValue("mux_output_port", ui->mux_out_port->currentIndex() );
    automation->restart_mux_control();
}
