TARGET = QtTnkUnicorn
QPRO_PWD = $PWD
MODULE = tnkunicorn

QT += core sql

PUBLIC_HEADERS = engine.h \
                 entity.h \
                 model.h \
                 unicorn_global.h




HEADERS += $$PUBLIC_HEADERS $$PRIVATE_HEADERS
load(qt_module)

SOURCES += \
    engine.cpp \
    entity.cpp \
    model.cpp


