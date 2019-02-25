TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp

DISTFILES += \
    main.txt

LIBS += -lws2_32

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LibSocket/release/ -lsocketstream
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LibSocket/debug/ -lsocketstream
else:unix: LIBS += -L$$OUT_PWD/../LibSocket/ -lsocketstream

INCLUDEPATH += $$PWD/../LibSocket
DEPENDPATH += $$PWD/../LibSocket
