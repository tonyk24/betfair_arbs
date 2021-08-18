#-------------------------------------------------
#
# Project created by QtCreator 2015-06-03T22:01:11
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = SrcGenerator
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app


SOURCES += main.cpp \
    controller.cpp

HEADERS += \
    controller.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BetfairLib/release/ -lBetfairLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BetfairLib/debug/ -lBetfairLib
else:unix: LIBS += -L$$OUT_PWD/../BetfairLib/ -lBetfairLib

INCLUDEPATH += $$PWD/../BetfairLib
DEPENDPATH += $$PWD/../BetfairLib
