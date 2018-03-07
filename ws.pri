QT += network

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD


include ('common.pri')


HEADERS += \
    $$PWD/ws/restws.h \
    $$PWD/ws/couchdb.h

SOURCES += \    
    $$PWD/ws/restws.cpp \
    $$PWD/ws/couchdb.cpp
