QT += widgets

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/widgets/traywidget.h \
    $$PWD/widgets/stylesheet.h \
    $$PWD/widgets/jsoneditdialog.h \
    $$PWD/external/QJsonModel/qjsonmodel.h

SOURCES += \
    $$PWD/widgets/traywidget.cpp \
    $$PWD/widgets/stylesheet.cpp \
    $$PWD/widgets/jsoneditdialog.cpp \
    $$PWD/external/QJsonModel/qjsonmodel.cpp

RESOURCES += \
    $$PWD/widgets/res/res.qrc

LIBS += User32.lib

FORMS += \
    $$PWD/widgets/jsoneditdialog.ui
