#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>

#include "betfairapi/accountsapi.h"
#include "betfairapi/eventsapi.h"

#include "extsites/extsitesp.h"

#include "misc/config.h"

#include "gamedialog.h"

using namespace BfLib;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_pushButton_clicked();

  void on_pushButtonFunds_clicked();

  void on_pushButtonEvents_clicked();

  void on_tableWidget_doubleClicked(const QModelIndex &index);
  void tabCloseRequested(int);

  void on_lineEditFilter_textChanged(const QString &arg1);

  void on_pushButtonAddWalletEntry_clicked();
  void updateExtSites();
  void on_pushButtonHorn_clicked();

public slots:
  void receivedAccountDetails(BfLib::BfAccountDetailsRsp accountDetailsRsp);
  void receivedAccountFunds(BfLib::BfAccountFundsRsp accountFundsRsp);
  void receivedEvents(QVector<BfLib::BfEvent> events);

  void errorOccurred(BfLib::BfApiNgException *ex);
  void onReceivedSPBets(std::list<ExtSiteSPOdds> result);
  void onReceivedGameHasArbBets(bool hasArbBets);
  void keepAliveTimeout();
private:
  bool m_hasAribtrageBets;
  Ui::MainWindow *ui;
  GameDialog *gameDialog;

  Config *m_config;
  AccountsApi *m_accountsApi;
  EventsApi *m_eventsApi;
  KeepAliveApi *m_keepAliveApi;

  QTimer *m_keepAliveTimer;

  QVector<BfEvent> m_events;
  QVector<BfEvent> m_filteredEvents;

  void filterEvents();
  void updateEventTableWidget();

  void filterExtSSEvents();
  void updateExtSSTableWidget();
  void refreshWalletList();

  QTimer *m_extUpdateTimer;

  ExtSiteSP m_extSiteSP;
  std::list<ExtSiteSPOdds> m_extSiteSPEvents;
  std::list<ExtSiteSPOdds> m_filteredExtSiteSPEvents;
};

#endif // MAINWINDOW_H
