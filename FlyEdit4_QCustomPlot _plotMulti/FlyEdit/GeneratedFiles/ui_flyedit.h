/********************************************************************************
** Form generated from reading UI file 'flyedit.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLYEDIT_H
#define UI_FLYEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_FlyEditClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_Submit;
    QPushButton *pushButton_ReMod;
    QPushButton *pushButton_DeleRow;
    QGroupBox *groupBox;
    QRadioButton *radioButton_Down;
    QRadioButton *radioButton_Up;
    QPushButton *pushButton_InsRow;
    QPushButton *pushButton_ImportExcel;
    QPushButton *pushButton_ExportToExcel;
    QGroupBox *groupBox_2;
    QTreeView *treeView_paraList;
    QGroupBox *groupBox_3;
    QTableView *tableView_Para1;
    QTableWidget *tableWidget_paraListCheck;
    QCustomPlot *customPlot_paraChecked;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FlyEditClass)
    {
        if (FlyEditClass->objectName().isEmpty())
            FlyEditClass->setObjectName(QStringLiteral("FlyEditClass"));
        FlyEditClass->resize(1302, 817);
        centralWidget = new QWidget(FlyEditClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_Submit = new QPushButton(centralWidget);
        pushButton_Submit->setObjectName(QStringLiteral("pushButton_Submit"));
        pushButton_Submit->setGeometry(QRect(406, 650, 93, 28));
        pushButton_ReMod = new QPushButton(centralWidget);
        pushButton_ReMod->setObjectName(QStringLiteral("pushButton_ReMod"));
        pushButton_ReMod->setGeometry(QRect(406, 620, 93, 28));
        pushButton_DeleRow = new QPushButton(centralWidget);
        pushButton_DeleRow->setObjectName(QStringLiteral("pushButton_DeleRow"));
        pushButton_DeleRow->setGeometry(QRect(500, 636, 81, 28));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(240, 620, 161, 51));
        radioButton_Down = new QRadioButton(groupBox);
        radioButton_Down->setObjectName(QStringLiteral("radioButton_Down"));
        radioButton_Down->setGeometry(QRect(10, 6, 81, 19));
        radioButton_Down->setChecked(true);
        radioButton_Up = new QRadioButton(groupBox);
        radioButton_Up->setObjectName(QStringLiteral("radioButton_Up"));
        radioButton_Up->setGeometry(QRect(10, 30, 81, 19));
        pushButton_InsRow = new QPushButton(groupBox);
        pushButton_InsRow->setObjectName(QStringLiteral("pushButton_InsRow"));
        pushButton_InsRow->setGeometry(QRect(83, 12, 71, 28));
        pushButton_ImportExcel = new QPushButton(centralWidget);
        pushButton_ImportExcel->setObjectName(QStringLiteral("pushButton_ImportExcel"));
        pushButton_ImportExcel->setGeometry(QRect(120, 20, 141, 23));
        pushButton_ExportToExcel = new QPushButton(centralWidget);
        pushButton_ExportToExcel->setObjectName(QStringLiteral("pushButton_ExportToExcel"));
        pushButton_ExportToExcel->setGeometry(QRect(310, 20, 141, 23));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 60, 211, 551));
        treeView_paraList = new QTreeView(groupBox_2);
        treeView_paraList->setObjectName(QStringLiteral("treeView_paraList"));
        treeView_paraList->setGeometry(QRect(11, 21, 189, 509));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(260, 60, 271, 551));
        tableView_Para1 = new QTableView(groupBox_3);
        tableView_Para1->setObjectName(QStringLiteral("tableView_Para1"));
        tableView_Para1->setGeometry(QRect(10, 20, 251, 511));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableView_Para1->sizePolicy().hasHeightForWidth());
        tableView_Para1->setSizePolicy(sizePolicy);
        tableView_Para1->setDragEnabled(false);
        tableWidget_paraListCheck = new QTableWidget(centralWidget);
        tableWidget_paraListCheck->setObjectName(QStringLiteral("tableWidget_paraListCheck"));
        tableWidget_paraListCheck->setGeometry(QRect(550, 80, 161, 511));
        customPlot_paraChecked = new QCustomPlot(centralWidget);
        customPlot_paraChecked->setObjectName(QStringLiteral("customPlot_paraChecked"));
        customPlot_paraChecked->setGeometry(QRect(730, 80, 561, 511));
        FlyEditClass->setCentralWidget(centralWidget);
        groupBox_3->raise();
        pushButton_Submit->raise();
        pushButton_ReMod->raise();
        pushButton_DeleRow->raise();
        groupBox->raise();
        pushButton_ImportExcel->raise();
        pushButton_ExportToExcel->raise();
        groupBox_2->raise();
        tableWidget_paraListCheck->raise();
        customPlot_paraChecked->raise();
        menuBar = new QMenuBar(FlyEditClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1302, 23));
        FlyEditClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FlyEditClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FlyEditClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FlyEditClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FlyEditClass->setStatusBar(statusBar);

        retranslateUi(FlyEditClass);

        QMetaObject::connectSlotsByName(FlyEditClass);
    } // setupUi

    void retranslateUi(QMainWindow *FlyEditClass)
    {
        FlyEditClass->setWindowTitle(QApplication::translate("FlyEditClass", "FlyEdit", 0));
        pushButton_Submit->setText(QApplication::translate("FlyEditClass", "\346\217\220\344\272\244\344\277\256\346\224\271", 0));
        pushButton_ReMod->setText(QApplication::translate("FlyEditClass", "\346\222\244\351\224\200\344\277\256\346\224\271", 0));
        pushButton_DeleRow->setText(QApplication::translate("FlyEditClass", "\345\210\240\351\231\244\351\200\211\344\270\255\350\241\214", 0));
        groupBox->setTitle(QString());
        radioButton_Down->setText(QApplication::translate("FlyEditClass", "\345\275\223\345\211\215\350\241\214\344\270\213", 0));
        radioButton_Up->setText(QApplication::translate("FlyEditClass", "\345\275\223\345\211\215\350\241\214\344\270\212", 0));
        pushButton_InsRow->setText(QApplication::translate("FlyEditClass", "\346\217\222\345\205\245\350\241\214", 0));
        pushButton_ImportExcel->setText(QApplication::translate("FlyEditClass", "\344\273\216Excel\345\257\274\345\205\245\346\226\260\346\225\260\346\215\256", 0));
        pushButton_ExportToExcel->setText(QApplication::translate("FlyEditClass", "\345\260\206\346\225\260\346\215\256\345\257\274\345\207\272\345\210\260Excel", 0));
        groupBox_2->setTitle(QApplication::translate("FlyEditClass", "\345\217\202\346\225\260\345\210\227\350\241\250", 0));
        groupBox_3->setTitle(QApplication::translate("FlyEditClass", "\346\211\200\351\200\211\345\217\202\346\225\260\346\225\260\346\215\256\344\277\241\346\201\257", 0));
    } // retranslateUi

};

namespace Ui {
    class FlyEditClass: public Ui_FlyEditClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLYEDIT_H
