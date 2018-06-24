QT += sql network

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD


HEADERS += \
    $$PWD/sql/querytablemodel.h \
    $$PWD/sql/proxymodel.h \
    $$PWD/sql/sqltablemodel.h \
    $$PWD/sql/sqldatabase.h \
    $$PWD/sql/parser/baseparser.h \
    $$PWD/sql/parser/csvparser.h \
    $$PWD/sql/parser/xlsparser.h

SOURCES += \    
    $$PWD/sql/querytablemodel.cpp \
    $$PWD/sql/proxymodel.cpp \
    $$PWD/sql/sqltablemodel.cpp \
    $$PWD/sql/sqldatabase.cpp \
    $$PWD/sql/parser/baseparser.cpp \
    $$PWD/sql/parser/csvparser.cpp \
    $$PWD/sql/parser/xlsparser.cpp
