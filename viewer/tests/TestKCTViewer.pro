QT += core webkitwidgets testlib

TARGET = KCTViewerTest
CONFIG += c++11 testcase
win32: LIBS += -lws2_32 -lmswsock

SOURCES += TestKVTranslator.cpp
include(../KCTViewer.pri)
