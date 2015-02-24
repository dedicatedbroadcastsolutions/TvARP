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

//
//#include <QtGui/QApplication>
#include <QtWidgets>
#include "mainwindow.h"
#include "sys_tray_icon.h"
//#include "video_window.h"
#include "windows.h"

#include "QDebug"
int main(int argc, char *argv[])
{

#if defined(Q_OS_WIN)
   SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, SPIF_SENDCHANGE, 0, 0);
#endif

    SystemParametersInfo(SPI_SETSCREENSAVEACTIVE,FALSE,NULL,TRUE);
    QCoreApplication::setOrganizationName("ZCybercomputing");
    QCoreApplication::setOrganizationDomain("3abnlocal.tv");
    QCoreApplication::setApplicationName("TVARP");
    QSettings settings;


    Q_INIT_RESOURCE(systray);

    QApplication a(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    sys_Tray_Icon sys_Tray_Icon;

    if ( sys_Tray_Icon.program_running() )
        return(0);

    sys_Tray_Icon.setVisible(!settings.value("visible").toBool());



    return a.exec();
}
