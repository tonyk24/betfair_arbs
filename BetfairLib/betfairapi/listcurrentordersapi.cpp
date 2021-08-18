#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "listcurrentordersapi.h"
#include "bfjsonparser/bflistcurrentordersparser.h"
#include "bfjsoncreator/bflistcurrentordersjsoncreator.h"

ListCurrentOrdersApi::ListCurrentOrdersApi(QObject *parent, BfConfig *bfConfig) :
  m_bfConfig(bfConfig),
  m_httpJsonClient(0, bfConfig, "https://api.betfair.com/exchange/betting/json-rpc/v1") {
  Q_UNUSED(parent);
  QObject::connect(&m_httpJsonClient, SIGNAL(replyFinish(QString)),
                   this, SLOT(replyFinish(QString)));

  QObject::connect(&m_httpJsonClient, SIGNAL(error(BfApiNgException*)),
                   this, SLOT(errorOccurred(BfApiNgException*)));
}

void ListCurrentOrdersApi::listCurrentOrders(std::list<QString> marketIds) {
  QJsonObject jsonObj;
  BfListCurrentOrdersJsonCreator::create(marketIds, jsonObj);
  //QJsonDocument doc(jsonObj);
  //QByteArray data = doc.toJson();
  //qDebug() << "listCurrentOrders= " << QString(data);
  m_httpJsonClient.send(jsonObj);
}

void ListCurrentOrdersApi::replyFinish(QString answer) {
  //qDebug() << answer;
  std::list<BfCurrentOrder> currentOrders;
  BfApiNgException *apiNgEx = BfListCurrentOrdersParser::parse(answer,currentOrders);

  if (apiNgEx != 0) {
    emit error(apiNgEx);
  } else {
    emit listCurrentOrdersResponse(currentOrders);
  }
}

void ListCurrentOrdersApi::errorOccurred(BfApiNgException *ex) {
  emit error(ex);
}

