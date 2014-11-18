/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**

  File modified and customised by Zach Swena, modifications subject to GPL.
****************************************************************************/

#include <QtWidgets>
#include "sys_tray_icon.h"
//! [0]
sys_Tray_Icon::sys_Tray_Icon()
{
    createActions();
    createTrayIcon();

    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    setIcon(1);
    trayIcon->show();
}

sys_Tray_Icon::~sys_Tray_Icon()
{
    QFile file("Schedule_and_logs/running.config");
    if (!file.open(QIODevice::WriteOnly))
        return;
    QTextStream out(&file);
        out << 0;
    file.close();
}

/// ----------------------------------------------------
void sys_Tray_Icon::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(isMaximized() || !visible);
    QMainWindow::setVisible(visible);
}
/// ----------------------------------------------------
void sys_Tray_Icon::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible())
    {
        trayIcon->showMessage(tr("Still here!!!"),
        tr("This application is still running. To quit please right click this icon and select Quit"));
        hide();
       // hide();
        event->ignore();
    }
}
/// ----------------------------------------------------
/*
void sys_Tray_Icon::changeEvent(QEvent* e)
{
    if (e->type() == QEvent::WindowStateChange)
      {

         if (this->windowState() & Qt::WindowMinimized)
         {
            video->show();
         }
      }
    else
    QMainWindow::changeEvent(e);
}*/
/// ----------------------------------------------------
void sys_Tray_Icon::setIcon(int index)
{
    trayIcon->setIcon(QIcon(":/images/run.svg"));
}
/// ----------------------------------------------------
bool hidden=0;
void sys_Tray_Icon::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:

    case QSystemTrayIcon::DoubleClick:
        if(hidden)
        {
           this->showNormal();
           hidden=0;
        }
        else
        {
           this->hide();
           hidden=1;
        }
        break;
    case QSystemTrayIcon::MiddleClick:
        showMessage();
        break;
    default:
        ;
    }
}
/// ----------------------------------------------------

void sys_Tray_Icon::showMessage()
{
    //trayIcon->showMessage(tr("Message Clicked"),
     //       tr("Sorry I haven't implemented this yet"));
}
/// ----------------------------------------------------
void sys_Tray_Icon::messageClicked()
{
   // trayIcon->showMessage(tr("Message Clicked"),
    ///        tr("Sorry I haven't implemented this yet"));
}
/// ----------------------------------------------------
void sys_Tray_Icon::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    //restore_videoAction = new QAction(tr("Restore Video"),this);
   //  connect(restore_videoAction, SIGNAL(triggered()), video, SLOT(move_video()));

    //video_fullscreen = new QAction(tr("Fullscreen Video"),this);
   // connect(video_fullscreen, SIGNAL(triggered()), video, SLOT(fullscreen()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit_program()));
}
/// ----------------------------------------------------
void sys_Tray_Icon::quit_program()
{
    qApp->quit();
}
/// ----------------------------------------------------
void sys_Tray_Icon::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    //trayIconMenu->addAction(restore_videoAction);
    trayIconMenu->addSeparator();
    //trayIconMenu->addAction(video_fullscreen);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);


    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}
/// ----------------------------------------------------
