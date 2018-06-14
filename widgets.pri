QT += widgets

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/widgets/traywidget.h \
    $$PWD/widgets/stylesheet.h \
    $$PWD/widgets/framelesswidget.h
SOURCES += \
    $$PWD/widgets/traywidget.cpp \
    $$PWD/widgets/stylesheet.cpp \
    $$PWD/widgets/framelesswidget.cpp

RESOURCES += \
    $$PWD/widgets/res/res.qrc

LIBS += User32.lib

FORMS += \
    $$PWD/widgets/framelesswidget.ui

