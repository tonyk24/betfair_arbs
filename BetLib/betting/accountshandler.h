#ifndef ACCOUNTSHANDLER_H
#define ACCOUNTSHANDLER_H

#include <cmath>

#include <QObject>
#include <QDebug>
#include <QString>

#include "bftypes/bfaccountdetailsrsp.h"
#include "bftypes/bfaccountfundsrsp.h"

/*
 * INFO_NEED_UPDATE
 *      |
 *      |
 * */

using namespace BfLib;
class AccountsHandler : public QObject {
private:
  enum State { INFO_NEED_UPDATE,
               INFO_NEED_UPDATE_WAITING,
               INFO_UNKOWN,
               INFO_UPTODATE};
  QString stateToStr(State s) const {
    if (s == INFO_NEED_UPDATE) {
      return QString("INFO_NEED_UPDATE");
    } else if (s == INFO_NEED_UPDATE_WAITING) {
      return QString("INFO_NEED_UPDATE_WAITING");
    } else if (s == INFO_UNKOWN) {
      return QString("INFO_UNKOWN");
    } else if (s == INFO_UPTODATE) {
      return QString("INFO_UPTODATE");
    }

    return "";
  }

public:
  AccountsHandler(QObject *parent, double configuredMaxExposure) :
    m_infoState(INFO_NEED_UPDATE),
    m_walletFunds(0.0),
    m_configuredMaxExposure(configuredMaxExposure)
  {
    qDebug() << "AccountsHandler()";
     Q_UNUSED(parent);
  }

  void accountInfoReceived(BfAccountFundsRsp accountFundsRsp) {
    if (m_infoState == INFO_NEED_UPDATE_WAITING) {
      m_infoState = INFO_UPTODATE;
    }
    m_walletFunds = accountFundsRsp.m_availableToBetBalance;
    qDebug() << "updateWallet(walletFunds=" << m_walletFunds;
    qDebug() << __PRETTY_FUNCTION__ << " " << stateToStr(m_infoState);
  }

  // Move state
  void placeBetsActive() {
    m_infoState = INFO_UNKOWN;
    qDebug() << __PRETTY_FUNCTION__ << " " << stateToStr(m_infoState);
  }

  void noPlaceBetsActive() {
    if (m_infoState == INFO_UNKOWN) {
      m_infoState = INFO_NEED_UPDATE;
    }
    qDebug() << __PRETTY_FUNCTION__ << " " << stateToStr(m_infoState);
  }

  void updateInfo() {
    m_infoState = INFO_NEED_UPDATE;
    qDebug() << __PRETTY_FUNCTION__ << " " << stateToStr(m_infoState);
  }

  void requestSent() {
    if (m_infoState == INFO_NEED_UPDATE) {
      m_infoState = INFO_NEED_UPDATE_WAITING;
    }
    qDebug() << __PRETTY_FUNCTION__ << " " << stateToStr(m_infoState);
  }

  // Check state
  bool shouldSendRequest() {
    return m_infoState == INFO_NEED_UPDATE;
  }

  bool isInfoUpToDate() {
    return m_infoState == INFO_UPTODATE;
  }

  // MaxExposure
  double getConfiguredMaxExposure() const {
    return m_configuredMaxExposure;
  }

  double getMaxExposure() const {
    return std::max(m_configuredMaxExposure, m_walletFunds*0.1);
  }

  double getWalletFunds() const {
    return m_walletFunds;
  }

  QString getDebugStr() {
    QString out;
    QTextStream tsOut(&out);

    tsOut << " * m_infoState= " << stateToStr(m_infoState) << "\n";
    tsOut << " * m_walletFunds= " << QString::number(m_walletFunds) << "\n";
    tsOut << " * m_configuredMaxExposure= " << QString::number(m_configuredMaxExposure) << "\n";
    return out;
  }

private:
  State m_infoState;
  double m_walletFunds;
  double m_configuredMaxExposure;
};

#endif // ACCOUNTSHANDLER_H

