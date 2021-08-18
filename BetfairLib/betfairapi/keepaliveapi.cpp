#include <QJsonDocument>
#include <QJsonObject>

#include "keepaliveapi.h"

#include "bftypes/bfapingexception.h"
#include "bfjsonparser/bfapingexceptionparser.h"

KeepAliveApi::KeepAliveApi(QObject *parent, BfConfig *bfConfig) :
  m_bfConfig(bfConfig) {
  Q_UNUSED(parent);

  connect (&m_networkAccessManager, SIGNAL(finished(QNetworkReply *)),
           this, SLOT(replyFinishToken (QNetworkReply  *)));
}

void KeepAliveApi::sendKeepAlive() {
  QSslConfiguration sslConfiguration;
  QUrl endPoint;
  endPoint.setUrl("https://identitysso.betfair.com/api/keepAlive");

  QNetworkRequest request(endPoint);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  request.setRawHeader("Accept", "application/json");
  request.setRawHeader("X-Application", m_bfConfig->getAppKey().toUtf8());
  request.setRawHeader("X-Authentication", m_bfConfig->getSessionToken().toUtf8());
  if (!sslConfiguration.isNull())
    request.setSslConfiguration(sslConfiguration);

  QByteArray data = "";

  m_networkAccessManager.post(request, data);
}

void KeepAliveApi::replyFinishToken(QNetworkReply *reply)
{
  QString answer = QString::fromUtf8(reply->readAll());
  reply->deleteLater();

  QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());

  QJsonObject jsonObj = jsonResponse.object();

  BfApiNgException *apiNgEx = 0;

  if (jsonObj["error"].isObject()) {
    apiNgEx = BfApiNgExceptionParser::parseException(answer);
  } else if (jsonObj["status"].toString().compare("SUCCESS") == 0)
  {
    m_bfConfig->setSessionToken(jsonObj["token"].toString());
    //qDebug() << "token= " << jsonObj["token"].toString();
    //qDebug() << "appkey= " << jsonObj["product"].toString();
  }
  else
  {
    apiNgEx = NEW_INTERNAL_EXCEPTION("FAILURE" + answer);
  }

  if (apiNgEx != 0) {
    emit error(apiNgEx);
  }
}
