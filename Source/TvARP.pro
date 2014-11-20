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
#LIBS += -L$$PWD/lib/ -llibvlc
#LIBS += -L$$PWD/ffmpeg-20141113-git-3e1ac10-win32-dev/lib -lavutil -lavcodec -lavformat -lswscale

SOURCES += main.cpp\
        mainwindow.cpp \
    automation.cpp \
    sys_tray_icon.cpp \
    eas.cpp \
    mux_control.cpp \
    stream.cpp \
    configure_eas.cpp

HEADERS  += \
    automation.h \
    sys_tray_icon.h \
    mainwindow.h \
    eas.h \
    mux_control.h \
    stream.h \
    configure_eas.h

FORMS    += mainwindow.ui \
    configure_eas.ui

RESOURCES += \
    systray.qrc
