#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QDialog>
#include <QSignalMapper>
#include "betfairapi/eventsapi.h"
#include "soccergame.h"
#include "misc/config.h"
#include "widgets/extbetstablewidget.h"
#include "widgets/bfbetstablewidget.h"
#include "widgets/arbbetstablewidget.h"
#include "widgets/betplottingwidget.h"

#include "resmat.h"

#include "extsites/extsitesp.h"

using namespace BfLib;

namespace Ui {
class GameDialog;
}

class GameDialog : public QDialog
{
  Q_OBJECT

public:
  explicit GameDialog(QWidget *parent,
                      Config *config, BfEvent bfEvent,
                      QString extSiteSPGameTitle);
  ~GameDialog();

signals:
  void onHasAribtrageBetsChanged(bool);
private slots:
  void updateProgressBar();

  void on_pushButtonStartStop_clicked();

  void on_pushSetTime_clicked();





  void receivedResultMatrix(ResMat resultMatrixReal,
                            ResMat resultMatrixRealSim,
                            ResMat resultMatrixSim,
                            ResMat resultMatrixLucky);
  void receivedTotalGoalsUpdated(EventStats::TOTALGOALS_EQ, EventStats::TOTALGOALS_LE);

  void receivedPlacedBetsUpdated(std::list<std::pair<BfLib::BfPlaceExecutionReport,BfLib::BfCurrentOrder> >);
  void removePlacedBet();

  void on_pushButtonSetMaxExposure_clicked();

  void on_tableWidgetPlacedBets_customContextMenuRequested(const QPoint &pos);

  void onReceivedSPBets(std::list<ExtSiteSPOdds> result);

  void receivedGreenExtBets(bool hasArbBets);
  void receivedBfLuckyBets(bool hasLuckyBets);
  void on_pushButtonWebsite_clicked();

private:
  void updateGame();


  Ui::GameDialog *ui;

  ArbBetsTableWidget *m_arbBetsTableWidget;
  BfBetsTableView *m_bfBetsTableView;
  BetPlottingWidget *m_plottingWidget;

  QString m_extSiteSPGameTitle;

  QTimer *progressTimer;
  bool m_gameStarted;
  int m_gameTimeMs;

  SoccerGame *m_soccerGame;
  Config *m_config;

  bool m_hasExtArbitrageBets;
  bool m_hasBfArbitrageBets;
  bool m_hasAribitrageBets;


};

#endif // GAMEDIALOG_H
