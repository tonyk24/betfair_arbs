#include <stdexcept>
#include <algorithm>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QFile>
#include <QSound>


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "factory/bffilterfactory.h"
#include "form.h"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  m_hasAribtrageBets(false)
{
  ui->setupUi(this);

  m_config = new Config(true);

  m_accountsApi = new AccountsApi(0, m_config->getBfConfig());
  m_eventsApi = new EventsApi(0, m_config->getBfConfig());
  m_keepAliveApi = new KeepAliveApi(0, m_config->getBfConfig());

  QObject::connect(m_accountsApi, SIGNAL(valueChanged(BfLib::BfAccountDetailsRsp)),
                   this, SLOT(receivedAccountDetails(BfLib::BfAccountDetailsRsp)));
  QObject::connect(m_accountsApi, SIGNAL(valueChanged(BfLib::BfAccountFundsRsp)),
                   this, SLOT(receivedAccountFunds(BfLib::BfAccountFundsRsp)));
  QObject::connect(m_eventsApi, SIGNAL(valueChanged(QVector<BfLib::BfEvent>)),
                   this, SLOT(receivedEvents(QVector<BfLib::BfEvent>)));

  QObject::connect(m_accountsApi, SIGNAL(error(BfLib::BfApiNgException*)),
                   this, SLOT(errorOccurred(BfLib::BfApiNgException*)));
  QObject::connect(m_eventsApi, SIGNAL(error(BfLib::BfApiNgException*)),
                   this, SLOT(errorOccurred(BfLib::BfApiNgException*)));

  QObject::connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)),
                   this, SLOT(tabCloseRequested(int)));

  ui->tableWidget->setColumnCount(4);
  QStringList m_TableHeader;
  m_TableHeader<<"EventId" << "Name"<<"Country"<<"OpenDate";
  ui->tableWidget->setColumnWidth(1, 200);
  ui->tableWidget->setHorizontalHeaderLabels(m_TableHeader);

  int eventtypeid = 1;

  BetfairMarketFilter marketFilter = BfFilterFactory::chooseEventsFilter(eventtypeid);

  m_eventsApi->get(marketFilter);
  refreshWalletList();

  // External sites
  m_extUpdateTimer = new QTimer();
  m_extUpdateTimer->start(5000);
  connect(m_extUpdateTimer, SIGNAL(timeout()),
          this, SLOT(updateExtSites()));
  updateExtSites();
  connect(&m_extSiteSP, SIGNAL(resultUpdated(std::list<ExtSiteSPOdds>)),
          this, SLOT(onReceivedSPBets(std::list<ExtSiteSPOdds>)));

  // Keep alive
  m_keepAliveTimer = new QTimer(this);
  m_keepAliveTimer->start(60000);
  QObject::connect(m_keepAliveTimer, SIGNAL(timeout()),
                   this, SLOT(keepAliveTimeout()));
  QObject::connect(m_keepAliveApi, SIGNAL(error(BfLib::BfApiNgException*)),
                   this, SLOT(errorOccurred(BfLib::BfApiNgException*)));
}

MainWindow::~MainWindow()
{
    delete m_keepAliveApi;
  delete ui;
}

void MainWindow::receivedAccountDetails(BfAccountDetailsRsp accountDetailsRsp) {
  QMessageBox msgBox;
  msgBox.setText("Details received.");
  msgBox.exec();
}

void MainWindow::receivedAccountFunds(BfAccountFundsRsp accountFundsRsp) {
  ui->lineEdit->setText("Funds: " + QString::number(accountFundsRsp.m_availableToBetBalance));
}

bool compSortEvents(const BfEvent & a, const BfEvent & b) {
  return a.m_openDate.currentMSecsSinceEpoch() > b.m_openDate.currentMSecsSinceEpoch();
}

void MainWindow::receivedEvents(QVector<BfLib::BfEvent> newEvents) {
  m_events = newEvents;
  filterEvents();
  updateEventTableWidget();

}

void MainWindow::on_pushButton_clicked()
{
  m_extSiteSP.update();
}



void MainWindow::on_pushButtonFunds_clicked()
{
  m_accountsApi->getAccountFunds();
}

void MainWindow::errorOccurred(BfApiNgException *ex) {
  qWarning() << "Receieved error:" << ", " << ex->toString();
  if (ex->m_errorType == BfApiNgException::API_NG_ERR) {
    if (ex->m_apiNgErrorCode == "TOO_MUCH_DATA") {
    } else if(ex->m_apiNgErrorCode == "INVALID_INPUT_DATA" ||
              ex->m_apiNgErrorCode == "INVALID_SESSION_INFORMATION" ||
              ex->m_apiNgErrorCode == "NO_APP_KEY" ||
              ex->m_apiNgErrorCode == "NO_SESSION" ||
              ex->m_apiNgErrorCode == "UNEXPECTED_ERROR" ||
              ex->m_apiNgErrorCode == "INVALID_APP_KEY" ||
              ex->m_apiNgErrorCode == "TOO_MANY_REQUESTS" ||
              ex->m_apiNgErrorCode == "REQUEST_SIZE_EXCEEDS_LIMIT" ||
              ex->m_apiNgErrorCode == "ACCESS_DENIED") {
      qWarning() << "Exiting: " << ex->toString();
      throw std::runtime_error(ex->toString().toStdString());
      return;
    } else if(ex->m_apiNgErrorCode == "SERVICE_BUSY") {
      // Do nothing
      return;
    } else if(ex->m_apiNgErrorCode == "TIMEOUT_ERROR") {
      // Do nothing
      return;
    } else {
      qWarning() << "Found unexpected API_NG_ERR error code..";
      qWarning() << "Exiting: " << ex->toString();
      throw std::runtime_error(ex->toString().toStdString());
      return;
    }
  }


  throw std::runtime_error(ex->toString().toStdString());
  delete ex;
}

void MainWindow::keepAliveTimeout()
{
  m_keepAliveApi->sendKeepAlive();
}

void MainWindow::on_pushButtonEvents_clicked()
{
  int eventtypeid = 1;
  if (ui->comboBox->currentText() == "Football")
    eventtypeid = 1;
  else
    eventtypeid = 7524;

  BetfairMarketFilter marketFilter = BfFilterFactory::chooseEventsFilter(eventtypeid);

  m_eventsApi->get(marketFilter);
}

void MainWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{
  int counter = 0;
  for(QVector<BfEvent>::iterator it = m_filteredEvents.begin();
      it != m_filteredEvents.end(); it++)
  {
    if (ui->tableWidget->item(index.row(), 0)->text() == it->m_eventId)
    {
      QString currentExtSSTitle = "None";
      if (ui->tableWidgetExtSS->currentItem() != 0)
        currentExtSSTitle = ui->tableWidgetExtSS->currentItem()->text();
      gameDialog = new GameDialog(this,
                                  m_config,
                                  *it,
                                  currentExtSSTitle);

      connect(&m_extSiteSP, SIGNAL(resultUpdated(std::list<ExtSiteSPOdds>)),
              gameDialog, SLOT(onReceivedSPBets(std::list<ExtSiteSPOdds>)));
      connect(gameDialog, SIGNAL(onHasAribtrageBetsChanged(bool)),
              this, SLOT(onReceivedGameHasArbBets(bool)));
      ui->tabWidget->addTab(gameDialog, it->m_name);

    }
    counter++;
  }
}

void MainWindow::tabCloseRequested(int index)
{
  if (index > 0)
  {
    delete ui->tabWidget->widget(index);
  }
}

void MainWindow::on_lineEditFilter_textChanged(const QString &arg1)
{
  Q_UNUSED(arg1)
  filterEvents();
  updateEventTableWidget();
  filterExtSSEvents();
  updateExtSSTableWidget();
}

void MainWindow::on_pushButtonAddWalletEntry_clicked()
{

  QFile file("C:\\Users\\Tony\\Betfairdata\\wallet.csv");
  if (file.open(QFile::Append))
  {
    QTextStream stream(&file);
    stream << QDateTime().currentDateTime().toString() << ","
           << ui->lineEditCashIn->text()<< ","
           << ui->lineEditBf->text() << ","
           << ui->lineEditUB->text() << "\n";

    file.close();
  }

  refreshWalletList();
}

void MainWindow::filterEvents()
{
  QString filter = ui->lineEditFilter->text();
  if (filter == "")
  {
    m_filteredEvents = m_events;
  }
  else
  {
    m_filteredEvents.clear();
    for(QVector<BfEvent>::iterator it = m_events.begin();
        it != m_events.end(); it++)
    {
      if (it->m_name.contains(filter, Qt::CaseInsensitive))
        m_filteredEvents.push_back(*it);
    }
  }
}

void MainWindow::updateEventTableWidget()
{
  ui->tableWidget->setRowCount(m_filteredEvents.size());


  int counter = 0;
  for(QVector<BfEvent>::iterator it = m_filteredEvents.begin();
      it != m_filteredEvents.end(); it++)
  {
    ui->tableWidget->setItem(counter, 0, new QTableWidgetItem(it->m_eventId));
    ui->tableWidget->setItem(counter, 1, new QTableWidgetItem(it->m_name));
    ui->tableWidget->setItem(counter, 2, new QTableWidgetItem(it->m_countryCode));
    ui->tableWidget->setItem(counter, 3, new QTableWidgetItem(it->m_openDate.toLocalTime().toString("yyyy-MM-dd hh:mm:ss")));
    counter++;
  }
}

void MainWindow::filterExtSSEvents()
{
  QString filter = ui->lineEditFilter->text();
  if (filter == "")
  {
    m_filteredExtSiteSPEvents = m_extSiteSPEvents;
  }
  else
  {
    m_filteredExtSiteSPEvents.clear();
    for (std::list<ExtSiteSPOdds>::iterator it = m_extSiteSPEvents.begin();
         it != m_extSiteSPEvents.end(); it++)
    {
      if (it->m_title.contains(filter, Qt::CaseInsensitive))
        m_filteredExtSiteSPEvents.push_back(*it);
    }
  }
}

void MainWindow::updateExtSSTableWidget()
{

  ui->tableWidgetExtSS->setRowCount(m_filteredExtSiteSPEvents.size()+1);
  ui->tableWidgetExtSS->setItem(0, 0, new QTableWidgetItem("None"));

  int counter = 1;
  for (std::list<ExtSiteSPOdds>::iterator it = m_filteredExtSiteSPEvents.begin();
       it != m_filteredExtSiteSPEvents.end(); it++, counter++)
    ui->tableWidgetExtSS->setItem(counter, 0, new QTableWidgetItem(it->m_title));
}

void MainWindow::refreshWalletList()
{
  QFile file("C:\\Users\\Tony\\Betfairdata\\wallet.csv");
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << file.errorString();
  }

  ui->tableWidgetWalletHistory->setRowCount(0);

  QStringList wordList;

  std::list<QByteArray> lines;
  while (!file.atEnd()) {

    QByteArray line = file.readLine();
    lines.push_back(line);
  }
  double balance = 0;
  double totalCashIn = 0;
  int counter = lines.size();
  ui->tableWidgetWalletHistory->setRowCount(lines.size());
  for (std::list<QByteArray>::iterator it = lines.begin();
       it != lines.end(); it++)
  {
    QDateTime date = QDateTime().fromString(QString(it->split(',').at(0)));
    double cashIn = QString(it->split(',').at(1)).toDouble();
    double bfVal = QString(it->split(',').at(2)).toDouble();
    double UBVal = QString(it->split(',').at(3)).replace("\n","").toDouble();

    double sumWallet = bfVal+UBVal;
    totalCashIn += cashIn;
    balance = bfVal+UBVal-totalCashIn;


    counter--;

    ui->tableWidgetWalletHistory->setItem(counter, 0,
                                          new QTableWidgetItem(date.toString()));
    ui->tableWidgetWalletHistory->setItem(counter, 1,
                                          new QTableWidgetItem(QString::number(cashIn)));
    ui->tableWidgetWalletHistory->setItem(counter, 2,
                                          new QTableWidgetItem(QString::number(bfVal)));
    ui->tableWidgetWalletHistory->setItem(counter, 3,
                                          new QTableWidgetItem(QString::number(UBVal)));
    ui->tableWidgetWalletHistory->setItem(counter, 4,
                                          new QTableWidgetItem(QString::number(sumWallet)));
    ui->tableWidgetWalletHistory->setItem(counter, 5,
                                          new QTableWidgetItem(QString::number(balance)));
  }
  ui->labelBalance->setText("Balance: " + QString::number(balance));

  qDebug() << wordList;
}

void MainWindow::updateExtSites()
{
  m_extSiteSP.update();
}

void MainWindow::onReceivedSPBets(std::list<ExtSiteSPOdds> result)
{
  m_extSiteSPEvents = result;
  filterExtSSEvents();
  updateExtSSTableWidget();
}

void MainWindow::onReceivedGameHasArbBets(bool hasArbBets)
{
  for (int tab = 0; tab<ui->tabWidget->count(); tab++)
  {
    QWidget *gameDialog = ui->tabWidget->widget(tab);
    if (sender() == gameDialog)
    {
      if (hasArbBets)
      {
        ui->tabWidget->tabBar()->setTabTextColor(tab, Qt::darkGreen);
        QSound::play(":/sounds/Pling-KevanGC-1485374730.wav");
      }
      else
      {
        ui->tabWidget->tabBar()->setTabTextColor(tab, Qt::black);
      }
    }
  }
}


void MainWindow::on_pushButtonHorn_clicked()
{
    QSound::play(":/sounds/Pling-KevanGC-1485374730.wav");
}
