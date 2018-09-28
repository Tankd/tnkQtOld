
TARGET = QtTnkCommon
QPRO_PWD = $PWD
MODULE = tnkcommon

QT += core
PUBLIC_HEADERS = jsonobject.h \
                 singleton.h \
                 timer.h \
                 utils.h \
                 common_global.h

SOURCES += jsonobject.cpp \
           timer.cpp \
           utils.cpp 



HEADERS += $$PUBLIC_HEADERS $$PRIVATE_HEADERS
load(qt_module)


