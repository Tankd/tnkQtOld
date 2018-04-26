INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += network

HEADERS += \
    $$PWD/mail/imap.h \
    $$PWD/mail/longstream_p.h \
    $$PWD/mail/longstring_p.h \
    $$PWD/mail/qmailaddress.h \
    $$PWD/mail/qmailcodec.h \
    $$PWD/mail/qmailid.h \
    $$PWD/mail/qmailipc.h \
    $$PWD/mail/qmailmessage.h \
    $$PWD/mail/qmailmessage_p.h \
    $$PWD/mail/qmailmessagefwd.h \
    $$PWD/mail/qmailnamespace.h \
    $$PWD/mail/qmailtimestamp.h \
    $$PWD/mail/qprivateimplementation.h \
    $$PWD/mail/qprivateimplementationdef_p.h

SOURCES += \
    $$PWD/mail/imap.cpp \
    $$PWD/mail/longstream.cpp \
    $$PWD/mail/longstring.cpp \
    $$PWD/mail/qmailaddress.cpp \
    $$PWD/mail/qmailcodec.cpp \
    $$PWD/mail/qmailid.cpp \
    $$PWD/mail/qmailinstantiations.cpp \
    $$PWD/mail/qmailmessage.cpp \
    $$PWD/mail/qmailmessagefwd.cpp \
    $$PWD/mail/qmailnamespace.cpp \
    $$PWD/mail/qmailtimestamp.cpp \
    $$PWD/mail/qprivateimplementation.cpp
