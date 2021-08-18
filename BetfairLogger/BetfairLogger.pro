#-------------------------------------------------
#
# Project created by QtCreator 2015-05-31T10:55:35
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = BetfairLogger
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app


SOURCES += main.cpp \
    debugmsglogger.cpp \
    mainthread.cpp

HEADERS += \
    debugmsglogger.h \
    mainthread.h \
    interactiveapp.h

DISTFILES += \
    TODO.txt \
    bok.txt

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BetLib/release/ -lBetLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BetLib/debug/ -lBetLib
else:unix: LIBS += -L$$OUT_PWD/../BetLib/ -lBetLib

INCLUDEPATH += $$PWD/../BetLib
DEPENDPATH += $$PWD/../BetLib


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../bfapingqtcpp/BetfairLib/release/ -lBetfairLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../bfapingqtcpp/BetfairLib/debug/ -lBetfairLib
else:unix: LIBS += -L$$OUT_PWD/../../../bfapingqtcpp/BetfairLib/ -lBetfairLib

INCLUDEPATH += $$PWD/../../../bfapingqtcpp/BetfairLib
DEPENDPATH += $$PWD/../../../bfapingqtcpp/BetfairLib
