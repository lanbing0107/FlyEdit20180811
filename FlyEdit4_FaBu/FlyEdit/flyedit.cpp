#include "flyedit.h"

#include<qsqldatabase.h>
#include<qmessagebox.h>
#include<qsqlerror.h>
#include<qsqltablemodel.h>
#include<qitemselectionmodel.h>
#include<qfiledialog.h>
#include<QtXlsx\xlsxdocument.h>
#include<qsqlquery.h>
#include <qdebug.h>
#include<qsqlrecord.h>

//构造函数（实现初始化）。类的成员变量（m_xxxx）在此函数内实例化
FlyEdit::FlyEdit(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	////connect(ui.pushButton_Import, SIGNAL(clicked()), this, SLOT(onImport()));
	connect(ui.pushButton_Submit, SIGNAL(clicked()), this, SLOT(onSubmit()));
	connect(ui.pushButton_ReMod, SIGNAL(clicked()), this, SLOT(onReMod()));
	connect(ui.pushButton_InsRow, SIGNAL(clicked()), this, SLOT(onInsRow()));
	connect(ui.pushButton_DeleRow, SIGNAL(clicked()), this, SLOT(onDeleRow()));
	connect(ui.treeView_paraList, SIGNAL(clicked(QModelIndex)), this, SLOT(paraSelectAndShow()));////////
	connect(ui.pushButton_ImportExcel, SIGNAL(clicked()), this, SLOT(onImportExcel()));
	connect(ui.pushButton_ExportToExcel, SIGNAL(clicked()), this, SLOT(onExportToExcel()));
	
	connect(ui.customPlot_paraCheckedOriginal, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(mouseDoubleToRescaleAxesOriginal()));
	connect(ui.customPlot_paraCheckedNormalization, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(mouseDoubleToRescaleAxesNormalization()));
	/*m_db = QSqlDatabase::addDatabase("QMYSQL");
	m_model = new QSqlTableModel(this, m_db);
	m_paraListmodel = new QSqlTableModel(this, m_db);
	//QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	m_db.setHostName("localhost");
	m_db.setDatabaseName("test_wxb");
	m_db.setUserName("root");
	m_db.setPassword("123456");
	m_db.setPort(3306);
	bool ok = m_db.open();*/  //ok
	//QString err = db.lastError().databaseText();
	//QSqlTableModel *model = new QSqlTableModel(this, db);

	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_model = new QSqlTableModel(this, m_db);
	m_paraListmodel = new QSqlTableModel(this, m_db);
	m_path = QDir::currentPath();//可以用QDir::setCurrent(const QString &path)设置工作目录
	
	QString dataBasePathName = m_path.append("/test_flyEdit.db");
	m_db.setDatabaseName(dataBasePathName);//设置数据库名
	bool ok = m_db.open();
	if (ok == false)
	{
		QString sqlError = m_db.lastError().text();
		QMessageBox::warning(NULL, QStringLiteral("提示"), sqlError, QMessageBox::Yes);

		return;
	}
	//---------------------------------------------------------//
	setupTreeView();//调试完需释放！！！！！

	setupTableWidget();
	
	//-------初始化tableWidget之后，才能去绑定下面的信号槽函数，不然从数据库往tableWidget里一写内容就会触发信号！！！-------//
	connect(ui.tableWidget_paraListCheck, SIGNAL(cellChanged(int, int)), this, SLOT(setParaSelectsAndPlot()));//
	//connect(ui.customPlot_paraChecked, SIGNAL(mouseDoubleClick(QMouseEvent)), this, SLOT(mouseDoubleToRescaleAxes()));
}

FlyEdit::~FlyEdit()
{
	m_db.close();
}

//飞行包参数列表树的初始化：根据上一次导入的Excel所存入的数据库的表信息
void FlyEdit::setupTreeView()
{
	m_paraListmodel->clear();
	//QSqlQuery query(m_db);
	//QString sqlCmdSelect = QString("SELECT name FROM sqlite_master WHERE type='table' ORDER BY name");
	//query.exec(sqlCmdSelect);
	////error = query.lastError().databaseText();
	//QString tableName1;
	//if(query.next())
	//{
	//	tableName1 = query.value(0).toString();
	//}
	//else
	//{
	//	return;
	//}
	m_paraListmodel->setTable("paralist");//总表名总是paralist，这个是定死的！！！！！！
	m_paraListmodel->select();
	ui.treeView_paraList->setModel(m_paraListmodel);
	ui.treeView_paraList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.treeView_paraList->hideColumn(1);
	ui.treeView_paraList->resizeColumnToContents(0);//根据内容自适应列宽
	ui.treeView_paraList->show();
}

//从Excel导入所有参数数据（包含参数总表sheet和每个参数的sheet）
void FlyEdit::onImportExcel()
{
	QTime time1;
	time1.start();

	QString excelFileName = QFileDialog::getOpenFileName(this, tr("选择Excel文件"), m_path, tr("Excel 工作簿(*.xlsx);;Excel 97-2003 工作簿(*.xls)"));
	if (excelFileName == "")
	{
		return;
	}
	//-------------------------------------------------------//
	//if判断文件格式和内容（设置一个int类型标记量），记录是否正确打开且符合格式内容，否则提示错误，treeView中不显示

	//------------------------删除数据库原有表-----------------------------//
	QSqlQuery query(m_db);
	QString sqlCmdSelectOldTable = QString("SELECT name FROM sqlite_master WHERE type='table' ORDER BY name");
	query.exec(sqlCmdSelectOldTable);
	QString error;
	QStringList oldTableNames;
	while (query.next())
	{
		QString oldTableName = query.value(0).toString();
		oldTableNames.append(oldTableName);
		
	}
	int oldTableNumber = oldTableNames.size();
	QSqlQuery query2(m_db);
	for (int i = 0; i < oldTableNumber; ++i)
	{
		QString oldTableName = oldTableNames.value(i);
		QString sqlCmdDeleteOldTable = QString("DROP TABLE %1").arg(oldTableName);
		query2.exec(sqlCmdDeleteOldTable);
		//error = query2.lastError().databaseText();
	}
	
	qDebug() << time1.elapsed() / 1000.0 << "s";

	    //-------------------从Excel读sheet，创建数据库表--------------------//
	QXlsx::Document xlsx(excelFileName);
	QStringList sheetNames = xlsx.sheetNames();//Excel文件各sheet表名；sheet个数，从0开始
	int sheetNumber = sheetNames.size();//sheet个数，从0开始
	for (int i = 0; i < sheetNumber; ++i)
	{
		QString shName = sheetNames.value(i);//QString shName2 = sheetnames.at(i);
		xlsx.selectSheet(shName);
		QXlsx::CellRange range = xlsx.dimension();
		int rowCounts = range.lastRow();//获取打开文件的最后一行（注意，如果最后一行有空格也为有效行）
		int colCounts = range.lastColumn();//获取打开文件的最后一列
		QString sqlCmdCreateTable;
		QString fieldNameAndTypes;
		//将字段名及类型拼成字符串，便于下面创建相应的数据库表
		for (int j = 1; j < colCounts + 1; ++j)//几列即几个字段
		{
			QString fieldName = xlsx.read(1, j).toString();//得到要创建数据库表格的字段名
			fieldName.append(" TEXT NOT NULL,");//将字段类型全部定义为TEXT，并且不能为空，即NOT NULL
			fieldNameAndTypes.append(fieldName);
		}
		int lastIndexOfComma = fieldNameAndTypes.lastIndexOf(",");//字符位数从0开始计数
		fieldNameAndTypes.remove(lastIndexOfComma, 1);//得到了要创建数据库表格的字段名和类型
		sqlCmdCreateTable = QString("CREATE TABLE %1(%2)").arg(shName).arg(fieldNameAndTypes);
		query2.exec(sqlCmdCreateTable);
		//QString error = query2.lastError().databaseText();

		qDebug() << time1.elapsed() / 1000.0 << "s";

		//----------------------将Excel内容写入数据库------------------------//
		//一行一行地读和写
		for (int ir = 2; ir < rowCounts + 1; ++ir)
		{
			QString rowFieldValues = "\"";
			QString sqlCmdInsertRowFieldValues;
			//将每行的各列拼为一个QString，便于往数据库表中写
			for (int ic = 1; ic < colCounts + 1; ++ic)
			{
				QString fieldValue = xlsx.read(ir, ic).toString();
				fieldValue.append("\",\"");
				rowFieldValues.append(fieldValue);
			}
			lastIndexOfComma = rowFieldValues.lastIndexOf(",\"");
			rowFieldValues.remove(lastIndexOfComma, 2);
			sqlCmdInsertRowFieldValues = QString("INSERT INTO %1 VALUES(%2)").arg(shName).arg(rowFieldValues);
			query2.exec(sqlCmdInsertRowFieldValues);
			error = query2.lastError().databaseText();
		}

		qDebug() << time1.elapsed() / 1000.0 << "s";
	}

	qDebug() << time1.elapsed() / 1000.0 << "s";
	
	if (error.isEmpty())
	{
		/*QMessageBox msgBox;
		msgBox.setWindowTitle("提示");
		msgBox.setText("数据导入成功！");
		msgBox.exec();*/
		QMessageBox::information(this, QStringLiteral("提示"), "数据导入成功！", QMessageBox::Yes);
	}

	qDebug() << time1.elapsed() / 1000.0 << "s";

}


//点击treeView的某个项目，获取该参数的英文参数名，即数据库表名；并在右侧tableView中显示相应的数据库表内容
//---------------可以利用信号与槽之间的参数传递，简化并优化该函数！！！---------------------//
void FlyEdit::paraSelectAndShow()
{
	
	QItemSelectionModel *selectionModel = ui.treeView_paraList->selectionModel();
	QModelIndex index = selectionModel->currentIndex();
	//QString text = QString("(%1,%2)").arg(index.row()).arg(index.column());//text=(rownumber,colnumber),index.row()=rownumber
	index = index.sibling(index.row(), 1);
	QMap<int, QVariant> rowMap = m_paraListmodel->itemData(index);
	//QVariant value = rowMap.value(1, QVariant());
	QString paraName;
	if(rowMap.contains(2))
	{
		QVariant value = rowMap.value(2);
		paraName = value.toString();
	}
	//return m_paraName;
	if (paraName.isEmpty())
	{
		QMessageBox::warning(NULL, QStringLiteral("提示"), "请在左侧选择参数！", QMessageBox::Yes);
		return;
	}
	m_model->clear();
	m_model->setTable(paraName);
	m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_model->setSort(0, Qt::AscendingOrder);//升序排序
	m_model->select();
	//m_model->lastError();//怎么看错误代码？
	//m_model->setHeaderData(0, Qt::Horizontal, tr("Name"));
	//m_model->setHeaderData(1, Qt::Horizontal, tr("Salary"));
	ui.tableView_Para1->setModel(m_model);
	ui.tableView_Para1->resizeColumnToContents(0);//根据内容自适应列宽
	//ui.tableView_Para1->resizeColumnToContents(1);
	ui.tableView_Para1->show();
}

//提交修改
void FlyEdit::onSubmit()
{
	m_model->database().transaction();//开始事务操作

	if (m_model->submitAll()) // 提交所有被修改的数据到数据库中
	{
		if (m_model->database().commit())//提交//提交成功，事务将真正修改数据库数据
			QMessageBox::information(this, "提示", tr("数据修改成功!"));
	}
	else
	{
		m_model->database().rollback();//提交失败，事务回滚
		QMessageBox::warning(this, "提示", tr("数据库错误： %1").arg(m_model->lastError().text()), QMessageBox::Ok);
	}

}

//撤销未提交的修改,必须是未提交的
void FlyEdit::onReMod()
{
	m_model->revertAll();//撤销修改
}

//插入一行
void FlyEdit::onInsRow()
{
	int curRow = ui.tableView_Para1->currentIndex().row();
	if (ui.radioButton_Down->isChecked())
	{
		m_model->insertRow(curRow + 1);//在当前行下插入一行
	}
	else
	{
		m_model->insertRow(curRow);//在当前行上插入一行
	}
}

//删除选中行
void FlyEdit::onDeleRow()
{
	/*int curRow = ui.tableView_Para1->currentIndex().row();
	m_model->removeRow(curRow);
	m_model->submitAll();*/

	QItemSelectionModel *selections = ui.tableView_Para1->selectionModel();
	QModelIndexList selected = selections->selectedIndexes();

	foreach(QModelIndex index, selected)
	{
		QMap<int, int> rowMap;
		rowMap.insert(index.row(), 0);

		int rowToDel;
		QMapIterator<int, int> rowMapIterator(rowMap);
		rowMapIterator.toBack();
		if (rowMapIterator.hasPrevious())//用while?
		{
			rowMapIterator.previous();
			rowToDel = rowMapIterator.key();
			m_model->removeRow(rowToDel);
		}
	}
	int ok = QMessageBox::warning(this, "删除行！", "你确定删除所选行吗？", QMessageBox::Yes, QMessageBox::No);
	if (ok == QMessageBox::No)
	{
		m_model->revertAll();//提交，在数据库中删除该行
	}
	else
	{
		m_model->submitAll();//如果不删除，则撤销
	}

}

//将数据库中各表和内容导出至Excel
void FlyEdit::onExportToExcel()
{
	QString saveExcelFileName = QFileDialog::getSaveFileName(this, "保存为", m_path, "Excel 工作簿(*.xlsx);;Excel 97-2003 工作簿(*.xls)");
	if (saveExcelFileName == "")
	{
		return;
	}

	QTime time2;
	time2.start();


	QFile::remove(saveExcelFileName);
	QXlsx::Document xlsx(saveExcelFileName);
	//xlsx.save();//调试用
	QString error;
	QSqlQuery query(m_db);
	QString sqlCmdSelect = QString("SELECT name FROM sqlite_master WHERE type='table' ORDER BY name");
	query.exec(sqlCmdSelect);
	//error = query.lastError().databaseText();
	QStringList tableNames;
	while (query.next()) 
	{
		tableNames.append(query.value(0).toString());
		xlsx.addSheet(query.value(0).toString());
	}
	xlsx.deleteSheet("sheet1");//因为新创建的Excel文件默认有一个名字为”sheet1“的sheet

	qDebug() << time2.elapsed() / 1000.0 << "s";

	for (int i = 0; i < tableNames.size(); ++i) 
	{
		//也可以使用QSqlRecord来实现，QSqlField
		QString sqlCmdTableColName = QString("PRAGMA table_info([%1])").arg(tableNames.at(i));
		query.exec(sqlCmdTableColName);
		xlsx.selectSheet(tableNames.value(i));
		int nColCount = 0;//字段数，即该表有几列
		while (query.next()) 
		{
			//qDebug() << query.value(1).toString();
			xlsx.write(1, nColCount+1, query.value(1).toString());
			nColCount++;
		}
		//qDebug() << nColCount;
		QSqlQuery query2(m_db);
		QString sqlCmdSelectSheet = QString("SELECT * FROM %1").arg(tableNames.at(i));
		//至此
		query2.exec(sqlCmdSelectSheet);
		error = query2.lastError().databaseText();
		int nRowCount = 0;
		while (query2.next())
		{
			for (int j = 0; j < nColCount; ++j)
			{
				//qDebug() << query2.value(j).toString();
				xlsx.write(nRowCount + 2, j + 1, query2.value(j).toString());
			}
			nRowCount++;
		}
	}

	qDebug() << time2.elapsed() / 1000.0 << "s";

	xlsx.save();

	qDebug() << time2.elapsed() / 1000.0 << "s";

	if (error.isEmpty())
	{
		QMessageBox::information(this, QStringLiteral("提示"), "数据导出成功！", QMessageBox::Yes);
	}
	
	qDebug() << time2.elapsed() / 1000.0 << "s";

}

//初始化tableWidget，显示参数和复选框
void FlyEdit::setupTableWidget()
{
	QSqlQuery query(m_db);
	QString sqlCmdReadTableParalist = "SELECT *FROM paralist";
	query.exec(sqlCmdReadTableParalist);
	QSqlRecord rec = query.record();
	int colCounts = rec.count();//得到一条记录的count，即数据库表格列数，即字段数
	query.last();
	int rowCounts = query.at() + 1;//at()返回当前行的索引，索引从0开始；再加1，得到数据库表格行数
	ui.tableWidget_paraListCheck->setColumnCount(colCounts+1);//tableWidget多加一列来插入复选框，这一列计划设计在第0列
	ui.tableWidget_paraListCheck->setRowCount(rowCounts);
	//读取数据库表paralist的内容，往tableWidget中写。默认已知数据库表paralist的列数及各列含义，并隐藏第1、2列
	query.exec(sqlCmdReadTableParalist);
	int tableWidgetCurrentRow = 0;//tableWidget的行和列都从0开始计数
	while (query.next())
	{
		for (int j = 1; j < colCounts+1; ++j)//从tableWiget第1列开始写，而前面第0列空出来添加复选框checkBox
		{
			ui.tableWidget_paraListCheck->setItem(tableWidgetCurrentRow, j, new QTableWidgetItem(query.value(j-1).toString()));//将每条record的三列都写进去，写到tableWidget的1、2、3列
		}
		//QTableWidgetItem这个对象有CheckState属性，既能显示QCheckBox，又能读取状态
		QTableWidgetItem *checkBox = new QTableWidgetItem();
		checkBox->setCheckState(Qt::Unchecked);
		ui.tableWidget_paraListCheck->setItem(tableWidgetCurrentRow, 0, checkBox); //tableWidget第0列写入复选框checkBox
		tableWidgetCurrentRow = tableWidgetCurrentRow + 1;
	}
	ui.tableWidget_paraListCheck->hideColumn(1);//隐藏1、2列
	ui.tableWidget_paraListCheck->hideColumn(2);
	ui.tableWidget_paraListCheck->horizontalHeader()->hide();//隐藏tableWidget列头
	//设置垂直头不可见，同 ui.tableWidget_paraListCheck->verticalHeader()->hide();
	ui.tableWidget_paraListCheck->verticalHeader()->setVisible(false);
	ui.tableWidget_paraListCheck->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
	ui.tableWidget_paraListCheck->horizontalHeader()->setStretchLastSection(true);//设置充满表宽度
	ui.tableWidget_paraListCheck->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//设置自适应列宽
	//----------------下面这个函数怎么用？--------------//
	//ui.tableWidget_paraListCheck->setCellWidget(0, 0, new QCheckBox);

	////但是如何判断复选框是否被选中呢，方法是利用QTableWidget::cellChanged()函数，检查单元格内容的变化，然后连接此信号，在槽函数中检测checkBox的状态。
	////connect(tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(changeTest(int, int)));
	
}

void FlyEdit::setParaSelectsAndPlot()
{
	///QString selectItemText = ui.tableWidget_paraListCheck->item(row, 2)->text();//得到tableWidget第2列的内容，即参数英文名，也即数据库表名
	ui.customPlot_paraCheckedOriginal->clearGraphs();
	ui.customPlot_paraCheckedNormalization->clearGraphs();
	paraSelectsAndPlot(ui.customPlot_paraCheckedOriginal,0);
	paraSelectsAndPlot(ui.customPlot_paraCheckedNormalization, 1);
	ui.customPlot_paraCheckedOriginal->replot();
	ui.customPlot_paraCheckedNormalization->replot();
}



//在tableWidget中点复选框选择参数，在qCustomPlot中绘制所选参数的曲线
void FlyEdit::paraSelectsAndPlot(QCustomPlot *customPlot,int dataType)
{
	////QString selectItemText = ui.tableWidget_paraListCheck->item(row, 2)->text();//得到tableWidget第2列的内容，即参数英文名，也即数据库表名
	///QString graphName = "graph_" + selectItemText;
	//QCPGraph *
	QSqlQuery query(m_db);
	QString sqlCmdReadTableParalist = "SELECT *FROM paralist";
	query.exec(sqlCmdReadTableParalist);
	query.last();
	int paraRowCounts = query.at() + 1;//at()返回当前行的索引，索引从0开始；再加1，得到数据库表格行数

	QPen pen;
	for (int row = 0; row < paraRowCounts; ++row)
	{

		//先判断是否是“选中”操作。因为有可能是“取消选择”或其他操作！！！
		if (ui.tableWidget_paraListCheck->item(row, 0)->checkState() == Qt::Checked)
		{
			//QTableWidgetItem *item = ui.tableWidget_paraListCheck->item(row, 2);
			QString selectItemText = ui.tableWidget_paraListCheck->item(row, 2)->text();//得到tableWidget第2列的内容，即参数英文名，也即数据库表名
			QSqlQuery query(m_db);

			//测试得到数据库表x的行数的语句。可用！ 
			/*QString sqlCmd = "SELECT count(*) FROM x";
			query.exec(sqlCmd);
			query.next();
			int rowCountsDirectly = query.value(0).toInt();*/

			QString sqlCmdSelectTable = QString("SELECT *FROM %1").arg(selectItemText);//选择与所选某一复选框对应的数据库表
			query.exec(sqlCmdSelectTable);
			//注意：默认已知数据库表第0列是时间，第1列是值！！！
			//QSqlRecord rec = query.record();
			bool queryTorF = query.last();
			int rowCounts = query.at() + 1;//at()返回当前行的索引，索引从0开始；再加1，得到数据库表格列数
			if (queryTorF == false && rowCounts == -1)
			{
				QMessageBox::information(this, QStringLiteral("提示"), "该参数目前没有数据", QMessageBox::Yes);
				return;
			}
			customPlot->addGraph();
			pen.setColor(QColor(qSin(row*0.3) * 100 + 100, qSin(row*0.6 + 0.7) * 100 + 100, qSin(row*0.4 + 0.6) * 100 + 100));//设置每条参数曲线的颜色值
			customPlot->graph()->setPen(pen);
			customPlot->graph()->setName(selectItemText);

		
			QVector<QCPGraphData> timeAndData(rowCounts);//QCPGraphData(double key,double value)
			QVector<double> dataForSort(rowCounts);
			query.exec(sqlCmdSelectTable);
			int i = 0;
			QString format = "yyyy/MM/dd-HH:mm:ss:zzz";
			while (query.next())
			{
				QString sDateTimeFromSql = query.value(0).toString();
				QDateTime dDateTimeFromSqlString = QDateTime::fromString(sDateTimeFromSql, format);
				double dateTime = dDateTimeFromSqlString.toMSecsSinceEpoch() / 1000.0;//转换为了单位为S，精度为ms的 时间戳？
				timeAndData[i].key = dateTime;
				QString sDataFromSql = query.value(1).toString();
				double data = sDataFromSql.toDouble();
				timeAndData[i].value = data;
				dataForSort[i] = data;
				i = i + 1;
			}
			
			//QVector<QCPGraphData> sortData(rowCounts), timeAndDataValueToOne(rowCounts);//sortData用于排序，从而得到timeAndData中value的绝对值最大者
			//sortData.swap(timeAndData); 
			if (dataType == 1)
			{
				qSort(dataForSort.begin(), dataForSort.end());
				double minData = dataForSort.at(0);
				double maxData = dataForSort.at(rowCounts - 1);
				double MinDataAbs = qAbs(minData);
				double MaxDataAbs = qAbs(maxData);
				if (MinDataAbs != 0 || MaxDataAbs != 0)
				{
					double absMax = qMax(MinDataAbs, MaxDataAbs);
					for (int j = 0; j < rowCounts; ++j)
					{
						timeAndData[j].value = timeAndData[j].value / absMax;
					}
				}
			}
			else
			{
				dataType = 0;
			}
			customPlot->graph()->data()->set(timeAndData);
			customPlot->graph()->rescaleAxes(true);

		}

		else
		{
			continue;
		}
	}
	customPlot->rescaleAxes();
	customPlot->legend->setFont(QFont("Helvetica", 8));
	customPlot->legend->setRowSpacing(-3);
	customPlot->legend->setVisible(true);
	//设置底部坐标轴显示日期时间而不是数字
	QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
	dateTimeTicker->setDateTimeFormat("yyyy/MM/dd\nHH:mm:ss:zzz");
	customPlot->xAxis->setTicker(dateTimeTicker);
	customPlot->xAxis->setTickLabelFont(QFont("Helvetica", 8));
	customPlot->xAxis->setTickLabelRotation(20);
	customPlot->yAxis->setTickLabelFont(QFont("Helvetica", 8));
	//ui.customPlot_paraChecked->axisRect()->setupFullAxesBox();//四个刻度边线都调出来：除了下横轴和左纵轴刻度边线，还调出来了上横轴和右纵轴的刻度边线
	// Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking
	customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

}
void FlyEdit::mouseDoubleToRescaleAxesOriginal()
{
	ui.customPlot_paraCheckedOriginal->rescaleAxes();
	ui.customPlot_paraCheckedOriginal->replot();
}

void FlyEdit::mouseDoubleToRescaleAxesNormalization()
{
	ui.customPlot_paraCheckedNormalization->rescaleAxes();
	ui.customPlot_paraCheckedNormalization->replot();
}