#-------------------------------------------------
#
# Project created by QtCreator 2015-03-30T14:19:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = file-comparer
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/fileview.cpp \
    src/comparingresult.cpp \
    src/comparinginformation.cpp

HEADERS  += src/mainwindow.h \
    src/common.h \
    src/fileview.h \
    src/comparingresult.h \
    src/comparinginformation.h

FORMS    +=
