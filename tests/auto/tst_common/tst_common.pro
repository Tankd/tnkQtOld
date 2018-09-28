include(gtest_dependency.pri)
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
QT += tnkcommon testlib

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt

SOURCES += main.cpp



HEADERS += \
    tst_json.h \
    tst_utils.h
