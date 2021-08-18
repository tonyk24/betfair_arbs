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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonLogin;
    QTextEdit *textEditAccountDetails;
    QLineEdit *lineEditUsername;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEditPassword;
    QPushButton *pushButtonGetEvents;
    QTableView *tableView;
    QLineEdit *lineEditAppKeyDelayed;
    QLabel *label_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(867, 325);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButtonLogin = new QPushButton(centralWidget);
        pushButtonLogin->setObjectName(QStringLiteral("pushButtonLogin"));
        pushButtonLogin->setGeometry(QRect(10, 110, 181, 23));
        textEditAccountDetails = new QTextEdit(centralWidget);
        textEditAccountDetails->setObjectName(QStringLiteral("textEditAccountDetails"));
        textEditAccountDetails->setGeometry(QRect(10, 140, 181, 131));
        lineEditUsername = new QLineEdit(centralWidget);
        lineEditUsername->setObjectName(QStringLiteral("lineEditUsername"));
        lineEditUsername->setGeometry(QRect(80, 10, 113, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 47, 13));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 30, 47, 13));
        lineEditPassword = new QLineEdit(centralWidget);
        lineEditPassword->setObjectName(QStringLiteral("lineEditPassword"));
        lineEditPassword->setGeometry(QRect(80, 30, 113, 20));
        pushButtonGetEvents = new QPushButton(centralWidget);
        pushButtonGetEvents->setObjectName(QStringLiteral("pushButtonGetEvents"));
        pushButtonGetEvents->setGeometry(QRect(214, 20, 631, 23));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(210, 50, 641, 221));
        lineEditAppKeyDelayed = new QLineEdit(centralWidget);
        lineEditAppKeyDelayed->setObjectName(QStringLiteral("lineEditAppKeyDelayed"));
        lineEditAppKeyDelayed->setGeometry(QRect(10, 80, 181, 20));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 60, 47, 13));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 867, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButtonLogin->setText(QApplication::translate("MainWindow", "Login", 0));
        label->setText(QApplication::translate("MainWindow", "User: ", 0));
        label_2->setText(QApplication::translate("MainWindow", "Password", 0));
        pushButtonGetEvents->setText(QApplication::translate("MainWindow", "Get Events", 0));
        label_3->setText(QApplication::translate("MainWindow", "App key delayed", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
