#ifndef HTTPJSONCLIENT_H
#define HTTPJSONCLIENT_H

#include <list>

#include <QString>
#include <QJsonObject>
#include <QNetworkReply>
#include <QTimer>

#include "betfairlib_global.h"

#include "betfairapi/loginapi.h"

#include "misc/bfconfig.h"

#include "bftypes/bfapingexception.h"

class BETFAIRLIBSHARED_EXPORT HttpJsonClient : public QObject {
  Q_OBJECT
public:
  HttpJsonClient(QObject *parent, BfConfig *bfConfig, QString url);
  void send(QJsonObject jsonObj);

private:

  BfConfig *m_bfConfig;
  std::list<QJsonObject> m_jsonObjs;
  LoginApi m_loginApi;
  QNetworkAccessManager m_networkAccessManager;
  QString m_url;
private slots:
  void execute();
public slots:
  void replyFinish(QNetworkReply *reply);
  void sslErrorsReceived(QNetworkReply*,QList<QSslError>);
  void loginCompleted();
  void errorOccurred(BfApiNgException *ex);
signals:
  void replyFinish(QString answer);
  void error(BfApiNgException *ex);
};

#endif // HTTPJSONCLIENT_H

