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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QtCore>
#include <QScrollBar>
#include <QFileDialog>
#include "automation.h"
#include "smtp.h"
//#include "video_window.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
   // video_window *video;
    QSettings settings;
    Automation *automation;

public slots:
    void readSettings();
signals:
    void play();
private:
    Ui::MainWindow *ui;
    //EAS *eas;
    int mux_scroll_maximum;
    int mux_scroll_2_maximum;
    int encoder_scroll_maximum;
    int eas_status_scroll_maximum;
    int stream_status_scroll_maximum;
    int ingest_status_scroll_maximum;
    QList < int > eas_ch , ad_ch;
    QStringList file_attachments;
private slots:
    void sendMail();
    void mailSent(QString);
    void browse();

    void store_mux_settings();
    void on_actionStart_Minimized_toggled(bool );
    void on_actionExit_triggered();
    void on_restart_eas_clicked();

    void on_stream_status_display_textChanged();
    void on_eas_detect_textChanged();
    void on_mux_log_display_textChanged();
    void on_mux_log_display_2_textChanged();
    void on_encoder_display_textChanged();
    void on_update_mux_settings_clicked();
    void on_restore_mux_defaults_clicked();
    void on_set_mux_defaults_clicked();
    void on_mux_advanced_toggled(bool checked);
    void on_ch1_clicked(bool checked);
    void on_ch2_clicked(bool checked);
    void on_ch3_clicked(bool checked);
    void on_ch4_clicked(bool checked);
    void on_ch5_clicked(bool checked);
    void on_ch6_clicked(bool checked);
    void on_ch7_clicked(bool checked);
    void on_ch8_clicked(bool checked);
    void send_eas_config();
    void on_revert_eas_config_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_ad_insert_clicked();
    void on_ad_return_to_network_clicked();
    void on_show_vmon_clicked(bool checked);
    void on_send_eas_config_clicked();
    void on_test_eas_clicked(bool checked);
    void on_ingest_clicked(bool checked);
    void on_ingest_display_textChanged();
    void on_inputfile_browse_clicked();
    void on_test_clicked();
    void on_test_station_ID_clicked();
    void on_station_id_filename_textChanged(const QString &arg1);
    void on_inputfile_browse_2_clicked();
    void on_pushButton_clicked();
    void on_start_stream_clicked();
};

#endif // MAINWINDOW_H
