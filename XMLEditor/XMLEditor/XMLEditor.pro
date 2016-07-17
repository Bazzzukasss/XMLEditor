#-------------------------------------------------
#
# Project created by QtCreator 2016-07-16T13:00:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XMLEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xmlnode.cpp \
    xmlprocessor.cpp

HEADERS  += mainwindow.h \
    xmlnode.h \
    xmlprocessor.h \
    xmldata.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
