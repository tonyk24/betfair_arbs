#-------------------------------------------------
#
# Project created by QtCreator 2015-08-15T13:56:39
#
#-------------------------------------------------

QT       += testlib network

QT       -= gui

TARGET = tst_betfairlibunitteststest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11
TEMPLATE = app


SOURCES += tst_betfairlibunitteststest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BetfairLib/release/ -lBetfairLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BetfairLib/debug/ -lBetfairLib
else:unix: LIBS += -L$$OUT_PWD/../BetfairLib/ -lBetfairLib

INCLUDEPATH += $$PWD/../BetfairLib
DEPENDPATH += $$PWD/../BetfairLib

RESOURCES += \
    testdata.qrc

DISTFILES += \
    jsonData/json_correctApiNgException.json \
    jsonData/json_placeOrdersInvalidBetsizeRsp.json \
    jsonData/json_placeOrdersInsufficientFundsRsp.json \
    jsonData/json_placeOrdersReq.json \
    jsonData/json_placeOrdersSuccessRsp.json \
    jsonData/json_listCurrentOrdersReq.json \
    jsonData/json_listCurrentOrdersRsp.json \
    jsonData/json_getAccountFundsReq.json \
    jsonData/json_getAccountFundsRsp.json \
    jsonData/json_getAccountDetailsReq.json \
    jsonData/json_getAccountDetailsRsp.json
