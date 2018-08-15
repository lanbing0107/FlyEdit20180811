#ifndef FLYEDIT_H
#define FLYEDIT_H

#pragma execution_character_set("utf-8")

#include <QtWidgets/QMainWindow>
#include "ui_flyedit.h"

#include<qsqldatabase.h>
#include<qsqltablemodel.h>
//#include<qstandarditemmodel.h>

class FlyEdit : public QMainWindow
{
	Q_OBJECT

public:
	FlyEdit(QWidget *parent = 0);//构造函数
	~FlyEdit();//析构函数

//signals:
//	void activated(QModelIndex index);

private:
	QSqlDatabase m_db;//m_xxxx：类的成员变量命名规则。.h文件中定义成员变量，.cpp文件构造函数中实例化成员变量
	QSqlTableModel *m_model;
	QSqlTableModel *m_paraListmodel;
	void setupTreeView();
	//QString m_paraName;//成员变量
	QString m_path;
	//QString m_dataBasePathName;
	void setupTableWidget();
	int m_graphNumber;
	void paraSelectsAndPlot();


private:
	Ui::FlyEditClass ui;

private slots:
	//void onImport();
	void onSubmit();
	void onReMod();
	void onInsRow();
	void onDeleRow();
	void paraSelectAndShow();
	void onImportExcel();
	void onExportToExcel();
	void setParaSelectsAndPlot();
	void mouseDoubleToRescaleAxes();
};

#endif // FLYEDIT_H
