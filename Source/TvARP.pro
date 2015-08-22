#-------------------------------------------------
#
# Project created by QtCreator 2010-09-14T19:42:59
#
#-------------------------------------------------
# http://qt-project.org/wiki/How-to-build-a-static-Qt-for-Windows-MinGW
# https://github.com/Mendeley/Update-Installer/tree/master/src
QT       += core gui serialport network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = TvARP_EAS_beta
TEMPLATE = app


#INCLUDEPATH += $$PWD/ffmpeg-20141113-git-3e1ac10-win32-dev/include
#LIBS += -L$$PWD/ffmpeg-20141113-git-3e1ac10-win32-dev/lib -lavutil -lavcodec -lavformat -lswscale

SOURCES +=\
        mainwindow.cpp \
    automation.cpp \
    sys_tray_icon.cpp \
    mux_control.cpp \
    stream.cpp \
    configure_eas.cpp \
    ffmpeg.cpp \
    server_main.cpp \
    smtp.cpp

HEADERS  += \
    automation.h \
    sys_tray_icon.h \
    mainwindow.h \
    mux_control.h \
    stream.h \
    configure_eas.h \
    ffmpeg.h \
    smtp.h

FORMS    += mainwindow.ui \
    configure_eas.ui

RESOURCES += \
    systray.qrc

DISTFILES +=
