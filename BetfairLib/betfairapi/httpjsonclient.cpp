#include <QJsonDocument>

#include "betfairapi/httpjsonclient.h"

HttpJsonClient::HttpJsonClient(QObject *parent, BfConfig *bfConfig, QString url) :
  m_bfConfig(bfConfig),
  m_loginApi(0, bfConfig),
  m_url(url)
{
  Q_UNUSED(parent);
  QObject::connect(&m_loginApi, SIGNAL(loginCompleted()), this, SLOT(loginCompleted()));
  QObject::connect(&m_loginApi, SIGNAL(error(BfApiNgException*)),
                   this, SLOT(errorOccurred(BfApiNgException*)));

  connect(&m_networkAccessManager, SIGNAL(finished(QNetworkReply *)),
          this, SLOT(replyFinish(QNetworkReply  *)));
  connect(&m_networkAccessManager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
          this, SLOT(sslErrorsReceived(QNetworkReply*,QList<QSslError>)));
}

void HttpJsonClient::send(QJsonObject jsonObj) {
  m_jsonObjs.push_back(jsonObj);
  execute();
}

void HttpJsonClient::execute() {
  if (m_loginApi.isWaitingForLoginReply()) {
    QTimer::singleShot(3000, this, SLOT(execute()));
  } else if (!m_loginApi.isLoggedIn()) {
    m_loginApi.login();
  } else {

    for (std::list<QJsonObject>::iterator it = m_jsonObjs.begin();
         it != m_jsonObjs.end();) {
      QSslConfiguration sslConfiguration;
      QUrl endPoint;
      endPoint.setUrl(m_url);
      //endPoint.setUrl("https://api.betfair.com/exchange/betting/json-rpc/v1");

      QNetworkRequest request(endPoint);
      request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
      request.setRawHeader("Accept", "application/json");
      request.setRawHeader("X-Application", m_bfConfig->getAppKeyDelayed().toUtf8());
      request.setRawHeader("X-Authentication", m_bfConfig->getSessionToken().toUtf8());
      if (!sslConfiguration.isNull())
        request.setSslConfiguration(sslConfiguration);

      QJsonDocument doc(*it);
      QByteArray data = doc.toJson();

      m_networkAccessManager.post(request, data);

      it = m_jsonObjs.erase(it);
    }
  }
}

void HttpJsonClient::loginCompleted() {
  execute();
}

void HttpJsonClient::replyFinish(QNetworkReply *reply) {
  QString answer = QString::fromUtf8(reply->readAll());
  reply->deleteLater();
  emit replyFinish(answer);
}

void HttpJsonClient::sslErrorsReceived(QNetworkReply *reply,
                                       QList<QSslError>) {
  emit error(NEW_INTERNAL_EXCEPTION("sslErrorsReceived"));
  reply->deleteLater();
}

void HttpJsonClient::errorOccurred(BfApiNgException *ex) {
  emit error(ex);
}
