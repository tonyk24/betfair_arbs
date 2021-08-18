#ifndef BETCONFIG_H
#define BETCONFIG_H

#include <QString>

class BfConfig {
public:
  BfConfig(QString user,
           QString pass,
           bool testMode,
           QString appKey,
           QString appKeyDelayed)
    : m_testMode(testMode),
      m_token(""),
      m_bfuser(user),
      m_bfPasswd(pass),
      m_appKey(appKey),
      m_appKeyDelayed(appKeyDelayed)
  {

  }

  QString getUsername() {
    return m_bfuser;
  }

  QString getPassword() {
    return m_bfPasswd;
  }

  QString getAppKey() {
    if (m_testMode) {
      return m_appKeyDelayed;
    }

    return m_appKey;
  }

  QString getAppKeyNonDelayed() {
    return m_appKey;
  }

  QString getAppKeyDelayed() {
    return m_appKeyDelayed;
  }

  QString getSessionToken() {
    return m_token;
  }

  void setSessionToken(QString token) {
    m_token = token;
  }

private:
  bool m_testMode;
  QString m_token;

  QString m_bfuser;
  QString m_bfPasswd;

  QString m_appKey;
  QString m_appKeyDelayed;
};

#endif // BETCONFIG_H

