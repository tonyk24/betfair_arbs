
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "betfairapi/eventsapi.h"
#include "misc/bfconfig.h"
#include "bftypes/bfapingexception.h"
#include "bfjsonparser/bfapingexceptionparser.h"
#include "bfjsonparser/bfeventresultlistparser.h"

EventsApi::EventsApi(QObject *parent, BfConfig *bfConfig) :
  m_bfConfig(bfConfig),
  m_httpJsonClient(0, bfConfig, "https://api.betfair.com/exchange/betting/json-rpc/v1")
{
  Q_UNUSED(parent);

  QObject::connect(&m_httpJsonClient, SIGNAL(replyFinish(QString)),
                   this, SLOT(replyFinish(QString)));
  QObject::connect(&m_httpJsonClient, SIGNAL(error(BfApiNgException*)),
                   this, SLOT(errorOccurred(BfApiNgException*)));
}

EventsApi::~EventsApi() {
  QObject::disconnect(&m_httpJsonClient, SIGNAL(replyFinish(QString)),
                      this, SLOT(replyFinish(QString)));
  QObject::disconnect(&m_httpJsonClient, SIGNAL(error(BfApiNgException*)),
                   this, SLOT(errorOccurred(BfApiNgException*)));
}

void EventsApi::get(const BetfairMarketFilter &marketFilter) {
  /*
   * [{"jsonrpc": "2.0",
   *  "method": "SportsAPING/v1.0/listEventTypes",
   *  "params": {"filter":
   *                  {"marketStartTime":
   *                      {"from":"2015-06-06T18:00:00Z",
   *                       "to":"2015-06-07T19:00:00Z"}}},
   *  "id": 1}]"
   * */
  QJsonObject jsonObj;
  jsonObj[QString("jsonrpc")] = QString("2.0");
  jsonObj[QString("id")] = QJsonValue(1);
  jsonObj[QString("method")] = QString("SportsAPING/v1.0/listEvents");

  QJsonObject jsonObjParams;

  QJsonObject jsonObjFilter;

  QJsonArray jsonArray;
  //qDebug() << "eventtypeids= " << QString::number(marketFilter.m_eventTypeIds.size());
  for (std::list<QString>::const_iterator it = marketFilter.m_eventTypeIds.begin();
       it != marketFilter.m_eventTypeIds.end(); it++)
  {
    QString val=*it;
    jsonArray.append(QJsonValue(val.toInt()));
  }
  jsonObjFilter[QString("eventTypeIds")] = jsonArray;

  QJsonArray jsonArrayCompetitions;
  if(!marketFilter.m_competitionIds.empty()) {
    for (std::list<QString>::const_iterator it = marketFilter.m_competitionIds.begin();
         it != marketFilter.m_competitionIds.end(); it++) {
      jsonArrayCompetitions.append(QJsonValue(*it));
    }
    jsonObjFilter[QString("competitionIds")] = jsonArrayCompetitions;
  }

  if (marketFilter.m_startAfter && marketFilter.m_startBefore) {
    QJsonObject jsonObjMarketStartTime;

    jsonObjMarketStartTime[QString("from")] = marketFilter.m_startAfter->toString("yyyy-MM-ddThh:mm:ss.zzzZ");
    jsonObjMarketStartTime[QString("to")] = marketFilter.m_startBefore->toString("yyyy-MM-ddThh:mm:ss.zzzZ");

    jsonObjFilter[QString("marketStartTime")] = jsonObjMarketStartTime;
  }
  jsonObjParams[QString("filter")] = jsonObjFilter;

  jsonObj[QString("params")] = jsonObjParams;



  m_httpJsonClient.send(jsonObj);
  //QJsonDocument doc(jsonObj);
  //QString strJson(doc.toJson(QJsonDocument::Compact));
  //qDebug() << "Sent http>JsonCLient request.." << strJson;
}

void EventsApi::replyFinish(QString answer) {

  std::list<BfEvent> events;

  BfApiNgException *apiNgEx = BfEventResultsListParser::parse(answer, events);

  if (apiNgEx != 0) {
    emit error(apiNgEx);
  }

  emit valueChanged(events);
}

void EventsApi::errorOccurred(BfApiNgException *ex) {
  emit error(ex);
}
