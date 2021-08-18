/********************************************************************************
** Form generated from reading UI file 'gamedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEDIALOG_H
#define UI_GAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameDialog
{
public:
    QGroupBox *groupBox;
    QTextEdit *textEditGameInfo;
    QPushButton *pushButtonWebsite;
    QPushButton *pushSetTime;
    QPushButton *pushButtonStartStop;
    QProgressBar *progressBar;
    QLineEdit *lineEditSetTime;
    QLabel *labelGameTime;
    QLineEdit *lineEditMaxExposure;
    QLabel *label;
    QPushButton *pushButtonSetMaxExposure;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTableWidget *tableWidgetResMatReal;
    QLabel *label_6;
    QLabel *label_7;
    QWidget *tab_3;
    QTableWidget *tableWidgetResMatRealnSim;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *tab_2;
    QTableWidget *tableWidgetResMatSimulation;
    QLabel *label_4;
    QLabel *label_8;
    QWidget *tab_5;
    QTableWidget *tableWidgetResMatLucky;
    QLabel *label_5;
    QLabel *label_9;
    QLabel *labelGoals;
    QTabWidget *tabWidgetBfBets;
    QTabWidget *tabWidgetBetsInfo;
    QWidget *tab_4;
    QTableWidget *tableWidgetPlacedBets;
    QWidget *tabLuckyBets;
    QWidget *tab_6;
    QLabel *label_10;

    void setupUi(QDialog *GameDialog)
    {
        if (GameDialog->objectName().isEmpty())
            GameDialog->setObjectName(QStringLiteral("GameDialog"));
        GameDialog->resize(1671, 906);
        groupBox = new QGroupBox(GameDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 251, 271));
        textEditGameInfo = new QTextEdit(groupBox);
        textEditGameInfo->setObjectName(QStringLiteral("textEditGameInfo"));
        textEditGameInfo->setGeometry(QRect(10, 20, 221, 91));
        textEditGameInfo->setReadOnly(true);
        pushButtonWebsite = new QPushButton(groupBox);
        pushButtonWebsite->setObjectName(QStringLiteral("pushButtonWebsite"));
        pushButtonWebsite->setGeometry(QRect(10, 120, 75, 23));
        pushSetTime = new QPushButton(GameDialog);
        pushSetTime->setObjectName(QStringLiteral("pushSetTime"));
        pushSetTime->setGeometry(QRect(20, 160, 75, 23));
        pushButtonStartStop = new QPushButton(GameDialog);
        pushButtonStartStop->setObjectName(QStringLiteral("pushButtonStartStop"));
        pushButtonStartStop->setGeometry(QRect(20, 190, 75, 23));
        pushButtonStartStop->setAutoFillBackground(false);
        progressBar = new QProgressBar(GameDialog);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(110, 190, 118, 23));
        progressBar->setValue(24);
        lineEditSetTime = new QLineEdit(GameDialog);
        lineEditSetTime->setObjectName(QStringLiteral("lineEditSetTime"));
        lineEditSetTime->setGeometry(QRect(110, 160, 51, 20));
        labelGameTime = new QLabel(GameDialog);
        labelGameTime->setObjectName(QStringLiteral("labelGameTime"));
        labelGameTime->setGeometry(QRect(180, 160, 51, 16));
        lineEditMaxExposure = new QLineEdit(GameDialog);
        lineEditMaxExposure->setObjectName(QStringLiteral("lineEditMaxExposure"));
        lineEditMaxExposure->setGeometry(QRect(90, 230, 51, 20));
        label = new QLabel(GameDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 230, 81, 21));
        pushButtonSetMaxExposure = new QPushButton(GameDialog);
        pushButtonSetMaxExposure->setObjectName(QStringLiteral("pushButtonSetMaxExposure"));
        pushButtonSetMaxExposure->setGeometry(QRect(150, 230, 101, 23));
        tabWidget = new QTabWidget(GameDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(270, 10, 431, 291));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tableWidgetResMatReal = new QTableWidget(tab);
        if (tableWidgetResMatReal->columnCount() < 7)
            tableWidgetResMatReal->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetResMatReal->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetResMatReal->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetResMatReal->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetResMatReal->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetResMatReal->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetResMatReal->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetResMatReal->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        if (tableWidgetResMatReal->rowCount() < 7)
            tableWidgetResMatReal->setRowCount(7);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetResMatReal->setVerticalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetResMatReal->setVerticalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetResMatReal->setVerticalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetResMatReal->setVerticalHeaderItem(3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidgetResMatReal->setVerticalHeaderItem(4, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidgetResMatReal->setVerticalHeaderItem(5, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidgetResMatReal->setVerticalHeaderItem(6, __qtablewidgetitem13);
        tableWidgetResMatReal->setObjectName(QStringLiteral("tableWidgetResMatReal"));
        tableWidgetResMatReal->setGeometry(QRect(30, 20, 391, 241));
        tableWidgetResMatReal->setAutoScrollMargin(16);
        tableWidgetResMatReal->horizontalHeader()->setDefaultSectionSize(51);
        label_6 = new QLabel(tab);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(190, 0, 47, 13));
        label_7 = new QLabel(tab);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 100, 16, 61));
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tableWidgetResMatRealnSim = new QTableWidget(tab_3);
        if (tableWidgetResMatRealnSim->columnCount() < 7)
            tableWidgetResMatRealnSim->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidgetResMatRealnSim->setHorizontalHeaderItem(0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidgetResMatRealnSim->setHorizontalHeaderItem(1, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidgetResMatRealnSim->setHorizontalHeaderItem(2, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidgetResMatRealnSim->setHorizontalHeaderItem(3, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidgetResMatRealnSim->setHorizontalHeaderItem(4, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidgetResMatRealnSim->setHorizontalHeaderItem(5, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidgetResMatRealnSim->setHorizontalHeaderItem(6, __qtablewidgetitem20);
        if (tableWidgetResMatRealnSim->rowCount() < 7)
            tableWidgetResMatRealnSim->setRowCount(7);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidgetResMatRealnSim->setVerticalHeaderItem(0, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidgetResMatRealnSim->setVerticalHeaderItem(1, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidgetResMatRealnSim->setVerticalHeaderItem(2, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidgetResMatRealnSim->setVerticalHeaderItem(3, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidgetResMatRealnSim->setVerticalHeaderItem(4, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidgetResMatRealnSim->setVerticalHeaderItem(5, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidgetResMatRealnSim->setVerticalHeaderItem(6, __qtablewidgetitem27);
        tableWidgetResMatRealnSim->setObjectName(QStringLiteral("tableWidgetResMatRealnSim"));
        tableWidgetResMatRealnSim->setGeometry(QRect(30, 20, 391, 241));
        tableWidgetResMatRealnSim->setAutoScrollMargin(16);
        tableWidgetResMatRealnSim->horizontalHeader()->setDefaultSectionSize(51);
        label_2 = new QLabel(tab_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(170, 0, 47, 13));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 100, 16, 61));
        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tableWidgetResMatSimulation = new QTableWidget(tab_2);
        if (tableWidgetResMatSimulation->columnCount() < 7)
            tableWidgetResMatSimulation->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidgetResMatSimulation->setHorizontalHeaderItem(0, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidgetResMatSimulation->setHorizontalHeaderItem(1, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidgetResMatSimulation->setHorizontalHeaderItem(2, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidgetResMatSimulation->setHorizontalHeaderItem(3, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidgetResMatSimulation->setHorizontalHeaderItem(4, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidgetResMatSimulation->setHorizontalHeaderItem(5, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidgetResMatSimulation->setHorizontalHeaderItem(6, __qtablewidgetitem34);
        if (tableWidgetResMatSimulation->rowCount() < 7)
            tableWidgetResMatSimulation->setRowCount(7);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidgetResMatSimulation->setVerticalHeaderItem(0, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidgetResMatSimulation->setVerticalHeaderItem(1, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidgetResMatSimulation->setVerticalHeaderItem(2, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidgetResMatSimulation->setVerticalHeaderItem(3, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidgetResMatSimulation->setVerticalHeaderItem(4, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidgetResMatSimulation->setVerticalHeaderItem(5, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableWidgetResMatSimulation->setVerticalHeaderItem(6, __qtablewidgetitem41);
        tableWidgetResMatSimulation->setObjectName(QStringLiteral("tableWidgetResMatSimulation"));
        tableWidgetResMatSimulation->setGeometry(QRect(30, 20, 391, 241));
        tableWidgetResMatSimulation->setAutoScrollMargin(16);
        tableWidgetResMatSimulation->horizontalHeader()->setDefaultSectionSize(51);
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(180, 0, 47, 13));
        label_8 = new QLabel(tab_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 110, 16, 61));
        tabWidget->addTab(tab_2, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        tableWidgetResMatLucky = new QTableWidget(tab_5);
        if (tableWidgetResMatLucky->columnCount() < 7)
            tableWidgetResMatLucky->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidgetResMatLucky->setHorizontalHeaderItem(0, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tableWidgetResMatLucky->setHorizontalHeaderItem(1, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tableWidgetResMatLucky->setHorizontalHeaderItem(2, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tableWidgetResMatLucky->setHorizontalHeaderItem(3, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tableWidgetResMatLucky->setHorizontalHeaderItem(4, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tableWidgetResMatLucky->setHorizontalHeaderItem(5, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tableWidgetResMatLucky->setHorizontalHeaderItem(6, __qtablewidgetitem48);
        if (tableWidgetResMatLucky->rowCount() < 7)
            tableWidgetResMatLucky->setRowCount(7);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tableWidgetResMatLucky->setVerticalHeaderItem(0, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tableWidgetResMatLucky->setVerticalHeaderItem(1, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tableWidgetResMatLucky->setVerticalHeaderItem(2, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tableWidgetResMatLucky->setVerticalHeaderItem(3, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tableWidgetResMatLucky->setVerticalHeaderItem(4, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        tableWidgetResMatLucky->setVerticalHeaderItem(5, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        tableWidgetResMatLucky->setVerticalHeaderItem(6, __qtablewidgetitem55);
        tableWidgetResMatLucky->setObjectName(QStringLiteral("tableWidgetResMatLucky"));
        tableWidgetResMatLucky->setGeometry(QRect(30, 20, 391, 241));
        tableWidgetResMatLucky->setAutoScrollMargin(16);
        tableWidgetResMatLucky->horizontalHeader()->setDefaultSectionSize(51);
        label_5 = new QLabel(tab_5);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(170, 0, 47, 13));
        label_9 = new QLabel(tab_5);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 100, 16, 61));
        tabWidget->addTab(tab_5, QString());
        labelGoals = new QLabel(GameDialog);
        labelGoals->setObjectName(QStringLiteral("labelGoals"));
        labelGoals->setGeometry(QRect(90, 260, 101, 16));
        tabWidgetBfBets = new QTabWidget(GameDialog);
        tabWidgetBfBets->setObjectName(QStringLiteral("tabWidgetBfBets"));
        tabWidgetBfBets->setGeometry(QRect(10, 290, 1651, 611));
        tabWidgetBetsInfo = new QTabWidget(GameDialog);
        tabWidgetBetsInfo->setObjectName(QStringLiteral("tabWidgetBetsInfo"));
        tabWidgetBetsInfo->setGeometry(QRect(710, 10, 861, 281));
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        tableWidgetPlacedBets = new QTableWidget(tab_4);
        if (tableWidgetPlacedBets->columnCount() < 7)
            tableWidgetPlacedBets->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        tableWidgetPlacedBets->setHorizontalHeaderItem(0, __qtablewidgetitem56);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        tableWidgetPlacedBets->setHorizontalHeaderItem(1, __qtablewidgetitem57);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        tableWidgetPlacedBets->setHorizontalHeaderItem(2, __qtablewidgetitem58);
        QTableWidgetItem *__qtablewidgetitem59 = new QTableWidgetItem();
        tableWidgetPlacedBets->setHorizontalHeaderItem(3, __qtablewidgetitem59);
        QTableWidgetItem *__qtablewidgetitem60 = new QTableWidgetItem();
        tableWidgetPlacedBets->setHorizontalHeaderItem(4, __qtablewidgetitem60);
        QTableWidgetItem *__qtablewidgetitem61 = new QTableWidgetItem();
        tableWidgetPlacedBets->setHorizontalHeaderItem(5, __qtablewidgetitem61);
        QTableWidgetItem *__qtablewidgetitem62 = new QTableWidgetItem();
        tableWidgetPlacedBets->setHorizontalHeaderItem(6, __qtablewidgetitem62);
        tableWidgetPlacedBets->setObjectName(QStringLiteral("tableWidgetPlacedBets"));
        tableWidgetPlacedBets->setGeometry(QRect(10, 10, 841, 241));
        tableWidgetPlacedBets->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableWidgetPlacedBets->setSelectionBehavior(QAbstractItemView::SelectRows);
        tabWidgetBetsInfo->addTab(tab_4, QString());
        tabLuckyBets = new QWidget();
        tabLuckyBets->setObjectName(QStringLiteral("tabLuckyBets"));
        tabWidgetBetsInfo->addTab(tabLuckyBets, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        tabWidgetBetsInfo->addTab(tab_6, QString());
        label_10 = new QLabel(GameDialog);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(20, 260, 47, 13));

        retranslateUi(GameDialog);

        tabWidget->setCurrentIndex(3);
        tabWidgetBfBets->setCurrentIndex(-1);
        tabWidgetBetsInfo->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(GameDialog);
    } // setupUi

    void retranslateUi(QDialog *GameDialog)
    {
        GameDialog->setWindowTitle(QApplication::translate("GameDialog", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("GameDialog", "Game", 0));
        pushButtonWebsite->setText(QApplication::translate("GameDialog", "Website", 0));
        pushSetTime->setText(QApplication::translate("GameDialog", "SetTime (s)", 0));
        pushButtonStartStop->setText(QApplication::translate("GameDialog", "Start/Stop", 0));
        labelGameTime->setText(QApplication::translate("GameDialog", "0 min", 0));
        lineEditMaxExposure->setText(QApplication::translate("GameDialog", "300", 0));
        label->setText(QApplication::translate("GameDialog", "Max exposure", 0));
        pushButtonSetMaxExposure->setText(QApplication::translate("GameDialog", "Set max exposure", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetResMatReal->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("GameDialog", "0", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetResMatReal->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("GameDialog", "1", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetResMatReal->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("GameDialog", "2", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetResMatReal->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("GameDialog", "3", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetResMatReal->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("GameDialog", "4", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetResMatReal->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("GameDialog", "5", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetResMatReal->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("GameDialog", "7", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetResMatReal->verticalHeaderItem(0);
        ___qtablewidgetitem7->setText(QApplication::translate("GameDialog", "0", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetResMatReal->verticalHeaderItem(1);
        ___qtablewidgetitem8->setText(QApplication::translate("GameDialog", "1", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetResMatReal->verticalHeaderItem(2);
        ___qtablewidgetitem9->setText(QApplication::translate("GameDialog", "2", 0));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetResMatReal->verticalHeaderItem(3);
        ___qtablewidgetitem10->setText(QApplication::translate("GameDialog", "3", 0));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetResMatReal->verticalHeaderItem(4);
        ___qtablewidgetitem11->setText(QApplication::translate("GameDialog", "4", 0));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidgetResMatReal->verticalHeaderItem(5);
        ___qtablewidgetitem12->setText(QApplication::translate("GameDialog", "5", 0));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidgetResMatReal->verticalHeaderItem(6);
        ___qtablewidgetitem13->setText(QApplication::translate("GameDialog", "7", 0));
        label_6->setText(QApplication::translate("GameDialog", "Away", 0));
        label_7->setText(QApplication::translate("GameDialog", "<html><head/><body>H<br>o<br>m<br>e<br></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("GameDialog", "Real", 0));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidgetResMatRealnSim->horizontalHeaderItem(0);
        ___qtablewidgetitem14->setText(QApplication::translate("GameDialog", "0", 0));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidgetResMatRealnSim->horizontalHeaderItem(1);
        ___qtablewidgetitem15->setText(QApplication::translate("GameDialog", "1", 0));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidgetResMatRealnSim->horizontalHeaderItem(2);
        ___qtablewidgetitem16->setText(QApplication::translate("GameDialog", "2", 0));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidgetResMatRealnSim->horizontalHeaderItem(3);
        ___qtablewidgetitem17->setText(QApplication::translate("GameDialog", "3", 0));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidgetResMatRealnSim->horizontalHeaderItem(4);
        ___qtablewidgetitem18->setText(QApplication::translate("GameDialog", "4", 0));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidgetResMatRealnSim->horizontalHeaderItem(5);
        ___qtablewidgetitem19->setText(QApplication::translate("GameDialog", "5", 0));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidgetResMatRealnSim->horizontalHeaderItem(6);
        ___qtablewidgetitem20->setText(QApplication::translate("GameDialog", "6", 0));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidgetResMatRealnSim->verticalHeaderItem(0);
        ___qtablewidgetitem21->setText(QApplication::translate("GameDialog", "0", 0));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidgetResMatRealnSim->verticalHeaderItem(1);
        ___qtablewidgetitem22->setText(QApplication::translate("GameDialog", "1", 0));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidgetResMatRealnSim->verticalHeaderItem(2);
        ___qtablewidgetitem23->setText(QApplication::translate("GameDialog", "2", 0));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidgetResMatRealnSim->verticalHeaderItem(3);
        ___qtablewidgetitem24->setText(QApplication::translate("GameDialog", "3", 0));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidgetResMatRealnSim->verticalHeaderItem(4);
        ___qtablewidgetitem25->setText(QApplication::translate("GameDialog", "4", 0));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidgetResMatRealnSim->verticalHeaderItem(5);
        ___qtablewidgetitem26->setText(QApplication::translate("GameDialog", "5", 0));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidgetResMatRealnSim->verticalHeaderItem(6);
        ___qtablewidgetitem27->setText(QApplication::translate("GameDialog", "6", 0));
        label_2->setText(QApplication::translate("GameDialog", "Away", 0));
        label_3->setText(QApplication::translate("GameDialog", "<html><head/><body>H<br>o<br>m<br>e<br></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("GameDialog", "Real and Simulation", 0));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidgetResMatSimulation->horizontalHeaderItem(0);
        ___qtablewidgetitem28->setText(QApplication::translate("GameDialog", "0", 0));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidgetResMatSimulation->horizontalHeaderItem(1);
        ___qtablewidgetitem29->setText(QApplication::translate("GameDialog", "1", 0));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidgetResMatSimulation->horizontalHeaderItem(2);
        ___qtablewidgetitem30->setText(QApplication::translate("GameDialog", "2", 0));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidgetResMatSimulation->horizontalHeaderItem(3);
        ___qtablewidgetitem31->setText(QApplication::translate("GameDialog", "3", 0));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidgetResMatSimulation->horizontalHeaderItem(4);
        ___qtablewidgetitem32->setText(QApplication::translate("GameDialog", "4", 0));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidgetResMatSimulation->horizontalHeaderItem(5);
        ___qtablewidgetitem33->setText(QApplication::translate("GameDialog", "5", 0));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidgetResMatSimulation->horizontalHeaderItem(6);
        ___qtablewidgetitem34->setText(QApplication::translate("GameDialog", "7", 0));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidgetResMatSimulation->verticalHeaderItem(0);
        ___qtablewidgetitem35->setText(QApplication::translate("GameDialog", "0", 0));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidgetResMatSimulation->verticalHeaderItem(1);
        ___qtablewidgetitem36->setText(QApplication::translate("GameDialog", "1", 0));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidgetResMatSimulation->verticalHeaderItem(2);
        ___qtablewidgetitem37->setText(QApplication::translate("GameDialog", "2", 0));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidgetResMatSimulation->verticalHeaderItem(3);
        ___qtablewidgetitem38->setText(QApplication::translate("GameDialog", "3", 0));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidgetResMatSimulation->verticalHeaderItem(4);
        ___qtablewidgetitem39->setText(QApplication::translate("GameDialog", "4", 0));
        QTableWidgetItem *___qtablewidgetitem40 = tableWidgetResMatSimulation->verticalHeaderItem(5);
        ___qtablewidgetitem40->setText(QApplication::translate("GameDialog", "5", 0));
        QTableWidgetItem *___qtablewidgetitem41 = tableWidgetResMatSimulation->verticalHeaderItem(6);
        ___qtablewidgetitem41->setText(QApplication::translate("GameDialog", "7", 0));
        label_4->setText(QApplication::translate("GameDialog", "Away", 0));
        label_8->setText(QApplication::translate("GameDialog", "<html><head/><body>H<br>o<br>m<br>e<br></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("GameDialog", "Simulation", 0));
        QTableWidgetItem *___qtablewidgetitem42 = tableWidgetResMatLucky->horizontalHeaderItem(0);
        ___qtablewidgetitem42->setText(QApplication::translate("GameDialog", "0", 0));
        QTableWidgetItem *___qtablewidgetitem43 = tableWidgetResMatLucky->horizontalHeaderItem(1);
        ___qtablewidgetitem43->setText(QApplication::translate("GameDialog", "1", 0));
        QTableWidgetItem *___qtablewidgetitem44 = tableWidgetResMatLucky->horizontalHeaderItem(2);
        ___qtablewidgetitem44->setText(QApplication::translate("GameDialog", "2", 0));
        QTableWidgetItem *___qtablewidgetitem45 = tableWidgetResMatLucky->horizontalHeaderItem(3);
        ___qtablewidgetitem45->setText(QApplication::translate("GameDialog", "3", 0));
        QTableWidgetItem *___qtablewidgetitem46 = tableWidgetResMatLucky->horizontalHeaderItem(4);
        ___qtablewidgetitem46->setText(QApplication::translate("GameDialog", "4", 0));
        QTableWidgetItem *___qtablewidgetitem47 = tableWidgetResMatLucky->horizontalHeaderItem(5);
        ___qtablewidgetitem47->setText(QApplication::translate("GameDialog", "5", 0));
        QTableWidgetItem *___qtablewidgetitem48 = tableWidgetResMatLucky->horizontalHeaderItem(6);
        ___qtablewidgetitem48->setText(QApplication::translate("GameDialog", "7", 0));
        QTableWidgetItem *___qtablewidgetitem49 = tableWidgetResMatLucky->verticalHeaderItem(0);
        ___qtablewidgetitem49->setText(QApplication::translate("GameDialog", "0", 0));
        QTableWidgetItem *___qtablewidgetitem50 = tableWidgetResMatLucky->verticalHeaderItem(1);
        ___qtablewidgetitem50->setText(QApplication::translate("GameDialog", "1", 0));
        QTableWidgetItem *___qtablewidgetitem51 = tableWidgetResMatLucky->verticalHeaderItem(2);
        ___qtablewidgetitem51->setText(QApplication::translate("GameDialog", "2", 0));
        QTableWidgetItem *___qtablewidgetitem52 = tableWidgetResMatLucky->verticalHeaderItem(3);
        ___qtablewidgetitem52->setText(QApplication::translate("GameDialog", "3", 0));
        QTableWidgetItem *___qtablewidgetitem53 = tableWidgetResMatLucky->verticalHeaderItem(4);
        ___qtablewidgetitem53->setText(QApplication::translate("GameDialog", "4", 0));
        QTableWidgetItem *___qtablewidgetitem54 = tableWidgetResMatLucky->verticalHeaderItem(5);
        ___qtablewidgetitem54->setText(QApplication::translate("GameDialog", "5", 0));
        QTableWidgetItem *___qtablewidgetitem55 = tableWidgetResMatLucky->verticalHeaderItem(6);
        ___qtablewidgetitem55->setText(QApplication::translate("GameDialog", "7", 0));
        label_5->setText(QApplication::translate("GameDialog", "Away", 0));
        label_9->setText(QApplication::translate("GameDialog", "<html><head/><body>H<br>o<br>m<br>e<br></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("GameDialog", "Lucky", 0));
        labelGoals->setText(QApplication::translate("GameDialog", "TextLabel", 0));
        QTableWidgetItem *___qtablewidgetitem56 = tableWidgetPlacedBets->horizontalHeaderItem(0);
        ___qtablewidgetitem56->setText(QApplication::translate("GameDialog", "BetId", 0));
        QTableWidgetItem *___qtablewidgetitem57 = tableWidgetPlacedBets->horizontalHeaderItem(1);
        ___qtablewidgetitem57->setText(QApplication::translate("GameDialog", "Error", 0));
        QTableWidgetItem *___qtablewidgetitem58 = tableWidgetPlacedBets->horizontalHeaderItem(2);
        ___qtablewidgetitem58->setText(QApplication::translate("GameDialog", "Side", 0));
        QTableWidgetItem *___qtablewidgetitem59 = tableWidgetPlacedBets->horizontalHeaderItem(3);
        ___qtablewidgetitem59->setText(QApplication::translate("GameDialog", "Price", 0));
        QTableWidgetItem *___qtablewidgetitem60 = tableWidgetPlacedBets->horizontalHeaderItem(4);
        ___qtablewidgetitem60->setText(QApplication::translate("GameDialog", "Size", 0));
        QTableWidgetItem *___qtablewidgetitem61 = tableWidgetPlacedBets->horizontalHeaderItem(5);
        ___qtablewidgetitem61->setText(QApplication::translate("GameDialog", "Status", 0));
        QTableWidgetItem *___qtablewidgetitem62 = tableWidgetPlacedBets->horizontalHeaderItem(6);
        ___qtablewidgetitem62->setText(QApplication::translate("GameDialog", "MarketId", 0));
        tabWidgetBetsInfo->setTabText(tabWidgetBetsInfo->indexOf(tab_4), QApplication::translate("GameDialog", "Placed bets", 0));
        tabWidgetBetsInfo->setTabText(tabWidgetBetsInfo->indexOf(tabLuckyBets), QApplication::translate("GameDialog", "Lucky bets", 0));
        tabWidgetBetsInfo->setTabText(tabWidgetBetsInfo->indexOf(tab_6), QApplication::translate("GameDialog", "Green out", 0));
        label_10->setText(QApplication::translate("GameDialog", "Goals: ", 0));
    } // retranslateUi

};

namespace Ui {
    class GameDialog: public Ui_GameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEDIALOG_H
