QT += sql network

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD


HEADERS += \
    $$PWD/sql/querytablemodel.h \
    $$PWD/sql/proxymodel.h \
    $$PWD/sql/sqltablemodel.h \
    $$PWD/sql/sqldatabase.h

SOURCES += \    
    $$PWD/sql/querytablemodel.cpp \
    $$PWD/sql/proxymodel.cpp \
    $$PWD/sql/sqltablemodel.cpp \
    $$PWD/sql/sqldatabase.cpp
