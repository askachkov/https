TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += thread

SOURCES += \
        main.cpp \
    client.cpp \
    utils.cpp \
    httpheader.cpp \
    http_request.cpp \
    tasks.cpp \
    handlers.cpp \
    Daemon.cpp

HEADERS += \
    client.h \
    utils.h \
    httpheader.h \
    http_request.h \
    tasks.h \
    handlers.h \
    Daemon.h

LIBS += -lssl -lcrypto -lz -lbrotlienc -lbrotlicommon

win32:CONFIG(release, debug|release): LIBS += -lws2_32

DISTFILES += \
    www/index.htm \
    www/404.htm \
    www/face.png

unix:!macx: LIBS += -L$$PWD/../../../lib/ -lcgzip -ldaemon-lite

INCLUDEPATH += $$PWD/../../../include
DEPENDPATH += $$PWD/../../../include
