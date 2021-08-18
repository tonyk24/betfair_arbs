#ifndef BFEVENTRESULTLISTPARSER_H
#define BFEVENTRESULTLISTPARSER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QString>
#include <QTextStream>

#include "bftypes/bfapingexception.h"

class BfEventResultsListParser {
public:
  static BfApiNgException * parse(const QString &answer,
                                   std::list<BfEvent> &events) {
    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());

    QJsonObject jsonObj = jsonResponse.object();

    BfApiNgException *apiNgEx = 0;

    if (jsonObj["error"].isObject()) {
      apiNgEx = BfApiNgExceptionParser::parseException(answer);
    } else if (jsonObj["result"].isArray()) {
      QJsonArray jsonArray = jsonObj["result"].toArray();
      for (QJsonArray::const_iterator it = jsonArray.begin();
           it != jsonArray.end(); it++) {
        QJsonObject eventObj = (*it).toObject();
        QJsonObject eventItemObj = eventObj["event"].toObject();
        BfEvent bfEvent = BfEvent(QString(eventItemObj["id"].toString()),
            QString(eventItemObj["name"].toString()),
            QString(eventItemObj["countryCode"].toString()),
            QString(eventItemObj["timezone"].toString()),
            QString(eventItemObj["openDate"].toString()));
        events.push_back(bfEvent);
      }
    } else if (answer.size() == 0) {
      // Aperentyl empty sometimes, accept..
    }
      else {
      QTextStream ts( stdout );
      ts << answer;
      ts << "Expecting object";
      apiNgEx = NEW_INTERNAL_EXCEPTION(QString("Excpecting object, got answer %1").arg(answer));
    }

    return apiNgEx;
  }
};

#endif // BFEVENTRESULTLISTPARSER_H

