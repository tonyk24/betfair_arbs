#include <cmath>

#include <QHBoxLayout>
#include <QMenu>
#include <QDesktopServices>

#include "gamedialog.h"
#include "ui_gamedialog.h"

#include "widgets/extbetstablewidget.h"
#include "types/extbet.h"

GameDialog::GameDialog(QWidget *parent, Config *config, BfEvent bfEvent,
                       QString extSiteSPGameTitle) :
  QDialog(parent),
  m_config(config),
  m_extSiteSPGameTitle(extSiteSPGameTitle),
  m_hasExtArbitrageBets(false),
  m_hasBfArbitrageBets(false),
  m_hasAribitrageBets(false),
  ui(new Ui::GameDialog)
{
  ui->setupUi(this);
  this->setWindowTitle(bfEvent.m_name);

  m_soccerGame = new SoccerGame(0, m_config, bfEvent);

  progressTimer = new QTimer(this);
  connect(progressTimer, SIGNAL(timeout()), this, SLOT(updateProgressBar()));
  connect(m_soccerGame, SIGNAL(resultMatrixUpdated(ResMat,ResMat,ResMat,ResMat)),
          this, SLOT(receivedResultMatrix(ResMat,ResMat,ResMat, ResMat)));
  connect(m_soccerGame, SIGNAL(totalGoalsUpdated(EventStats::TOTALGOALS_EQ,EventStats::TOTALGOALS_LE)),
          this, SLOT(receivedTotalGoalsUpdated(EventStats::TOTALGOALS_EQ,EventStats::TOTALGOALS_LE)));
  connect(m_soccerGame, SIGNAL(placedBetsUpdated(std::list<std::pair<BfLib::BfPlaceExecutionReport,BfLib::BfCurrentOrder> >)),
          this, SLOT(receivedPlacedBetsUpdated(std::list<std::pair<BfLib::BfPlaceExecutionReport,BfLib::BfCurrentOrder> >)));




  m_soccerGame->start();
  progressTimer->start(60);

  m_gameStarted = true;
  m_gameTimeMs = 0;

  ui->tableWidgetPlacedBets->setContextMenuPolicy(Qt::CustomContextMenu);
  ui->tableWidgetPlacedBets->setColumnWidth(0,100); // betid
  ui->tableWidgetPlacedBets->setColumnWidth(1,60); // betid
  ui->tableWidgetPlacedBets->setColumnWidth(2,60); // side
  ui->tableWidgetPlacedBets->setColumnWidth(3,60); // Price
  ui->tableWidgetPlacedBets->setColumnWidth(4,60); // status
  ui->tableWidgetPlacedBets->setColumnWidth(5,100); // marketid

  // Update gameinfo

  ui->textEditGameInfo->setText(
        "Name: " + m_soccerGame->m_bfEvent.m_name + "\n" +
        "Competition: " + BfCompetition::toStr(m_soccerGame->m_bfEvent.m_competition) + "\n"
        "OpenDate: " + m_soccerGame->m_bfEvent.m_openDate.toLocalTime().toString("yyyy-MM-dd hh:mm:ss") + "\n" +
        "CountryCode: " + m_soccerGame->m_bfEvent.m_countryCode);

  // ------------------------- Aribitrage bets table widget

  m_arbBetsTableWidget = new ArbBetsTableWidget(ui->tabWidgetBetsInfo->widget(1));
  connect(m_soccerGame, SIGNAL(arbBetsUpdate(std::list<BfArbBet>)),
          m_arbBetsTableWidget, SLOT(receivedArbBetsUpdate(std::list<BfArbBet>)));
  connect(m_arbBetsTableWidget, SIGNAL(onLuckyBetsChanged(bool)),
          this, SLOT(receivedBfLuckyBets(bool)));
  connect(m_arbBetsTableWidget, SIGNAL(placeBet(QString,BfLib::BfPlaceInstruction)),
          m_soccerGame, SLOT(placeBet(QString,BfLib::BfPlaceInstruction)));
  QVBoxLayout *vbox = new QVBoxLayout();
  vbox->addWidget(m_arbBetsTableWidget);
  vbox->addStretch(1);
  ui->tabWidgetBetsInfo->widget(1)->setLayout(vbox);

  // ------------------------- Betfair bets table widget
  m_bfBetsTableView = new BfBetsTableView(ui->tabWidgetBfBets,
                                              this->m_soccerGame->m_bfEvent);
  ui->tabWidgetBfBets->addTab(m_bfBetsTableView,
                              "BfBets");

  bool ok = false;
  double maxExposure = ui->lineEditMaxExposure->text().toDouble(&ok);
  if (ok)
    this->m_bfBetsTableView->updateMaxExposure(maxExposure);

  // Connect SoccerGame to BfBetsTableWidget
  connect(m_bfBetsTableView, SIGNAL(placeBetSimulated(QString,qint64,double,BfLib::BfSide::Enum,double,double)),
          m_soccerGame, SLOT(placeBetSimulated(QString,qint64,double,BfLib::BfSide::Enum,double,double)));
  connect(m_bfBetsTableView, SIGNAL(placeBetSimulatedRemove(QString,qint64,double,BfLib::BfSide::Enum)),
          m_soccerGame, SLOT(placeBetSimulatedRemove(QString,qint64,double,BfLib::BfSide::Enum)));

  connect(m_bfBetsTableView, SIGNAL(placeBet(QString,qint64,double,BfLib::BfSide::Enum,double,double)),
          m_soccerGame, SLOT(placeBet(QString,qint64,double,BfLib::BfSide::Enum,double,double)));

  connect(m_bfBetsTableView, SIGNAL(placeExtBetSimulated(ExtBet)),
          m_soccerGame, SLOT(placeExtBetSimulated(ExtBet)));
  connect(m_bfBetsTableView, SIGNAL(placeExtBetSimulatedRemoved(ExtBet)),
          m_soccerGame, SLOT(placeExtBetSimulatedRemoved(ExtBet)));
  connect(m_soccerGame, SIGNAL(marketsDataUpdated(std::list<BfLib::BetfairMarket>)),
          m_bfBetsTableView, SLOT(receivedMarketData(std::list<BfLib::BetfairMarket>)));
  connect(m_bfBetsTableView, SIGNAL(hasAribtrageBetsChanged(bool)),
          this, SLOT(receivedGreenExtBets(bool)));


  m_soccerGame->setBetSize(ui->lineEditMaxExposure->text().toDouble());

  // ------------------------- Plotting widget
  m_plottingWidget = new BetPlottingWidget();
  ui->tabWidgetBfBets->addTab(m_plottingWidget, "Plot");
  connect(m_soccerGame, SIGNAL(marketsDataUpdated(std::list<BfLib::BetfairMarket>)),
          m_plottingWidget, SLOT(receivedMarketData(std::list<BfLib::BetfairMarket>)));
}

GameDialog::~GameDialog()
{
  //qDebug() << "~GameDialog()";
  progressTimer->stop();
  delete progressTimer;
  delete m_soccerGame;
  delete ui;
}

void GameDialog::updateGame()
{
  // Upadte game time
  if (m_gameStarted)
    m_gameTimeMs += 60;
  ui->labelGameTime->setText(QString::number((m_gameTimeMs / 1000)/60) + "min " + QString::number((m_gameTimeMs / 1000)%60) + "secs");
}

void GameDialog::updateProgressBar()
{
  ui->progressBar->setMinimum(0);
  ui->progressBar->setMaximum(100);
  if (ui->progressBar->value() == 100)
  {
    ui->progressBar->setValue(0);
    m_soccerGame->getMarketData();
    m_soccerGame->getPlacedBets();

  }
  else
    ui->progressBar->setValue(ui->progressBar->value()+1);

  updateGame();
}

void GameDialog::on_pushButtonStartStop_clicked()
{
  if (m_gameStarted)
  {
    progressTimer->stop();
    m_gameStarted = false;
    QPalette pal = ui->pushButtonStartStop->palette();
    pal.setColor(QPalette::Button, QColor(Qt::red));
    ui->pushButtonStartStop->setAutoFillBackground(true);
    ui->pushButtonStartStop->setPalette(pal);
    ui->pushButtonStartStop->update();

  }
  else
  {
    progressTimer->start(60);
    m_gameStarted = true;
    QPalette pal = ui->pushButtonStartStop->palette();
    pal.setColor(QPalette::Button, QColor(Qt::green));
    ui->pushButtonStartStop->setAutoFillBackground(true);
    ui->pushButtonStartStop->setPalette(pal);
    ui->pushButtonStartStop->update();
  }
}

void GameDialog::on_pushSetTime_clicked()
{
  QString val = ui->lineEditSetTime->text();
  m_gameTimeMs = val.toInt()*1000;
}

void GameDialog::receivedResultMatrix(ResMat resultMatrixReal,
                                      ResMat resultMatrixRealSimulation,
                                      ResMat resultMatrixSimulation,
                                      ResMat resultMatrixLucky)
{
  for(int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      ui->tableWidgetResMatReal->setItem(row, col,
                                         new QTableWidgetItem(
                                           QString::number(resultMatrixReal.getItemData(row, col))));
    }
  }

  for(int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      ui->tableWidgetResMatRealnSim->setItem(row, col,
                                             new QTableWidgetItem(
                                               QString::number(resultMatrixRealSimulation.getItemData(row, col))));
    }
  }

  for(int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      ui->tableWidgetResMatSimulation->setItem(row, col,
                                               new QTableWidgetItem(
                                                 QString::number(resultMatrixSimulation.getItemData(row, col))));
    }
  }

  for(int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      ui->tableWidgetResMatLucky->setItem(row, col,
                                               new QTableWidgetItem(
                                                 QString::number(resultMatrixLucky.getItemData(row, col))));
    }
  }
}

void GameDialog::receivedTotalGoalsUpdated(EventStats::TOTALGOALS_EQ tgeq,
                                           EventStats::TOTALGOALS_LE tgle)
{
  ui->labelGoals->setText("tgeq= " + QString::number(tgeq) + ", tgle= " + QString::number(tgle));
}





void GameDialog::receivedPlacedBetsUpdated(std::list<std::pair<BfPlaceExecutionReport,BfCurrentOrder> > placedOrders)
{
  //qDebug() << "receivedPlacedBetsUpdated" << QString::number(placedOrders.size());
  ui->tableWidgetPlacedBets->setRowCount(placedOrders.size());
  int row = 0;
  for (std::list<std::pair<BfPlaceExecutionReport,BfCurrentOrder> >::iterator it = placedOrders.begin();
       it != placedOrders.end(); it++, row++)
  {
    //qDebug() << ", report= " + it->first.toStr();
    ui->tableWidgetPlacedBets->setItem(row, 0,
                                       new QTableWidgetItem(it->second.m_betId));
    ui->tableWidgetPlacedBets->setItem(row, 1,
                                       new QTableWidgetItem(BfExecutionErrorReportCode::toStr(it->first.m_errorCode)));
    ui->tableWidgetPlacedBets->setItem(row, 2,
                                       new QTableWidgetItem(BfSide::toStr(it->second.m_side)));
    ui->tableWidgetPlacedBets->setItem(row, 3,
                                       new QTableWidgetItem(QString::number(it->second.m_averagePriceMatched)));
    ui->tableWidgetPlacedBets->setItem(row, 4,
                                       new QTableWidgetItem(QString::number(it->second.m_sizeMatched)));
    ui->tableWidgetPlacedBets->setItem(row, 5,
                                       new QTableWidgetItem(BfOrderStatus::toStr(it->second.m_status)));
    if (it->second.m_betId != "")
      ui->tableWidgetPlacedBets->setItem(row, 6,
                                         new QTableWidgetItem(it->second.m_marketId));
    else
      ui->tableWidgetPlacedBets->setItem(row, 6,
                                         new QTableWidgetItem(it->first.m_marketId));
  }
}


void GameDialog::receivedGreenExtBets(bool hasArbBets)
{
  m_hasExtArbitrageBets = hasArbBets;
  if ((m_hasExtArbitrageBets || m_hasBfArbitrageBets) != m_hasAribitrageBets)
    emit onHasAribtrageBetsChanged(m_hasExtArbitrageBets || m_hasBfArbitrageBets);
  m_hasAribitrageBets = m_hasExtArbitrageBets || m_hasBfArbitrageBets;
}

void GameDialog::receivedBfLuckyBets(bool hasLuckyBets)
{
  m_hasBfArbitrageBets = hasLuckyBets;
  if ((m_hasExtArbitrageBets || m_hasBfArbitrageBets) != m_hasAribitrageBets)
    emit onHasAribtrageBetsChanged(m_hasExtArbitrageBets || m_hasBfArbitrageBets);
  m_hasAribitrageBets = m_hasExtArbitrageBets || m_hasBfArbitrageBets;
}

void GameDialog::on_pushButtonSetMaxExposure_clicked()
{
  bool ok = false;
  double maxExposure = ui->lineEditMaxExposure->text().toDouble(&ok);
  if (ok)
  {
    this->m_bfBetsTableView->updateMaxExposure(maxExposure);
    m_soccerGame->setBetSize(ui->lineEditMaxExposure->text().toDouble());
  }
}


void GameDialog::on_tableWidgetPlacedBets_customContextMenuRequested(const QPoint &pos)
{
  QMenu contextMenu("Context menu", this);

  QAction action1("Remove", this);
  connect(&action1, SIGNAL(triggered()), this, SLOT(removePlacedBet()));
  contextMenu.addAction(&action1);


  contextMenu.exec(ui->tableWidgetPlacedBets->viewport()->mapToGlobal(pos));
}

void GameDialog::removePlacedBet()
{
  qDebug() << "Remove placed bet...";

  QItemSelectionModel *selModel = ui->tableWidgetPlacedBets->selectionModel();
  QModelIndexList indexList = selModel->selectedRows();

  qDebug() << "selections= " << indexList.size();

  for (QModelIndexList::iterator it= indexList.begin();
       it != indexList.end(); it++)
  {
    // Remove selections
    int row = it->row();
    qDebug() << "removing.. row=" << row;
    BfPlaceExecutionReport executionReport;
    BfCurrentOrder currentOrder;
    currentOrder.m_betId = ui->tableWidgetPlacedBets->item(row, 0)->text();
    currentOrder.m_marketId = ui->tableWidgetPlacedBets->item(row, 6)->text();
    std::pair<BfPlaceExecutionReport, BfCurrentOrder> placedBet = std::make_pair(executionReport, currentOrder);
    m_soccerGame->removePlacedBet(placedBet);
  }
}

void GameDialog::onReceivedSPBets(std::list<ExtSiteSPOdds> result)
{
  for(std::list<ExtSiteSPOdds>::iterator it = result.begin();
      it != result.end(); it++)
  {
    if (m_extSiteSPGameTitle == it->m_title)
    {
      this->m_bfBetsTableView->updateSPOdds(*it);
    }
  }
}


void GameDialog::on_pushButtonWebsite_clicked()
{
  QDesktopServices::openUrl(QUrl("https://www.betfair.com/exchange/plus/#/football/event/"
                                 + m_soccerGame->m_bfEvent.m_eventId));
}
