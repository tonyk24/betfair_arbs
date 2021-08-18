#include <map>
#include <list>
#include <cmath>

#include <QString>
#include <QtTest>
#include <QJsonDocument>

#include "bfjsoncreator/bfplaceordersjsoncreator.h"
#include "bfjsoncreator/bfaccountsapijsoncreator.h"

#include "bfjsonparser/bfapingexceptionparser.h"
#include "bfjsonparser/bfmarketcatalogueparser.h"
#include "bfjsonparser/bfplaceordersparser.h"
#include "bfjsonparser/bfaccountsapiparser.h"

#include "bftypes/bfaccountdetailsrsp.h"
#include "bftypes/bfaccountfundsrsp.h"

#include "bftypes/bfevent.h"
#include "bftypes/bfmarket.h"
#include "bftypes/bfselection.h"

#include "bftypes/bfplaceexecutionreport.h"
#include "bftypes/bfplaceinstructionreport.h"
#include "bftypes/bfplaceinstruction.h"


#include "bfenums/bfexecutionreporterrorcode.h"
#include "bfenums/bfexecutionreportstatus.h"
#include "bfenums/bfinstructionreporterrorcode.h"
#include "bfenums/bfinstructionreportstatus.h"



class BfLibUT_JsonParers : public QObject
{
  Q_OBJECT

public:
  BfLibUT_JsonParers();


private Q_SLOTS:
  void tc_apiNgExceptionEmptyParsing();
  void tc_apiNgExceptionSuccessfullParsing();

  void tc_bfMarketCatalogueEmptyParser();
  void tc_bfMarketCatalogueSuccessfullParser();

  void tc_placeOrdersJsonCreator();

  void tc_getAccountFundsJsonCreator();
  void tc_getAccountDetailsJsonCreator();

  void tc_getAccountFundsJsonParser();
  void tc_getAccountDetailsJsonParser();

  void tc_placeOrdersEmptyRspJsonParsing();
  void tc_placeOrdersSuccessfullRspJsonParsing();
  void tc_placeOrdersInsufficientFundsJsonParsing();
  void tc_placeOrdersInvalidBetsizeJsonParsing();
};

BfLibUT_JsonParers::BfLibUT_JsonParers()
{
}

void BfLibUT_JsonParers::tc_apiNgExceptionEmptyParsing()
{
  QString answer = "";

  BfApiNgException *ex = BfApiNgExceptionParser::parseException(answer);


  QVERIFY2(BfApiNgExceptionParser::parseException(answer) != 0, "Non-parsable answer");
  QVERIFY2(ex->m_errorType == BfApiNgException::INTERNAL_ERR, QString("%1: %2").arg("code faulty", ex->toString()).toStdString().c_str());
}

void BfLibUT_JsonParers::tc_apiNgExceptionSuccessfullParsing()
{
  QFile data(":/jsonData/json_correctApiNgException.json");
  QVERIFY(data.open(QIODevice::ReadOnly | QIODevice::Text));
  QString answer = data.readAll();

  BfApiNgException *ex = BfApiNgExceptionParser::parseException(answer);

  QVERIFY2(ex != 0, "Parsable exception");

  QVERIFY2(ex->m_apiNgCode == -32099, "code faulty");
  QVERIFY2(ex->m_apiNgMessage == "ANGX-0001", "message faulty");
  QVERIFY2(ex->m_apiNgErrorDetails == "", "errorDetails faulty");
  QVERIFY2(ex->m_apiNgErrorCode == "TOO_MUCH_DATA", "errorCode faulty");
  QVERIFY2(ex->m_apiNgRequestUUID == "prdang044-07291214-005a69b6ce", "requestUUID faulty");
}

void BfLibUT_JsonParers::tc_bfMarketCatalogueEmptyParser()
{
  QString answer = "";

  BfApiNgException *ex = BfApiNgExceptionParser::parseException(answer);


  QVERIFY2(BfApiNgExceptionParser::parseException(answer) != 0, "Non-parsable answer");
  QVERIFY2(ex->m_errorType == BfApiNgException::INTERNAL_ERR, QString("%1: %2").arg("code faulty", ex->toString()).toStdString().c_str());
}

void BfLibUT_JsonParers::tc_bfMarketCatalogueSuccessfullParser()
{
  QFile data(":/jsonData/json_correctApiNgException.json");
  QVERIFY(data.open(QIODevice::ReadOnly | QIODevice::Text));
  QString answer = data.readAll();

  BfApiNgException *ex = BfApiNgExceptionParser::parseException(answer);

  QVERIFY2(ex != 0, "Parsable exception");

  QVERIFY2(ex->m_apiNgCode == -32099, "code faulty");
  QVERIFY2(ex->m_apiNgMessage == "ANGX-0001", "message faulty");
  QVERIFY2(ex->m_apiNgErrorDetails == "", "errorDetails faulty");
  QVERIFY2(ex->m_apiNgErrorCode == "TOO_MUCH_DATA", "errorCode faulty");
  QVERIFY2(ex->m_apiNgRequestUUID == "prdang044-07291214-005a69b6ce", "requestUUID faulty");
}

void BfLibUT_JsonParers::tc_placeOrdersJsonCreator() {
  /*
    {"jsonrpc": "2.0",
     "method": "SportsAPING/v1.0/placeOrders",
     "params": {"marketId":"1.120224362",
                "instructions":[
                     {"selectionId":"1222679",
                      "handicap":"0",
                      "side":"BACK",
                      "orderType":"LIMIT",
                      "limitOrder":{
                         "size":"30",
                         "price":"1.07",
                         "persistenceType":"LAPSE"}}]}, "id": 1}

   * */
  // Construct
  std::list<BfPlaceInstruction> placeInstructions;
  BfPlaceInstruction pi;
  pi.m_selectionId = 1222679;
  pi.m_handicap = 0.0;
  pi.m_side = BfSide::BACK;
  pi.m_orderType = BfOrderType::LIMIT;
  pi.m_limitOrder.m_size = 30.0;
  pi.m_limitOrder.m_price = 1.07;
  pi.m_limitOrder.m_persistenceType = BfPersistenceType::LAPSE;
  placeInstructions.push_back(pi);
  QJsonObject createdJsonObj;
  BfPlaceOrdersJsonCreator::create("1.120224362",placeInstructions,createdJsonObj);

  // Read correct data
  QFile data(":/jsonData/json_placeOrdersReq.json");
  QVERIFY(data.open(QIODevice::ReadOnly | QIODevice::Text));
  QString correctJsonData = data.readAll();

  // Verify
  QJsonDocument doc(createdJsonObj);
  QString createdJsonData = QString(doc.toJson()).replace(" ","").replace("\r","").replace("\n","").replace("\t","");

  QJsonDocument jsonReq = QJsonDocument::fromJson(correctJsonData.toUtf8());
  QJsonObject correctJsonObject = jsonReq.object();

  // TODO: Not comparing actual objects, not showing fail
  QVERIFY2(correctJsonObject == createdJsonObj, QString("Incorrect %1 %2")
           .arg(correctJsonData,QString(createdJsonData)).toStdString().c_str());
}

void BfLibUT_JsonParers::tc_getAccountFundsJsonCreator() {
  QJsonObject createdJsonObj;
  BfAccountsApiJsonCreator::createGetAccountFunds(createdJsonObj);

  // Read correct data
  QFile data(":/jsonData/json_getAccountFundsReq.json");
  QVERIFY(data.open(QIODevice::ReadOnly | QIODevice::Text));
  QString correctJsonData = data.readAll();

  // Verify
  QJsonDocument doc(createdJsonObj);
  QString createdJsonData = QString(doc.toJson()).replace(" ","").replace("\r","").replace("\n","").replace("\t","");

  QJsonDocument jsonReq = QJsonDocument::fromJson(correctJsonData.toUtf8());
  QJsonObject correctJsonObject = jsonReq.object();

  // TODO: Not comparing actual objects, not showing fail
  QVERIFY2(correctJsonObject == createdJsonObj, QString("Incorrect %1 %2")
           .arg(correctJsonData,QString(createdJsonData)).toStdString().c_str());
}

void BfLibUT_JsonParers::tc_getAccountDetailsJsonCreator() {
  QJsonObject createdJsonObj;
  BfAccountsApiJsonCreator::createGetAccountDetails(createdJsonObj);

  // Read correct data
  QFile data(":/jsonData/json_getAccountDetailsReq.json");
  QVERIFY(data.open(QIODevice::ReadOnly | QIODevice::Text));
  QString correctJsonData = data.readAll();

  // Verify
  QJsonDocument doc(createdJsonObj);
  QString createdJsonData = QString(doc.toJson()).replace(" ","").replace("\r","").replace("\n","").replace("\t","");

  QJsonDocument jsonReq = QJsonDocument::fromJson(correctJsonData.toUtf8());
  QJsonObject correctJsonObject = jsonReq.object();

  // TODO: Not comparing actual objects, not showing fail
  QVERIFY2(correctJsonObject == createdJsonObj, QString("Incorrect %1 %2")
           .arg(correctJsonData,QString(createdJsonData)).toStdString().c_str());
}

void BfLibUT_JsonParers::tc_getAccountFundsJsonParser() {
  // Test empty string
  QString answer = "";
  BfAccountFundsRsp accountFundsRspEmpty;
  BfApiNgException *ex = BfAccountsApiParser::parseGetAccountFunds(answer, accountFundsRspEmpty);

  QVERIFY2(ex != 0, "Non-parsable answer");
  QVERIFY2(ex->m_errorType == BfApiNgException::INTERNAL_ERR,
           QString("%1: %2").arg("code faulty", ex->toString()).toStdString().c_str());

  // Test successfull parsing
  BfAccountFundsRsp accountFundsRsp;
  QFile data(":/jsonData/json_getAccountFundsRsp.json");
  QVERIFY(data.open(QIODevice::ReadOnly | QIODevice::Text));
  answer = data.readAll();

  // Failed parsing
  ex = BfAccountsApiParser::parseGetAccountFunds(answer, accountFundsRsp);

  QVERIFY2(ex == 0, "Parsable exception");

  QVERIFY2(accountFundsRsp.m_availableToBetBalance == 355.89,
           QString("Found %1, expected %2").arg(QString::number(accountFundsRsp.m_availableToBetBalance)).toStdString().c_str());
  QVERIFY(accountFundsRsp.m_exposure == 3.0);
  QVERIFY(accountFundsRsp.m_retainedCommission == 2.0);
  QVERIFY(accountFundsRsp.m_exposureLimit == -50000.0);
  QVERIFY(accountFundsRsp.m_discountRate == 1.0);
  QVERIFY(accountFundsRsp.m_pointsBalance == 10);
}

void BfLibUT_JsonParers::tc_getAccountDetailsJsonParser() {
  // Test empty string
  QString answer = "";
  BfAccountDetailsRsp accountDetailsRspEmpty;
  BfApiNgException *ex = BfAccountsApiParser::parseGetAccountDetails(answer, accountDetailsRspEmpty);

  QVERIFY2(ex != 0, "Non-parsable answer");
  QVERIFY2(ex->m_errorType == BfApiNgException::INTERNAL_ERR,
           QString("%1: %2").arg("code faulty", ex->toString()).toStdString().c_str());

  // Test successfull parsing
  BfAccountDetailsRsp accountDetailsRsp;
  QFile data(":/jsonData/json_getAccountDetailsRsp.json");
  QVERIFY(data.open(QIODevice::ReadOnly | QIODevice::Text));
  answer = data.readAll();

  // Failed parsing
  ex = BfAccountsApiParser::parseGetAccountDetails(answer, accountDetailsRsp);

  QVERIFY2(ex == 0, "Parsable exception");

  QVERIFY(accountDetailsRsp.m_currencyCode == "SEK");
  QVERIFY(accountDetailsRsp.m_firstName == "Tony");
  QVERIFY(accountDetailsRsp.m_lastName == "Karlsson");
  QVERIFY(accountDetailsRsp.m_localeCode == "sv");
  QVERIFY(accountDetailsRsp.m_region == "GBR");
  QVERIFY(accountDetailsRsp.m_timezone == "Europe/London");
  QVERIFY(accountDetailsRsp.m_discountRate == 1.0);
  QVERIFY(accountDetailsRsp.m_pointsBalance == 10);
  QVERIFY(accountDetailsRsp.m_countryCode == "SE");
}


void BfLibUT_JsonParers::tc_placeOrdersEmptyRspJsonParsing() {
  QString answer = "";

  BfPlaceExecutionReport exeReport;

  BfApiNgException *ex = BfPlaceOrdersParser::parse(answer, exeReport);

  QVERIFY2(ex != 0, "Non-parsable answer");
  QVERIFY2(ex->m_errorType == BfApiNgException::INTERNAL_ERR,
           QString("%1: %2").arg("code faulty", ex->toString()).toStdString().c_str());
}

void BfLibUT_JsonParers::tc_placeOrdersSuccessfullRspJsonParsing()
{
  QString answer = "";
  BfPlaceExecutionReport exeReport;

  QFile data(":/jsonData/json_placeOrdersSuccessRsp.json");
  QVERIFY(data.open(QIODevice::ReadOnly | QIODevice::Text));
  answer = data.readAll();

  // Failed parsing
  BfApiNgException *ex = BfPlaceOrdersParser::parse(answer, exeReport);

  QVERIFY2(ex == 0, "Parsable exception");

  QVERIFY2(exeReport.m_status == BfExecutionReportStatus::SUCCESS, "Success");
  QVERIFY2(exeReport.m_errorCode == BfExecutionErrorReportCode::NONE, "Error code");
  QVERIFY2(exeReport.m_marketId == "1.120224362", "MarketId");

  QVERIFY2(exeReport.m_instructionReports.size() == 1, "size inst reports");
  BfPlaceInstructionReport instrReport = exeReport.m_instructionReports.front();
  QVERIFY2(instrReport.m_status == BfInstructionReportStatus::SUCCESS,
           "inst status not succesfull");

  QVERIFY2(instrReport.m_betId == "54512223950", "betId");
  QDateTime correct = QDateTime(QDate(2015,8,26), QTime(20,37,14), Qt::UTC);
  QVERIFY2(instrReport.m_averagePriceMatched == 1.69, "avgPriceMatched");

  QVERIFY2(instrReport.m_sizeMatched == 30.0, "sizeMatched");
  QVERIFY2(instrReport.m_placeDate == correct,
           QString("placeDate found=%1, correct=%2").arg(exeReport.m_instructionReports.front().m_placeDate.toString(), correct.toString()).toStdString().c_str());

  QVERIFY2(instrReport.m_placeInstruction.m_selectionId == 1222679,
           QString("selId found=%1, correct=1222679").arg(QString::number(exeReport.m_instructionReports.front().m_placeInstruction.m_selectionId)).toStdString().c_str());
  QVERIFY2(instrReport.m_placeInstruction.m_handicap == 0.0, "handicap");
  QVERIFY2(instrReport.m_placeInstruction.m_orderType == BfOrderType::LIMIT, "orderType");
  QVERIFY2(instrReport.m_placeInstruction.m_side == BfSide::BACK, "side");
  QVERIFY2(instrReport.m_placeInstruction.m_limitOrder.m_price == 1.07, "price");
  QVERIFY2(instrReport.m_placeInstruction.m_limitOrder.m_size == 30.0, "size");
  QVERIFY2(instrReport.m_placeInstruction.m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "persistenceType");
}

void BfLibUT_JsonParers::tc_placeOrdersInsufficientFundsJsonParsing() {
  QString answer = "";
  BfPlaceExecutionReport exeReport;

  QFile data(":/jsonData/json_placeOrdersInsufficientFundsRsp.json");
  QVERIFY(data.open(QIODevice::ReadOnly | QIODevice::Text));
  answer = data.readAll();

  // Failed parsing
  BfApiNgException *ex = BfPlaceOrdersParser::parse(answer, exeReport);

  QVERIFY2(ex == 0, "Parsable exception");

  QVERIFY2(exeReport.m_status == BfExecutionReportStatus::FAILURE, "Failure");
  QVERIFY2(exeReport.m_errorCode == BfExecutionErrorReportCode::INSUFFICIENT_FUNDS, "Error code");
  QVERIFY2(exeReport.m_marketId == "1.120224362", "MarketId");

  QVERIFY2(exeReport.m_instructionReports.size() == 1, "size inst reports");

  BfPlaceInstructionReport instrReport = exeReport.m_instructionReports.front();
  QVERIFY2(instrReport.m_status == BfInstructionReportStatus::FAILURE,
           "inst status not failure");
  QVERIFY2(instrReport.m_errorCode == BfInstructionReportErrorCode::ERROR_IN_ORDER, "inst error code");
  QVERIFY2(instrReport.m_betId == "", "betId");

  QVERIFY2(instrReport.m_averagePriceMatched == 0.0, "avgPriceMatched");

  QVERIFY2(instrReport.m_sizeMatched == 0.0, "sizeMatched");
  //QDateTime correct = QDateTime(QDate(2015,8,26), QTime(20,37,14), Qt::UTC);
  //QVERIFY2(instrReport.m_placeDate == correct,
  //        QString("placeDate found=%1, correct=%2").arg(exeReport.m_instructionReports.front().m_placeDate.toString(), correct.toString()).toStdString().c_str());

  QVERIFY2(instrReport.m_placeInstruction.m_selectionId == 1222679,
           QString("selId found=%1, correct=1222679").arg(QString::number(exeReport.m_instructionReports.front().m_placeInstruction.m_selectionId)).toStdString().c_str());
  QVERIFY2(instrReport.m_placeInstruction.m_handicap == 0.0, "handicap");
  QVERIFY2(instrReport.m_placeInstruction.m_orderType == BfOrderType::LIMIT, "orderType");
  QVERIFY2(instrReport.m_placeInstruction.m_side == BfSide::BACK, "side");
  QVERIFY2(instrReport.m_placeInstruction.m_limitOrder.m_price == 1.64, "price");
  QVERIFY2(instrReport.m_placeInstruction.m_limitOrder.m_size == 30.0, "size");
  QVERIFY2(instrReport.m_placeInstruction.m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "persistenceType");
}

void BfLibUT_JsonParers::tc_placeOrdersInvalidBetsizeJsonParsing() {
  QString answer = "";
  BfPlaceExecutionReport exeReport;

  QFile data(":/jsonData/json_placeOrdersInvalidBetsizeRsp.json");
  QVERIFY(data.open(QIODevice::ReadOnly | QIODevice::Text));
  answer = data.readAll();

  // Failed parsing
  BfApiNgException *ex = BfPlaceOrdersParser::parse(answer, exeReport);

  QVERIFY2(ex == 0, "Parsable exception");

  QVERIFY2(exeReport.m_status == BfExecutionReportStatus::FAILURE, "Failure");
  QVERIFY2(exeReport.m_errorCode == BfExecutionErrorReportCode::BET_ACTION_ERROR, "Error code");
  QVERIFY2(exeReport.m_marketId == "1.120224362", "MarketId");

  QVERIFY2(exeReport.m_instructionReports.size() == 1, "size inst reports");

  BfPlaceInstructionReport instrReport = exeReport.m_instructionReports.front();
  QVERIFY2(instrReport.m_status == BfInstructionReportStatus::FAILURE,
           "inst status not failure");
  QVERIFY2(instrReport.m_errorCode == BfInstructionReportErrorCode::INVALID_BET_SIZE, "inst error code");
  QVERIFY2(instrReport.m_betId == "", "betId");

  QVERIFY2(instrReport.m_averagePriceMatched == 0.0, "avgPriceMatched");

  QVERIFY2(instrReport.m_sizeMatched == 0.0, "sizeMatched");
  //QDateTime correct = QDateTime(QDate(2015,8,26), QTime(20,37,14), Qt::UTC);
  //QVERIFY2(instrReport.m_placeDate == correct,
  //        QString("placeDate found=%1, correct=%2").arg(exeReport.m_instructionReports.front().m_placeDate.toString(), correct.toString()).toStdString().c_str());

  QVERIFY2(instrReport.m_placeInstruction.m_selectionId == 1222679,
           QString("selId found=%1, correct=1222679").arg(QString::number(exeReport.m_instructionReports.front().m_placeInstruction.m_selectionId)).toStdString().c_str());
  QVERIFY2(instrReport.m_placeInstruction.m_handicap == 0.0, "handicap");
  QVERIFY2(instrReport.m_placeInstruction.m_orderType == BfOrderType::LIMIT, "orderType");
  QVERIFY2(instrReport.m_placeInstruction.m_side == BfSide::BACK, "side");
  QVERIFY2(instrReport.m_placeInstruction.m_limitOrder.m_price == 20.0, "price");
  QVERIFY2(instrReport.m_placeInstruction.m_limitOrder.m_size == 1.64, "size");
  QVERIFY2(instrReport.m_placeInstruction.m_limitOrder.m_persistenceType == BfPersistenceType::LAPSE, "persistenceType");
}

QTEST_APPLESS_MAIN(BfLibUT_JsonParers)

#include "tst_betfairlibunitteststest.moc"
