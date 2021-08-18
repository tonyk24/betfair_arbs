#ifndef LOGINAPI_H
#define LOGINAPI_H


#include <QObject>
#include <QNetworkReply>

#include "betfairlib_global.h"

#include "misc/bfconfig.h"

#include "bftypes/bfapingexception.h"

class BETFAIRLIBSHARED_EXPORT LoginApi : public QObject
{
  Q_OBJECT
public:
  LoginApi(QObject *parent, BfConfig *bfConfig);

  void login();
  bool isLoggedIn() { return m_loggedIn; }
  bool isWaitingForLoginReply() { return m_waitingLoginReply; }

private:
  BfConfig *m_bfConfig;
  static bool m_loggedIn;
  static bool m_waitingLoginReply;
  QNetworkAccessManager m_networkAccessManager;

private slots:
  void replyFinishToken(QNetworkReply *reply);
    void sslErrorsReceived(QNetworkReply*,QList<QSslError>);
signals:
  void loginCompleted();
  void error(BfApiNgException *ex);
};

#endif // LOGINAPI_H

