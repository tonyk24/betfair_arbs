#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "extsitesp.h"

ExtSiteSP::ExtSiteSP(QObject *parent)
{

}

void ExtSiteSP::update()
{
  QNetworkAccessManager *manager = new QNetworkAccessManager(this);
  connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(requestReceived(QNetworkReply*)));
  QNetworkRequest req = QNetworkRequest(QUrl("https://api.www.svenskaspel.se/search/query/?ctx=draw&type=oddsetlist&sort=payload.draw.categoryId;desc,payload.draw.regCloseTime,payload.draw.match.matchStart,payload.draw.league.id,payload.draw.id&andfilter=payload.draw.drawState;Open&notfilter=payload.draw.match.status;Speluppeh%C3%A5ll&infilter=payload.draw.league.uniqueLeagueId;12692691:12694415:12692698:12692830:12692630:12692458:12692737:12692645:12692650:12692699:12692626:12692823:12692834:12692833:12692620:12692619:12692628:12692667:12692679:12692725:12692783:12692200:12692793:12692806:12692804:12692802:12692803:12692820:12692842:12692651:12692850&offset=0&count=40&_=1476915398101"));
  req.setHeader(QNetworkRequest::UserAgentHeader, QString("Mozilla/5.0 (Windows NT 10.0; WOW64; rv:49.0) Gecko/20100101 Firefox/49.0"));
  manager->get(req);

  //
}

void ExtSiteSP::requestReceived(QNetworkReply *reply)
{
  reply->deleteLater();

  if(reply->error() == QNetworkReply::NoError) {
    // Get the http status code
    int v = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (v >= 200 && v < 300) // Success
    {
      // Here we got the final reply
      QString replyText = reply->readAll();
      //ui->txt_debug->appendPlainText(replyText);
      parseResult(replyText);
    }
    else if (v >= 300 && v < 400) // Redirection
    {
      // Get the redirection url
      QUrl newUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
      // Because the redirection url can be relative,
      // we have to use the previous one to resolve it
      newUrl = reply->url().resolved(newUrl);

      QNetworkAccessManager *manager = reply->manager();
      QNetworkRequest redirection(newUrl);
      QNetworkReply *newReply = manager->get(redirection);

      return; // to keep the manager for the next request
    }
  }
  else
  {
    parseResult(reply->errorString());
  }

  reply->manager()->deleteLater();
}

void ExtSiteSP::parseResult(QString resultStr)
{
  std::list<ExtSiteSPOdds> results;

  QJsonDocument jsonResponse = QJsonDocument::fromJson(resultStr.toUtf8());

  QJsonObject jsonObj = jsonResponse.object();

  QJsonArray resultArray = jsonObj["result"].toArray();
  for (QJsonArray::iterator resIt = resultArray.begin();
       resIt != resultArray.end(); resIt++) {
    ExtSiteSPOdds resItem;
    QJsonObject resultJsonObj = (*resIt).toObject();
    QJsonObject payLoadJsonObj = resultJsonObj["payload"].toObject();
    QJsonObject drawJsonObj = payLoadJsonObj["draw"].toObject();
    resItem.m_sportType = drawJsonObj["sport"].toObject()["name"].toString();
    resItem.m_league = drawJsonObj["league"].toObject()["name"].toString();
    resItem.m_startTime = QDateTime().fromString(drawJsonObj["match"].toObject()["matchStart"].toString());
    // Parse home and away team
    QJsonArray participantsArray = drawJsonObj["match"].toObject()["participants"].toArray();
    for (QJsonArray::iterator parIt = participantsArray.begin();
         parIt != participantsArray.end(); parIt++) {
      QJsonObject participantJsonObj = (*parIt).toObject();
      if (participantJsonObj["type"].toString() == "home")
        resItem.m_homeTeam = participantJsonObj["name"].toString();
      else if (participantJsonObj["type"].toString() == "away")
        resItem.m_awayTeam = participantJsonObj["name"].toString();
    }
    resItem.m_title = resItem.m_homeTeam + " v " + resItem.m_awayTeam;
    //qDebug() << "title= " << resItem.m_title;

    // Parse odds
    QJsonArray eventsArray = drawJsonObj["events"].toArray();
    for (QJsonArray::iterator eventIt = eventsArray.begin();
         eventIt != eventsArray.end(); eventIt++) {
      QJsonObject eventJsonObj = (*eventIt).toObject();
      QJsonArray outcomesArray = eventJsonObj["outcomes"].toArray();
      for (QJsonArray::iterator outcomesIt = outcomesArray.begin();
           outcomesIt != outcomesArray.end(); outcomesIt++) {
        QJsonObject outcomeJsonObj = (*outcomesIt).toObject();
        if (outcomeJsonObj["type"] == "HomeWin")
        {
          resItem.m_homeOdds = outcomeJsonObj["items"].toArray().first().toObject()["odds"].toString().replace(",", ".").toDouble();
        } else if(outcomeJsonObj["type"] == "Draw")
        {
          resItem.m_drawOdds = outcomeJsonObj["items"].toArray().first().toObject()["odds"].toString().replace(",", ".").toDouble();
        } else if(outcomeJsonObj["type"] == "AwayWin")
        {
          resItem.m_awayOdds = outcomeJsonObj["items"].toArray().first().toObject()["odds"].toString().replace(",", ".").toDouble();
        }
      }
    }
    //qDebug() << "homeOdds= " << resItem.m_homeOdds;
    //qDebug() << "m_drawOdds= " << resItem.m_drawOdds;
    //qDebug() << "m_awayOdds= " << resItem.m_awayOdds;

    results.push_back(resItem);
  }

  emit resultUpdated(results);
}
