#ifndef BFMARKETCATALOGUEPARSER_H
#define BFMARKETCATALOGUEPARSER_H

#include <map>
#include <list>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

#include "bftypes/bfmarket.h"
#include "bfjsonparser/bfapingexceptionparser.h"

class BfMarketCatalogueParser {
public:
  static BfApiNgException * parse(const QString &answer,
                                  std::map<QString, std::list<BetfairMarket> > &markets) {
    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());

    QJsonObject jsonObj = jsonResponse.object();

    /*
  "Response truncated to 4,000 chars:
  [{"jsonrpc":"2.0","result":
                [{"marketId":"1.118838770","marketName":"Asian Handicap","totalMatched":0.0,
                     "runners":
                           [{"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":-4.0,"sortPriority":1},
                            {"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":4.0,"sortPriority":2},
                            {"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":-3.75,"sortPriority":3},
                            {"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":3.75,"sortPriority":4},
                            {"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":-3.5,"sortPriority":5},
                            {"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":3.5,"sortPriority":6},
                            {"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":-3.25,"sortPriority":7},
                            {"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":3.25,"sortPriority":8},{"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":-3.0,"sortPriority":9},{"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":3.0,"sortPriority":10},{"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":-2.75,"sortPriority":11},{"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":2.75,"sortPriority":12},{"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":-2.5,"sortPriority":13},{"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":2.5,"sortPriority":14},{"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":-2.25,"sortPriority":15},{"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":2.25,"sortPriority":16},{"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":-2.0,"sortPriority":17},{"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":2.0,"sortPriority":18},{"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":-1.75,"sortPriority":19},{"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":1.75,"sortPriority":20},{"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":-1.5,"sortPriority":21},{"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":1.5,"sortPriority":22},{"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":-1.25,"sortPriority":23},{"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":1.25,"sortPriority":24},{"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":-1.0,"sortPriority":25},{"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":1.0,"sortPriority":26},{"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":-0.75,"sortPriority":27},{"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":0.75,"sortPriority":28},{"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":-0.5,"sortPriority":29},{"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":0.5,"sortPriority":30},{"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":-0.25,"sortPriority":31},{"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":0.25,"sortPriority":32},{"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":0.0,"sortPriority":33},{"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":0.0,"sortPriority":34},{"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":0.25,"sortPriority":35},{"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":-0.25,"sortPriority":36},{"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":0.5,"sortPriority":37},{"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":-0.5,"sortPriority":38},{"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":0.75,"sortPriority":39},{"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":-0.75,"sortPriority":40},{"selectionId":197970,"runnerName":"Maccabi Tel Aviv","handicap":1.0,"sortPriority":41},{"selectionId":5538497,"runnerName":"Hapoel Kiryat Shmona","handicap":-1.0,"sortPriority":42},{"selectionId":197970,"runnerName":"Maccabi Tel Aviv"," Controller.js:686:0

       * */

    // Parse
    if (jsonObj["error"].isObject()) {
      return BfApiNgExceptionParser::parseException(answer);
    }
    else if (jsonObj["result"].isArray())
    {
      QJsonArray jsonArray = jsonObj["result"].toArray();
      for (QJsonArray::iterator it = jsonArray.begin();
           it != jsonArray.end(); it++) {
        QJsonObject marketObj = (*it).toObject();

        QString eventId = marketObj["event"].toObject()["id"].toString();
        BetfairMarket market(QString(marketObj["marketId"].toString()),
            QString(marketObj["marketName"].toString()),0.0);

        if (marketObj["competition"].isObject()) {
          QJsonObject compJsonObj = marketObj["competition"].toObject();
          QString id = compJsonObj[QString("id")].toString();
          bool ok = false;
          int idInt = id.toInt(&ok);
          if (ok) {
            market.m_competition = BfCompetition::toEnum(idInt);
          }
        } else {
          qDebug() << "No competition found!!";
        }

        QJsonArray runnersArray = marketObj[QString("runners")].toArray();
        for (QJsonArray::iterator runnerIt = runnersArray.begin();
             runnerIt != runnersArray.end(); runnerIt++) {
          QJsonObject runnerObj = (*runnerIt).toObject();
          market.m_selections.push_back(BetfairSelection((qint64)runnerObj["selectionId"].toDouble(),
                                        runnerObj[QString("runnerName")].toString()));
        }
        if (markets.find(eventId) == markets.end()) {
          markets.insert(std::make_pair(eventId, std::list<BetfairMarket>()));
        }
        markets[eventId].push_back(market);
      }
    }
    else {
      qWarning() << "MarketCatalogueApi::replyFinish: Excpeting result array";
      return NEW_INTERNAL_EXCEPTION("Excpeting result array");
    }

    return 0;
  }
};

#endif // BFMARKETCATALOGUEPARSER_H

