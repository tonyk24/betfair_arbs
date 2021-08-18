/********************************************************************************
** Form generated from reading UI file 'gameform.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEFORM_H
#define UI_GAMEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameForm
{
public:
    QVBoxLayout *verticalLayout;
    QProgressBar *progressBar;
    QPushButton *pushButton;
    QFrame *frame;
    QFormLayout *formLayout;
    QTableView *tableView;
    QGroupBox *groupBox;
    QFormLayout *formLayout_2;
    QLabel *label_4;
    QLabel *labelStartTime;
    QLabel *labelGameTime;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *labelGameStatus;
    QLabel *label_6;
    QLabel *labelGoalCount;
    QLabel *label_8;
    QLabel *labelScore;
    QTreeView *treeViewOdds;

    void setupUi(QWidget *GameForm)
    {
        if (GameForm->objectName().isEmpty())
            GameForm->setObjectName(QStringLiteral("GameForm"));
        GameForm->resize(673, 394);
        verticalLayout = new QVBoxLayout(GameForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        progressBar = new QProgressBar(GameForm);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        progressBar->setTextDirection(QProgressBar::BottomToTop);

        verticalLayout->addWidget(progressBar);

        pushButton = new QPushButton(GameForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        frame = new QFrame(GameForm);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        formLayout = new QFormLayout(frame);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        tableView = new QTableView(frame);
        tableView->setObjectName(QStringLiteral("tableView"));

        formLayout->setWidget(2, QFormLayout::LabelRole, tableView);

        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        formLayout_2 = new QFormLayout(groupBox);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_4);

        labelStartTime = new QLabel(groupBox);
        labelStartTime->setObjectName(QStringLiteral("labelStartTime"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, labelStartTime);

        labelGameTime = new QLabel(groupBox);
        labelGameTime->setObjectName(QStringLiteral("labelGameTime"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, labelGameTime);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_3);

        labelGameStatus = new QLabel(groupBox);
        labelGameStatus->setObjectName(QStringLiteral("labelGameStatus"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, labelGameStatus);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_6);

        labelGoalCount = new QLabel(groupBox);
        labelGoalCount->setObjectName(QStringLiteral("labelGoalCount"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, labelGoalCount);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_8);

        labelScore = new QLabel(groupBox);
        labelScore->setObjectName(QStringLiteral("labelScore"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, labelScore);


        formLayout->setWidget(2, QFormLayout::FieldRole, groupBox);


        verticalLayout->addWidget(frame);

        treeViewOdds = new QTreeView(GameForm);
        treeViewOdds->setObjectName(QStringLiteral("treeViewOdds"));
        treeViewOdds->setEditTriggers(QAbstractItemView::NoEditTriggers);
        treeViewOdds->setAutoExpandDelay(0);
        treeViewOdds->setItemsExpandable(true);
        treeViewOdds->setExpandsOnDoubleClick(false);

        verticalLayout->addWidget(treeViewOdds);


        retranslateUi(GameForm);

        QMetaObject::connectSlotsByName(GameForm);
    } // setupUi

    void retranslateUi(QWidget *GameForm)
    {
        GameForm->setWindowTitle(QApplication::translate("GameForm", "Form", 0));
        pushButton->setText(QApplication::translate("GameForm", "GetMarketCatalogue", 0));
        groupBox->setTitle(QApplication::translate("GameForm", "Status", 0));
        label_4->setText(QApplication::translate("GameForm", "Start time:", 0));
        labelStartTime->setText(QApplication::translate("GameForm", "TextLabel", 0));
        labelGameTime->setText(QApplication::translate("GameForm", "TextLabel", 0));
        label_2->setText(QApplication::translate("GameForm", "Game time: ", 0));
        label_3->setText(QApplication::translate("GameForm", "Game status:", 0));
        labelGameStatus->setText(QApplication::translate("GameForm", "TextLabel", 0));
        label_6->setText(QApplication::translate("GameForm", "Goal count:", 0));
        labelGoalCount->setText(QApplication::translate("GameForm", "TextLabel", 0));
        label_8->setText(QApplication::translate("GameForm", "Score: ", 0));
        labelScore->setText(QApplication::translate("GameForm", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class GameForm: public Ui_GameForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEFORM_H
