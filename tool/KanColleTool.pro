#-------------------------------------------------
#
# Project created by QtCreator 2013-12-22T00:17:48
#
#-------------------------------------------------

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KanColleTool
TEMPLATE = app
CONFIG += c++11

QMAKE_INFO_PLIST = Info.plist

macx {
	LIBS += -framework Carbon -lobjc
}
unix:!macx {
	LIBS += -lX11
}

SOURCES += main.cpp \
	KCMainWindow.cpp \
	KCClient.cpp \
    KCShip.cpp \
    KCShipMaster.cpp

HEADERS  += KCMainWindow.h \
	KCClient.h \
    KCShip.h \
    KCShipMaster.h

FORMS    += \
    KCMainWindow.ui

RESOURCES += resources.qrc

OTHER_FILES += Info.plist
