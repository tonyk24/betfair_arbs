#-------------------------------------------------
#
# Project created by QtCreator 2015-09-26T13:25:20
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_betlibunitteststest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_betlibunitteststest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

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
