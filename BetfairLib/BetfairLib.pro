#-------------------------------------------------
#
# Project created by QtCreator 2015-05-24T01:09:59
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = BetfairLib
TEMPLATE = lib
CONFIG   += c++11
DEFINES += BETFAIRLIB_LIBRARY

SOURCES += \
    betfairapi/eventsapi.cpp \
    betfairapi/httpjsonclient.cpp \
    betfairapi/loginapi.cpp \
    betfairapi/marketbookapi.cpp \
    betfairapi/marketcatalogueapi.cpp \
    betfairapi/keepaliveapi.cpp \
    betfairapi/placeordersapi.cpp \
    betfairapi/accountsapi.cpp \
    betfairapi/listcurrentordersapi.cpp \
    betfairapi/cancelordersapi.cpp

HEADERS +=\
        betfairlib_global.h \
    betfairapi/eventsapi.h \
    betfairapi/httpjsonclient.h \
    betfairapi/loginapi.h \
    betfairapi/marketbookeapi.h \
    betfairapi/marketcatalogueapi.h \
    bftypes/bfmarket.h \
    bftypes/bfselection.h \
    betfairfilter/betfairmarketfilter.h \
    betfairapi/keepaliveapi.h \
    bfjsonparser/bfapingexceptionparser.h \
    bfjsonparser/bfmarketcatalogueparser.h \
    betfairfilter/bfmarkettype.h \
    bfjsonparser/bfeventresultlistparser.h \
    bftypes/bfeventresult.h \
    bftypes/bfplaceinstruction.h \
    bfenums/bfordertype.h \
    bfenums/bfmarketprojection.h \
    bfenums/bfpricedata.h \
    bfenums/bfmatchprojection.h \
    bfenums/bforderprojection.h \
    bfenums/bfmarketstatus.h \
    bfenums/bfrunnerstatus.h \
    bfenums/bftimegranuality.h \
    bfenums/bfside.h \
    bfenums/bforderstatus.h \
    bfenums/bforderby.h \
    bfenums/bfsortdir.h \
    bfenums/bfmarketsort.h \
    bfenums/bfmarketbettingtype.h \
    bfenums/bfexecutionreportstatus.h \
    bfenums/bfexecutionreporterrorcode.h \
    bfenums/bfpersistencetype.h \
    bfenums/bfinstructionreportstatus.h \
    bfenums/bfinstructionreporterrorcode.h \
    bfenums/bfrollupmodel.h \
    bfenums/bfgroupby.h \
    betfairapi/placeordersapi.h \
    bftypes/bfplaceexecutionreport.h \
    bftypes/bflimitorder.h \
    bftypes/bflimitoncloseorder.h \
    bftypes/bfmarketoncloseorder.h \
    bftypes/bfplaceinstructionreport.h \
    bfjsonparser/bfplaceordersparser.h \
    bfjsoncreator/bfplaceordersjsoncreator.h \
    misc/debugmacros.h \
    bfenums/bfcompetition.h \
    bftypes/bfevent.h \
    bftypes/bfmarket.h \
    bftypes/bfselection.h \
    betfairapi/accountsapi.h \
    bftypes/bfaccountfundsrsp.h \
    bftypes/bfaccountdetailsrsp.h \
    bfjsoncreator/bfaccountsapijsoncreator.h \
    bfjsonparser/bfaccountsapiparser.h \
    misc/bfconfig.h \
    betfairapi/listcurrentordersapi.h \
    bfjsoncreator/bflistcurrentordersjsoncreator.h \
    bftypes/bfcurrentorder.h \
    bfjsonparser/bflistcurrentordersparser.h \
    betfairapi/cancelordersapi.h \
    bftypes/bfcancelinstruction.h \
    bfjsoncreator/bfcancelordersjsoncreator.h \
    bfjsonparser/bfcancelordersparser.h \
    bftypes/bfcancelexecutionreport.h \
    bftypes/bfcancelinstructionreport.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    misc/Eigen/CMakeLists.txt
