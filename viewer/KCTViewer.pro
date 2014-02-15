#-------------------------------------------------
#
# Project created by QtCreator 2013-12-22T00:17:48
#
#-------------------------------------------------

QT       += core gui webkitwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KCTViewer
TEMPLATE = app
CONFIG += c++11
win32: LIBS += -lws2_32 -lmswsock

RC_FILE = KCTViewer.rc

# This is updated by the version bump script
VERSION = 0.8.2

macx: TARGET = KCT Viewer
unix:!macx: TARGET = kancolletool-viewer

binaries.path = $$PREFIX/usr/bin
binaries.files = kancolletool-viewer
INSTALLS += binaries

SOURCES += main.cpp \
	KVMainWindow.cpp \
	KVTranslator.cpp \
	KVProxy.cpp \
	KVProxy_p.cpp \
	KVUtil.cpp \
	lib/HTTP-Proxy/proxy.cpp

HEADERS  += KVMainWindow.h \
	KVTranslator.h \
	KVProxy.h \
	KVProxy_p.h \
	KVUtil.h \
	crc32.h \
	lib/HTTP-Proxy/proxy.hpp

INCLUDEPATH += lib/HTTP-Proxy
INCLUDEPATH += lib/HTTP-Proxy/deps/asio-1.10.1/include

RESOURCES += resources.qrc

OTHER_FILES += KCTViewer.rc \
    index.html
