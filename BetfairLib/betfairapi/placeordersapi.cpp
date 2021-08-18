#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "betfairapi/placeordersapi.h"
#include "bfjsonparser/bfplaceordersparser.h"
#include "bfjsoncreator/bfplaceordersjsoncreator.h"

PlaceOrdersApi::PlaceOrdersApi(QObject *parent, BfConfig *bfConfig) :
  m_bfConfig(bfConfig),
  m_httpJsonClient(0, bfConfig, "https://api.betfair.com/exchange/betting/json-rpc/v1") {
  Q_UNUSED(parent);
  QObject::connect(&m_httpJsonClient, SIGNAL(replyFinish(QString)),
                   this, SLOT(replyFinish(QString)));

  QObject::connect(&m_httpJsonClient, SIGNAL(error(BfApiNgException*)),
                   this, SLOT(errorOccurred(BfApiNgException*)));
}

void PlaceOrdersApi::placeOrders(QString marketId, std::list<BfPlaceInstruction> placeInstructions) {
  QJsonObject jsonObj;
  BfPlaceOrdersJsonCreator::create(marketId, placeInstructions, jsonObj);
  QJsonDocument doc(jsonObj);
  QByteArray data = doc.toJson();
  qDebug() << "placeOrders= " << QString(data);
  m_httpJsonClient.send(jsonObj);
}

void PlaceOrdersApi::replyFinish(QString answer) {
  BfPlaceExecutionReport executionReport;
  BfApiNgException *apiNgEx = BfPlaceOrdersParser::parse(answer, executionReport);

  if (apiNgEx != 0) {
    emit error(apiNgEx);
  } else {
    emit placeOrdersResponse(executionReport);
  }
}

void PlaceOrdersApi::errorOccurred(BfApiNgException *ex) {
  emit error(ex);
}
