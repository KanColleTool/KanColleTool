#-------------------------------------------------
#
# Project created by QtCreator 2013-12-22T00:17:48
#
#-------------------------------------------------

QT       += core gui network sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KanColleTool
TEMPLATE = app
CONFIG += c++11

# This is updated by the version bump script
VERSION = 0.8.4

unix:!macx: TARGET = kancolletool

QMAKE_INFO_PLIST = Info.plist
RC_FILE = KanColleTool.rc
ICON = KanColleTool.icns

macx: LIBS += -framework Carbon -lobjc

binaries.path = $$PREFIX/usr/bin
binaries.files = kancolletool
INSTALLS += binaries

SOURCES += main.cpp \
	KCMainWindow.cpp \
	KCSettingsDialog.cpp \
	KCClient.cpp \
	KCClient_p.cpp \
	KCToolServer.cpp \
	KCShip.cpp \
	KCShipType.cpp \
	KCFleet.cpp \
	KCDock.cpp \
	KCTranslator.cpp \
	KCLogger.cpp

HEADERS  += KCMainWindow.h \
	KCSettingsDialog.h \
	KCClient.h \
	KCToolServer.h \
	KCGameObject.h \
	KCShip.h \
	KCShipType.h \
	KCFleet.h \
	KCDock.h \
	KCTranslator.h \
	KCLogger.h \
	KCDefaults.h

FORMS    += \
    KCMainWindow.ui \
    KCSettingsDialog.ui

RESOURCES += resources.qrc

OTHER_FILES += Info.plist \
    KanColleTool.rc
