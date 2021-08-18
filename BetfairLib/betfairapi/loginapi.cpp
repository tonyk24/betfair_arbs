#include <QJsonDocument>
#include <QJsonObject>

#include "betfairapi/loginapi.h"

#include "bftypes/bfapingexception.h"
#include "bfjsonparser/bfapingexceptionparser.h"

bool LoginApi::m_loggedIn = false;
bool LoginApi::m_waitingLoginReply = false;

LoginApi::LoginApi(QObject *parent, BfConfig *bfConfig) :
  m_bfConfig(bfConfig)
{
  Q_UNUSED(parent);
  connect (&m_networkAccessManager, SIGNAL(finished(QNetworkReply *)),
           this, SLOT(replyFinishToken (QNetworkReply  *)));
  connect(&m_networkAccessManager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
          this, SLOT(sslErrorsReceived(QNetworkReply*,QList<QSslError>)));
}

void LoginApi::login() {
  m_waitingLoginReply = true;
  QSslConfiguration sslConfiguration;
  QUrl endPoint;
  endPoint.setUrl("https://identitysso.betfair.com/api/login");

  QNetworkRequest request(endPoint);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  request.setRawHeader("Accept", "application/json");
  request.setRawHeader("X-Application", m_bfConfig->getAppKey().toUtf8());
  if (!sslConfiguration.isNull())
    request.setSslConfiguration(sslConfiguration);

  QByteArray data;
  data.append(QString("username=" + m_bfConfig->getUsername() +
                      "&password=" + m_bfConfig->getPassword()));

  m_networkAccessManager.post(request, data);
}

void LoginApi::replyFinishToken(QNetworkReply *reply)
{
  m_waitingLoginReply = false;
  QString answer = QString::fromUtf8(reply->readAll());
  reply->deleteLater();

  QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());

  QJsonObject jsonObj = jsonResponse.object();

  BfApiNgException *apiNgEx = 0;

  if (jsonObj["error"].isObject()) {
    apiNgEx = BfApiNgExceptionParser::parseException(answer);
  } else if (jsonObj["status"].toString().compare("SUCCESS") == 0) {
    m_bfConfig->setSessionToken(jsonObj["token"].toString());
    qDebug() << "token= " << jsonObj["token"].toString();
    qDebug() << "appkey= " << m_bfConfig->getAppKey();
    qDebug() << "appkeydelayed= " << m_bfConfig->getAppKeyDelayed();
    m_loggedIn = true;
    emit loginCompleted();
  } else {
    m_loggedIn = false;
    apiNgEx = NEW_INTERNAL_EXCEPTION("Login failed...");
  }

  if (apiNgEx != 0) {
    emit error(apiNgEx);
  }
}

void LoginApi::sslErrorsReceived(QNetworkReply *reply,
                                       QList<QSslError>) {
  emit error(NEW_INTERNAL_EXCEPTION("sslErrorsReceived"));
  reply->deleteLater();
}

