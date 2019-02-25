TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    client.cpp \
    utils.cpp \
    httpheader.cpp \
    http_request.cpp

HEADERS += \
    client.h \
    utils.h \
    httpheader.h \
    http_request.h

LIBS += -lws2_32
