#-------------------------------------------------
#
# Project created by QtCreator 2016-06-25T20:50:50
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HDRI-Project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    startwidget.cpp \
    hdrmodule.cpp \
    abstractwidget.cpp \
    exif.cpp \
    gsolver.cpp \
    calweight.cpp \
    qcustomplot.cpp \
    gsolvemodule.cpp \
    gsolvewidget.cpp \
    gradientmodule.cpp \
    gradientwidget.cpp \
    tonemappingmodule.cpp \
    tonemappingwidget.cpp \
    alignmentmodel.cpp \
    alignmentwidget.cpp

HEADERS  += mainwindow.h \
    hdrmodule.h \
    startwidget.h \
    abstractwidget.h \
    exif.h \
    gsolver.h \
    calweight.h \
    qcustomplot.h \
    gsolvemodule.h \
    gsolvewidget.h \
    gradientmodule.h \
    gradientwidget.h \
    tonemappingmodule.h \
    tonemappingwidget.h \
    alignmentmodel.h \
    alignmentwidget.h

FORMS    += mainwindow.ui \
    startwidget.ui \
    gsolvewidget.ui \
    gradientwidget.ui \
    tonemappingwidget.ui \
    alignmentwidget.ui

DISTFILES += \
    LICENSE \
    README.md
