#include <QString>
#include <QtTest>

#include "bfjsonparser/bfapingexceptionparser.h"
#include "bfjsonparser/bfplaceordersparser.h"

class BfLibUT_placeOrders : public QObject
{
  Q_OBJECT

public:
  BfLibUT_placeOrders();

private Q_SLOTS:
  void tc1_placeOrdersSuccessfullRspJsonParsing();
};

BfLibUT_placeOrders::BfLibUT_placeOrders()
{
}

void BfLibUT_placeOrders::tc1_placeOrdersSuccessfullRspJsonParsing()
{
  QString answer = "";

  BfPlaceExecutionReport exeReport;

  BfApiNgException *ex = BfPlaceOrdersParser::parse(answer, exeReport);

  QVERIFY2(ex != 0, "Non-parsable answer");
  QVERIFY2(ex->m_errorType == BfApiNgException::INTERNAL_ERR,
           QString("%1: %2").arg("code faulty", ex->toString()).toStdString().c_str());

  QFile data(":/json_placeOrdersSuccessRsp.json");
  QVERIFY(data.open(QIODevice::ReadOnly | QIODevice::Text));
  answer = data.readAll();

  // Failed parsing
  ex = BfPlaceOrdersParser::parse(answer, exeReport);

  QVERIFY2(ex != 0, "Parsable exception");
}

QTEST_APPLESS_MAIN(BfLibUT_placeOrders)

#include "tst_bflib_placeorderstest.moc"

