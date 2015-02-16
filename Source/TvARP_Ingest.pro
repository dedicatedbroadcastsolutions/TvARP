#-------------------------------------------------
#
# Project created by QtCreator 2013-10-03T22:30:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TvARP_Ingest
TEMPLATE = app


SOURCES +=\
    ffmpeg.cpp \
    ingest_main.cpp \
    ingest_dialog.cpp

HEADERS  += \
    ffmpeg.h \
    ingest_dialog.h

FORMS    += \
    ingest_dialog.ui
