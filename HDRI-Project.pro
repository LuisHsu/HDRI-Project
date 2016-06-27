#-------------------------------------------------
#
# Project created by QtCreator 2016-06-25T20:50:50
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HDRI-Project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    startwidget.cpp \
    hdrmodule.cpp \
    calweight.cpp \
    mirrormodule.cpp \
    mirrorwidget.cpp \
    abstractwidget.cpp \
    exif.cpp \
    matlabqt.cpp

HEADERS  += mainwindow.h \
    hdrmodule.h \
    startwidget.h \
    calweight.h \
    mirrormodule.h \
    abstractwidget.h \
    mirrorwidget.h \
    exif.h \
    matlabqt.h

FORMS    += mainwindow.ui \
    startwidget.ui \
    mirrorwidget.ui

DISTFILES += \
    LICENSE \
    README.md
