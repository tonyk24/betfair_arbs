#include "betfairapi/marketcatalogueapi.h"
#include "bftypes/bfmarket.h"
#include "betfairfilter/bfmarkettype.h"

#include "bftypes/bfapingexception.h"
#include "bfjsonparser/bfapingexceptionparser.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <map>
#include <list>

#include "bfjsonparser/bfmarketcatalogueparser.h"
#include "bftypes/bfapingexception.h"

#include "bfenums/bfmarketprojection.h"
#include "betfairfilter/bfmarkettype.h"

MarketCatalogueApi::MarketCatalogueApi(QObject *parent, BfConfig *bfConfig) :
  m_bfConfig(bfConfig),
  m_httpJsonClient(0, bfConfig, "https://api.betfair.com/exchange/betting/json-rpc/v1") {
  Q_UNUSED(parent);
  QObject::connect(&m_httpJsonClient, SIGNAL(replyFinish(QString)),
                   this, SLOT(replyFinish(QString)));

  QObject::connect(&m_httpJsonClient, SIGNAL(error(BfApiNgException*)),
                   this, SLOT(errorOccurred(BfApiNgException*)));
}

void MarketCatalogueApi::get(const BetfairMarketFilter &marketFilter,
                             const std::list<BfMarketProjection::Enum> &marketProjections) {
  QJsonObject jsonObj;
  jsonObj[QString("jsonrpc")] = QString("2.0");
  jsonObj[QString("id")] = QJsonValue(1);

  jsonObj[QString("method")] = QString("SportsAPING/v1.0/listMarketCatalogue");

  /*
   * '{"jsonrpc": "2.0", "method": "SportsAPING/v1.0/listMarketCatalogue",
   * "params":
   *   {"filter":{"eventTypeIds":["' + eventTypeID + '"],
   * "marketCountries":["GB"],
   * "marketTypeCodes":["WIN"],'\
   *
   * [{"jsonrpc": "2.0", "method": "SportsAPING/v1.0/listMarketCatalogue",
   * "params": {"filter":
   *             {"marketIds":["1.118838770"]}
   *          ,"maxResults":"1",
   *           "marketProjection":["MARKET_DESCRIPTION","RUNNER_DESCRIPTION"]},
   * "id": 1}]"
   * */
  QJsonObject jsonObjParams;

  QJsonObject jsonObjFilter;

  QJsonArray jsonArray;
  for (std::list<QString>::const_iterator it = marketFilter.m_eventIds.begin();
       it != marketFilter.m_eventIds.end(); it++) {
    //qDebug() << "adding eventId= " << *it;
    jsonArray.append(QJsonValue(*it));
  }
  jsonObjFilter[QString("eventIds")] = jsonArray;
  jsonObjParams[QString("maxResults")] = QJsonValue(marketFilter.m_maxResults);
  QJsonArray marketProjArray;
  for (std::list<BfMarketProjection::Enum>::const_iterator it = marketProjections.begin();
       it != marketProjections.end(); it++) {
    marketProjArray.append(QJsonValue(BfMarketProjection::toStr(*it)));
  }
  QJsonArray marketTypeCodes;
  for (std::list<BfMarketType::Type>::const_iterator it = marketFilter.m_marketBettingTypes.begin();
       it != marketFilter.m_marketBettingTypes.end(); it++) {
    marketTypeCodes.append((QJsonValue(BfMarketType::toString(*it))));
  }
  jsonObjFilter[QString("marketTypeCodes")] = marketTypeCodes;

  jsonObjParams[QString("marketProjection")] = marketProjArray;

  jsonObjParams[QString("filter")] = jsonObjFilter;

  jsonObj[QString("params")] = jsonObjParams;

  QJsonDocument jDoc(jsonObj);

  //QJsonDocument doc(jsonObj);
  //QString strJson(doc.toJson(QJsonDocument::Compact));
  //qDebug() << strJson;

  m_httpJsonClient.send(jsonObj);
}

void MarketCatalogueApi::replyFinish(QString answer) {
  std::map<QString, std::list<BetfairMarket> > markets;

  BfApiNgException *apiNgEx = BfMarketCatalogueParser::parse(answer, markets);

  if (apiNgEx != 0) {
    emit error(apiNgEx);
  } else {
    // Send result, for one event at the time
    for (std::map<QString, std::list<BetfairMarket> >::iterator mapIt = markets.begin();
         mapIt != markets.end(); mapIt++) {

      for (std::list<BetfairMarket>::iterator itMarket = mapIt->second.begin();
           itMarket != mapIt->second.end(); itMarket++) {
        //qDebug() << "event= " << mapIt->first;
        //qDebug() << "market: id= " << itMarket->m_marketId << ", name= " << itMarket->m_marketName
        //         << ", competition= " << BfCompetition::toStr(itMarket->m_competition)
        //         << ", compId= " << QString::number(static_cast<int>(itMarket->m_competition));
      }

      emit valueChanged(mapIt->first, mapIt->second);
    }
  }
}

void MarketCatalogueApi::errorOccurred(BfApiNgException *ex) {
  emit error(ex);
}

