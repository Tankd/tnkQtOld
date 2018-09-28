include(gtest_dependency.pri)
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
QT += tnkunicorn testlib

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt

SOURCES += main.cpp \
    author.cpp \
    book.cpp

HEADERS += \
    author.h \
    book.h \
    tst_unicorn.h

