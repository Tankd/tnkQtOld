QT += sql network quick


include ('common.pri')
include ('sql.pri')
include ('ws.pri')

INCLUDEPATH += $$PWD

QMAKE_CXXFLAGS 	+= -fPIC
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -fpermissive

SOURCES += \
    $$PWD/sync/querybuilder.cpp \
    $$PWD/sync/object.cpp \
    $$PWD/sync/engine.cpp \
    $$PWD/sync/model.cpp

HEADERS += \
    $$PWD/sync/querybuilder.h \
    $$PWD/sync/object.h \
    $$PWD/sync/engine.h \
    $$PWD/sync/model.h
