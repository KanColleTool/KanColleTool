#-------------------------------------------------
#
# Project created by QtCreator 2013-12-22T00:17:48
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KanColleTool
TEMPLATE = app
QMAKE_INFO_PLIST = Info.plist

mac: LIBS += -framework Carbon


SOURCES += main.cpp \
	KCMainWindow.cpp \
	KCClient.cpp

HEADERS  += KCMainWindow.h \
	KCClient.h

FORMS    += KCMainWindow.ui

RESOURCES += resources.qrc

OTHER_FILES += Info.plist
