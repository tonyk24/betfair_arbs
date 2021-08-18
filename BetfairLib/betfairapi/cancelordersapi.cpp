#include <QJsonDocument>
#include "cancelordersapi.h"

#include "bfjsoncreator/bfcancelordersjsoncreator.h"
#include "bfjsonparser/bfcancelordersparser.h"
#include "bftypes/bfcancelexecutionreport.h"

CancelOrdersApi::CancelOrdersApi(QObject *parent, BfConfig *bfConfig) :
  m_bfConfig(bfConfig),
  m_httpJsonClient(0, bfConfig, "https://api.betfair.com/exchange/betting/json-rpc/v1")
{
  Q_UNUSED(parent);

  QObject::connect(&m_httpJsonClient, SIGNAL(replyFinish(QString)),
                   this, SLOT(replyFinish(QString)));

  QObject::connect(&m_httpJsonClient, SIGNAL(error(BfApiNgException*)),
                   this, SLOT(errorOccurred(BfApiNgException*)));
}


void CancelOrdersApi::cancelOrders(QString marketId, std::list<BfCancelInstruction> instructions)
{
  QJsonObject jsonObj;
  BfCancelOrdersJsonCreator::create(marketId, instructions, jsonObj);
  QJsonDocument doc(jsonObj);
  QByteArray data = doc.toJson();
  qDebug() << "cancelOrders= " << QString(data);
  m_httpJsonClient.send(jsonObj);
}

void CancelOrdersApi::replyFinish(QString answer) {
  qDebug() << answer;
  BfCancelExecutionReport cancelExecutionReport;
  BfApiNgException *apiNgEx = BfCancelOrdersParser::parse(answer,cancelExecutionReport);

  if (apiNgEx != 0) {
    emit error(apiNgEx);
  } else {
    emit cancelOrdersResponse(cancelExecutionReport);
  }
}

void CancelOrdersApi::errorOccurred(BfApiNgException *ex) {
  emit error(ex);
}
