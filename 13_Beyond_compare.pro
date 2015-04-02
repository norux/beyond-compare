#-------------------------------------------------
#
# Project created by QtCreator 2015-03-30T14:19:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 13_Beyond_compare
TEMPLATE = app


SOURCES += src/main.cpp\
		src/mainwindow.cpp \
	src/fileview.cpp \
	src/comparingresult.cpp \
	src/comparinginformation.cpp

HEADERS  += src/mainwindow.h \
	src/fileview.h \
	src/comparingresult.h \
	src/comparinginformation.h \
	src/common.h

FORMS    +=

RESOURCES += \
	resource/resource.qrc

TRANSLATIONS += resource/translations/ko_KR.ts

DISTFILES += \
	resource/translations/ko_KR.ts
