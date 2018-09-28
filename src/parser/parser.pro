TARGET = QtTnkParser
QPRO_PWD = $PWD
MODULE = tnkparser

QT += core

PUBLIC_HEADERS = baseparser.h \
                 csvparser.h \
                 xlsparser.h \
                 parser_global.h




HEADERS += $$PUBLIC_HEADERS $$PRIVATE_HEADERS
load(qt_module)

SOURCES += \
    baseparser.cpp \
    csvparser.cpp \
    xlsparser.cpp


