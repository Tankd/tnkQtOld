TARGET = QtTnkSql
QPRO_PWD = $PWD
MODULE = tnksql

QT += core sql

PUBLIC_HEADERS = proxymodel.h \
                 querytablemodel.h \
                 sqldatabase.h \
                 sqltablemodel.h \
                 sql_global.h




HEADERS += $$PUBLIC_HEADERS $$PRIVATE_HEADERS
load(qt_module)

SOURCES += \
    proxymodel.cpp \
    querytablemodel.cpp \
    sqldatabase.cpp \
    sqltablemodel.cpp


