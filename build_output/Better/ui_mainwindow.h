/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *pushButtonEvents;
    QLineEdit *lineEdit;
    QComboBox *comboBox;
    QPushButton *pushButtonFunds;
    QTableWidget *tableWidget;
    QLineEdit *lineEditFilter;
    QLabel *label;
    QTableWidget *tableWidgetWalletHistory;
    QLineEdit *lineEditBf;
    QPushButton *pushButtonAddWalletEntry;
    QLineEdit *lineEditUB;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditCashIn;
    QLabel *label_4;
    QLabel *labelBalance;
    QGroupBox *groupBox;
    QTableWidget *tableWidgetExtSS;
    QPushButton *pushButtonHorn;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1006, 743);
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabsClosable(true);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        pushButtonEvents = new QPushButton(tab);
        pushButtonEvents->setObjectName(QStringLiteral("pushButtonEvents"));
        pushButtonEvents->setGeometry(QRect(20, 130, 75, 23));
        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(110, 10, 141, 20));
        comboBox = new QComboBox(tab);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(110, 130, 131, 22));
        pushButtonFunds = new QPushButton(tab);
        pushButtonFunds->setObjectName(QStringLiteral("pushButtonFunds"));
        pushButtonFunds->setGeometry(QRect(20, 10, 75, 23));
        tableWidget = new QTableWidget(tab);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 170, 631, 461));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setSortingEnabled(true);
        lineEditFilter = new QLineEdit(tab);
        lineEditFilter->setObjectName(QStringLiteral("lineEditFilter"));
        lineEditFilter->setGeometry(QRect(110, 100, 113, 20));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 100, 47, 13));
        tableWidgetWalletHistory = new QTableWidget(tab);
        if (tableWidgetWalletHistory->columnCount() < 6)
            tableWidgetWalletHistory->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetWalletHistory->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetWalletHistory->setHorizontalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetWalletHistory->setHorizontalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetWalletHistory->setHorizontalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetWalletHistory->setHorizontalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetWalletHistory->setHorizontalHeaderItem(5, __qtablewidgetitem6);
        tableWidgetWalletHistory->setObjectName(QStringLiteral("tableWidgetWalletHistory"));
        tableWidgetWalletHistory->setGeometry(QRect(260, 10, 511, 141));
        tableWidgetWalletHistory->horizontalHeader()->setDefaultSectionSize(75);
        lineEditBf = new QLineEdit(tab);
        lineEditBf->setObjectName(QStringLiteral("lineEditBf"));
        lineEditBf->setGeometry(QRect(820, 70, 113, 20));
        pushButtonAddWalletEntry = new QPushButton(tab);
        pushButtonAddWalletEntry->setObjectName(QStringLiteral("pushButtonAddWalletEntry"));
        pushButtonAddWalletEntry->setGeometry(QRect(780, 130, 161, 23));
        lineEditUB = new QLineEdit(tab);
        lineEditUB->setObjectName(QStringLiteral("lineEditUB"));
        lineEditUB->setGeometry(QRect(820, 100, 113, 20));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(780, 70, 31, 16));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(780, 100, 21, 16));
        lineEditCashIn = new QLineEdit(tab);
        lineEditCashIn->setObjectName(QStringLiteral("lineEditCashIn"));
        lineEditCashIn->setGeometry(QRect(820, 40, 113, 20));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(780, 40, 31, 16));
        labelBalance = new QLabel(tab);
        labelBalance->setObjectName(QStringLiteral("labelBalance"));
        labelBalance->setGeometry(QRect(780, 10, 151, 16));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(650, 170, 331, 461));
        tableWidgetExtSS = new QTableWidget(groupBox);
        if (tableWidgetExtSS->columnCount() < 1)
            tableWidgetExtSS->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetExtSS->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        tableWidgetExtSS->setObjectName(QStringLiteral("tableWidgetExtSS"));
        tableWidgetExtSS->setGeometry(QRect(10, 20, 311, 431));
        tableWidgetExtSS->horizontalHeader()->setDefaultSectionSize(300);
        tableWidgetExtSS->horizontalHeader()->setMinimumSectionSize(37);
        pushButtonHorn = new QPushButton(tab);
        pushButtonHorn->setObjectName(QStringLiteral("pushButtonHorn"));
        pushButtonHorn->setGeometry(QRect(30, 50, 75, 23));
        tabWidget->addTab(tab, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action->setText(QApplication::translate("MainWindow", "Login", 0));
        pushButtonEvents->setText(QApplication::translate("MainWindow", "Get events", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Football", 0)
         << QApplication::translate("MainWindow", "IceHockey", 0)
        );
        pushButtonFunds->setText(QApplication::translate("MainWindow", "Get Funds", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Name", 0));
        label->setText(QApplication::translate("MainWindow", "Filter:", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetWalletHistory->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Date", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetWalletHistory->horizontalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "CashIn", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetWalletHistory->horizontalHeaderItem(2);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Betfair", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetWalletHistory->horizontalHeaderItem(3);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Ext", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetWalletHistory->horizontalHeaderItem(4);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Total", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetWalletHistory->horizontalHeaderItem(5);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "Balance", 0));
        pushButtonAddWalletEntry->setText(QApplication::translate("MainWindow", "Add", 0));
        label_2->setText(QApplication::translate("MainWindow", "Betfair", 0));
        label_3->setText(QApplication::translate("MainWindow", "Ext", 0));
        label_4->setText(QApplication::translate("MainWindow", "CashIn", 0));
        labelBalance->setText(QApplication::translate("MainWindow", "Balance: ", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "SS Games", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetExtSS->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "Name", 0));
        pushButtonHorn->setText(QApplication::translate("MainWindow", "PushButton", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Events", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
