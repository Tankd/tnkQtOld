TARGET = QtTnkWs
QPRO_PWD = $PWD
MODULE = tnkws

QT += core network tnkcommon

PUBLIC_HEADERS = restws.h \
                 ws_global.h

SOURCES += restws.cpp

HEADERS += $$PUBLIC_HEADERS $$PRIVATE_HEADERS
load(qt_module)


