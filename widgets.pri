QT += widgets

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD



HEADERS += \
    $$PWD/widgets/tabwidget.h \
    $$PWD/widgets/tabbar.h \
    $$PWD/widgets/tabbar.h \
    $$PWD/widgets/tabgrabwidget.h \
    $$PWD/widgets/tabwidget.h\
    $$PWD/widgets/traywidget.h

SOURCES += \     
    $$PWD/widgets/tabwidget.cpp \
    $$PWD/widgets/tabbar.cpp \
    $$PWD/widgets/tabbar.cpp \
    $$PWD/widgets/tabgrabwidget.cpp \
    $$PWD/widgets/tabwidget.cpp \
    $$PWD/widgets/traywidget.cpp

RESOURCES += \
    $$PWD/widgets/res/res.qrc
