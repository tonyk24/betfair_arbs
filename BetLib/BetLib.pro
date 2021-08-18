#-------------------------------------------------
#
# Project created by QtCreator 2015-09-25T19:37:15
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = BetLib
TEMPLATE = lib

DEFINES += BETLIB_LIBRARY

SOURCES += \
    betcontrollerlib.cpp \
    betting/bethandler.cpp \
    betting/betlogger.cpp \
    betting/betstatistics.cpp \
    betting/eventstats.cpp \
    misc/simplecrypt.cpp \
    misc/config.cpp \
    eventdataconsumer.cpp \
    eventdatalogger.cpp \
    betting/marketsdata.cpp

HEADERS +=\
        betlib_global.h \
    betcontrollerlib.h \
    betting/accountshandler.h \
    betting/activecombination.h \
    betting/bethandler.h \
    betting/betlogger.h \
    betting/betstatistics.h \
    betting/eventstats.h \
    misc/debugmacros.h \
    misc/simplecrypt.h \
    misc/config.h \
    eventdataconsumer.h \
    eventdatalogger.h \
    eventdatat.h \
    sleeper.h \
    betting/marketsdata.h \
    factory/bffilterfactory.h \
    misc/sleeper.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../bfapingqtcpp/BetfairLib/release/ -lBetfairLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../bfapingqtcpp/BetfairLib/debug/ -lBetfairLib
else:unix: LIBS += -L$$OUT_PWD/../../../bfapingqtcpp/BetfairLib/ -lBetfairLib

INCLUDEPATH += $$PWD/../../../bfapingqtcpp/BetfairLib
DEPENDPATH += $$PWD/../../../bfapingqtcpp/BetfairLib
