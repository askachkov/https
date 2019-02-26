TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    socket.cpp \
    socketstream.cpp

HEADERS += \
    socket.h \
    socketstream.h

win32:CONFIG(release, debug|release): LIBS += -lws2_32

TARGET = socketstream
