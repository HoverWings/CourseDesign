#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newRoute.h"
#include"newDayInfo.h"
#include"newDayEXPInfo.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel(tr("Route"));
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(15);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "item" <<"information");
    ui->tableWidget->verticalHeader()->setVisible(false);//hide vertical header
    ui->tableWidget->setColumnWidth(0,200);
    ui->tableWidget->setColumnWidth(1,200);

    QTreeWidgetItem *All = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("All")));
	//file
	this->setWindowTitle("个人自助游管理信息系统_Powered_By_Hover");
    QObject::connect(ui->newRouteAction, SIGNAL(triggered()), this, SLOT(newRouteSlot()));
    QObject::connect(ui->newDayInfoAction, SIGNAL(triggered()), this, SLOT(newDayInfoSlot()));
    QObject::connect(ui->newDayEXPInfoAction, SIGNAL(triggered()), this, SLOT(newDayEXPInfoSlot()));

    //QObject::connect(ui->exitAction,SIGNAL(triggered()),this,SLOT(close()));//是否判断未保存 人性化设计
    //edit menu
    QObject::connect(ui->deleteRouteAction, SIGNAL(triggered()), this, SLOT(deleteRouteSlot()));
    QObject::connect(ui->deleteDayInfoAction, SIGNAL(triggered()), this, SLOT(deleteDayInfoSlot()));
    QObject::connect(ui->deleteDayEXPInfoAction, SIGNAL(triggered()), this, SLOT(deleteDayEXPInfoSlot()));

    QObject::connect(ui->showRouteAction, SIGNAL(triggered()), this, SLOT(showRouteslot()));
    QObject::connect(ui->showDayInfoAction, SIGNAL(triggered()), this, SLOT(showDayInfoslot()));
    QObject::connect(ui->showDayEXPInfoAction, SIGNAL(triggered()), this, SLOT(showDayEXPInfoslot()));
    QObject::connect(ui->showAllAction, SIGNAL(triggered()), this, SLOT(showAllslot()));

    QObject::connect(ui->saveToFileAction, SIGNAL(triggered()), this, SLOT(saveToFileSlot()));
    QObject::connect(ui->loadFromFileAction, SIGNAL(triggered()), this, SLOT(loadFromFileSlot()));
    QObject::connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(Show_info(QTreeWidgetItem* ,int)));//mouse click -> show information

    QObject::connect(ui->modifyRouteAction,SIGNAL(triggered()),this,SLOT(modifyRouteSlot()));
    QObject::connect(ui->modifyDayInfoAction,SIGNAL(triggered()),this,SLOT(modifyDayInfoSlot()));
    QObject::connect(ui->modifyDayEXPInfoAction,SIGNAL(triggered()),this,SLOT(modifyDayEXPInfoSlot()));

    QObject::connect(ui->countEXPAction,SIGNAL(triggered()),this,SLOT(countEXPSlot()));
    QObject::connect(ui->showTransInfoAction,SIGNAL(triggered()),this,SLOT(showTransInfoSlot()));
    QObject::connect(ui->showResidenceAction,SIGNAL(triggered()),this,SLOT(showResidenceSlot()));
    QObject::connect(ui->showDressingIndexAction,SIGNAL(triggered()),this,SLOT(showDressingIndexSlot()));
    QObject::connect(ui->sortRouteAction,SIGNAL(triggered()),this,SLOT(sortRouteSlot()));
    QObject::connect(ui->sortDayInfoAction,SIGNAL(triggered()),this,SLOT(sortDayInfoSlot()));
    QObject::connect(ui->sortDayEXPInfoAction,SIGNAL(triggered()),this,SLOT(sortDayEXPInfoSlot()));
}


void MainWindow::Mouse_position(QTreeWidgetItem* item)//get mouse position use three int to store
{
    now_index[0] = -1;//initialization
    now_index[1] = -1;
    now_index[2] = -1;
    int i = 0;
    QTreeWidgetItem* parent = item->parent();//get parent node
    while(parent != NULL){//find all parents
        now_index[i] = parent->indexOfChild(item);
        i++;
        item = parent;
        parent = item->parent();
    }
   // qDebug()<<now_index[0]<<now_index[1]<<now_index[2];
}
void MainWindow::Show_info(QTreeWidgetItem* item,int n){//show details
    Mouse_position(item);//get mouse position
    //nothing
    if(now_index[0] == -1 && now_index[1] == -1 && now_index[2] == -1)//未点击
    {
       return;
    }
    //route
    if(now_index[0] != -1 && now_index[1] == -1 && now_index[2] == -1)
    {
        p_Route p1=hRoute;
        //struct college_info* college_temp = head;
        for(int i = 0; i < now_index[0]; ++i)
        {//find position
            p1 = p1->nextRoute;
        }
        if(p1 == NULL)
        {
            return ;
        }

        ui->tableWidget->setItem(0, 0, new QTableWidgetItem("行程编号"));//show information
        ui->tableWidget->setItem(1, 0, new QTableWidgetItem("主要目的地"));
        ui->tableWidget->setItem(2, 0, new QTableWidgetItem("目的地所属国家/省份"));
        ui->tableWidget->setItem(3, 0, new QTableWidgetItem("最低温度"));
        ui->tableWidget->setItem(4, 0, new QTableWidgetItem("最高温度"));
        ui->tableWidget->setItem(5, 0, new QTableWidgetItem("推荐的着装"));
        ui->tableWidget->setItem(6, 0, new QTableWidgetItem("大交通"));
        ui->tableWidget->setItem(7, 0, new QTableWidgetItem("主要景点"));
        ui->tableWidget->setItem(8, 0, new QTableWidgetItem("异地办理手续行程编号"));
        ui->tableWidget->setItem(9, 0, new QTableWidgetItem("出发日期"));
        ui->tableWidget->setItem(10, 0, new QTableWidgetItem("返回到达日期"));
        ui->tableWidget->setItem(11, 0, new QTableWidgetItem("行程总天数"));
        ui->tableWidget->setItem(12, 0, new QTableWidgetItem("行程总人数"));
        ui->tableWidget->setItem(13, 0, new QTableWidgetItem("行程总费用"));

        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QString::number(p1->routeNum, 10)));
        ui->tableWidget->setItem(1, 1, new QTableWidgetItem(QString::fromUtf8(p1->routeName)));
        ui->tableWidget->setItem(2, 1, new QTableWidgetItem(QString::fromUtf8(p1->routeCountry)));
        ui->tableWidget->setItem(3, 1, new QTableWidgetItem(QString("%1").arg(p1->dressingIndex.minT)));
        ui->tableWidget->setItem(4, 1, new QTableWidgetItem(QString("%1").arg(p1->dressingIndex.maxT)));
        ui->tableWidget->setItem(5, 1, new QTableWidgetItem(QString::fromUtf8(p1->dressingIndex.recommendedDressing)));
        ui->tableWidget->setItem(6, 1, new QTableWidgetItem(QString::fromUtf8(p1->bigTrans)));
        ui->tableWidget->setItem(7, 1, new QTableWidgetItem(QString::fromUtf8(p1->mainScene)));
        ui->tableWidget->setItem(8, 1, new QTableWidgetItem(QString::fromUtf8(p1->remoteNum)));
        ui->tableWidget->setItem(9, 1, new QTableWidgetItem(QString::fromUtf8(p1->beginDate)));
        ui->tableWidget->setItem(10, 1, new QTableWidgetItem(QString::fromUtf8(p1->arriveDate)));
        ui->tableWidget->setItem(11, 1, new QTableWidgetItem(QString("%1").arg(p1->totalTime)));
        ui->tableWidget->setItem(12, 1, new QTableWidgetItem(QString("%1").arg(p1->totalNum)));
        ui->tableWidget->setItem(13, 1, new QTableWidgetItem(QString("%1").arg(p1->totalPrice)));
    }

    //DayInfo
    if(now_index[0] != -1 && now_index[1] != -1 && now_index[2] == -1)
    {
        p_Route p1=hRoute;
        for(int i = 0; i < now_index[1]; ++i)//find position
        {
            p1 = p1->nextRoute;
        }
        p_DayInfo  p2 = p1->hDayInfo;
        for(int i = 0; i < now_index[0]; ++i)
        {
            p2 = p2->nextDayInfo;
        }
        if(p2 == NULL)
        {
            return ;
        }
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem("所属行程编号"));//show information
        ui->tableWidget->setItem(1, 0, new QTableWidgetItem("序号"));
        ui->tableWidget->setItem(2, 0, new QTableWidgetItem("早餐地点"));
        ui->tableWidget->setItem(3, 0, new QTableWidgetItem("上午景点"));
        ui->tableWidget->setItem(4, 0, new QTableWidgetItem("午餐地点"));
        ui->tableWidget->setItem(5, 0, new QTableWidgetItem("下午景点"));
        ui->tableWidget->setItem(6, 0, new QTableWidgetItem("晚餐地点"));
        ui->tableWidget->setItem(7, 0, new QTableWidgetItem("小交通"));
        ui->tableWidget->setItem(8, 0, new QTableWidgetItem("住宿地点"));
        ui->tableWidget->setItem(9, 0, new QTableWidgetItem(""));
        ui->tableWidget->setItem(10, 0, new QTableWidgetItem(""));
        ui->tableWidget->setItem(11, 0, new QTableWidgetItem(""));
        ui->tableWidget->setItem(12, 0, new QTableWidgetItem(""));
        ui->tableWidget->setItem(13, 0, new QTableWidgetItem(""));



        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QString("%1").arg(p2->routeNum)));
        ui->tableWidget->setItem(1, 1, new QTableWidgetItem(QString("%1").arg(p2->order)));
        ui->tableWidget->setItem(2, 1, new QTableWidgetItem(QString::fromUtf8(p2->breakfastLoc)));
        ui->tableWidget->setItem(3, 1, new QTableWidgetItem(QString::fromUtf8(p2->morningScene)));
        ui->tableWidget->setItem(4, 1, new QTableWidgetItem(QString::fromUtf8(p2->LunchLoc)));
        ui->tableWidget->setItem(5, 1, new QTableWidgetItem(QString::fromUtf8(p2->afternoonScene)));
        ui->tableWidget->setItem(6, 1, new QTableWidgetItem(QString::fromUtf8(p2->dinnerLoc)));
        ui->tableWidget->setItem(7, 1, new QTableWidgetItem(QString::fromUtf8(p2->transInfo)));
        ui->tableWidget->setItem(8, 1, new QTableWidgetItem(QString::fromUtf8(p2->residence)));
        ui->tableWidget->setItem(9, 1, new QTableWidgetItem(""));
        ui->tableWidget->setItem(10, 1, new QTableWidgetItem(""));
        ui->tableWidget->setItem(11, 1, new QTableWidgetItem(""));
        ui->tableWidget->setItem(12, 1, new QTableWidgetItem(""));
        ui->tableWidget->setItem(13, 1, new QTableWidgetItem(""));

    }

    //DayEXPInfo
    if(now_index[0] != -1 && now_index[1] != -1 && now_index[2] != -1)
    {
        p_Route p1=hRoute;
        for(int i = 0; i < now_index[2]; ++i)//find position
        {
            p1 = p1->nextRoute;
        }
        p_DayInfo  p2 = p1->hDayInfo;
        for(int i = 0; i < now_index[1]; ++i)
        {
            p2 = p2->nextDayInfo;
        }
        p_DayEXPInfo p3=p2->hDayEXPInfo;
        for(int i = 0; i < now_index[0]; ++i)
        {
            p3 = p3->nextDayEXPInfo;
        }
        if(p3==NULL)
        {
            return;
        }
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem("所属行程编号"));//show information
        ui->tableWidget->setItem(1, 0, new QTableWidgetItem("序号"));
        ui->tableWidget->setItem(2, 0, new QTableWidgetItem("顺序号"));
        ui->tableWidget->setItem(3, 0, new QTableWidgetItem("交易时间"));
        ui->tableWidget->setItem(4, 0, new QTableWidgetItem("交易种类"));
        ui->tableWidget->setItem(5, 0, new QTableWidgetItem("交易金额"));
        ui->tableWidget->setItem(6, 0, new QTableWidgetItem("是否预支付"));
        ui->tableWidget->setItem(7, 0, new QTableWidgetItem("支付方式"));
        ui->tableWidget->setItem(8, 0, new QTableWidgetItem("说明"));
        ui->tableWidget->setItem(9, 0, new QTableWidgetItem(""));
        ui->tableWidget->setItem(10, 0, new QTableWidgetItem(""));
        ui->tableWidget->setItem(11, 0, new QTableWidgetItem(""));
        ui->tableWidget->setItem(12, 0, new QTableWidgetItem(""));
        ui->tableWidget->setItem(13, 0, new QTableWidgetItem(""));


        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QString("%1").arg(p3->routeNum)));
        ui->tableWidget->setItem(1, 1, new QTableWidgetItem(QString("%1").arg(p2->order)));
        ui->tableWidget->setItem(2, 1, new QTableWidgetItem(QString("%1").arg(p3->serialNum)));
        ui->tableWidget->setItem(3, 1, new QTableWidgetItem(QString::fromUtf8(p3->TxTime)));
        ui->tableWidget->setItem(4, 1, new QTableWidgetItem(QString::fromUtf8(p3->TxKind)));
        ui->tableWidget->setItem(5, 1, new QTableWidgetItem(QString("%1").arg(p3->TxAmount)));
        ui->tableWidget->setItem(6, 1, new QTableWidgetItem(QString::fromUtf8(p3->isPrepayment)));
        ui->tableWidget->setItem(7, 1, new QTableWidgetItem(QString::fromUtf8(p3->payment)));
        ui->tableWidget->setItem(8, 1, new QTableWidgetItem(QString::fromUtf8(p3->explain)));
        ui->tableWidget->setItem(9, 1, new QTableWidgetItem(""));
        ui->tableWidget->setItem(10, 1, new QTableWidgetItem(""));
        ui->tableWidget->setItem(11, 1, new QTableWidgetItem(""));
        ui->tableWidget->setItem(12, 1, new QTableWidgetItem(""));
        ui->tableWidget->setItem(13, 1, new QTableWidgetItem(""));
    }

}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::newRouteSlot()
{
    newRoute* dialog = new newRoute;
    dialog->show();//unmodal dialog
    dialog->exec();//modal dialog
    showTree();
}

void MainWindow::newDayInfoSlot()
{
	newDayInfo* dailog = new newDayInfo;
    dailog->exec();//modal dialog
    showTree();
}


void MainWindow::newDayEXPInfoSlot()
{
	newDayEXPInfo* dialog = new newDayEXPInfo;
    //dialog->show();//unmodal dialog
    dialog->exec();//modal dialog
    showTree();
}


void MainWindow::showAllslot()
{
     showTree();
	p_Route p1 = hRoute;
	QMessageBox msgBox;
	if (p1 == NULL)
	{

		msgBox.setText("当前无信息 输出错误");
		msgBox.exec();
		return;
	}
	QString str;
	while (p1 != NULL)
	{
		//printf("%d\n",p1->routeNum);
		str = str + QString("%1").arg(p1->routeNum) + "\n";
		p_DayInfo p2 = p1->hDayInfo;
		while (p2 != NULL)
		{
			//printf("\t%d\n", p2->order);
			str = str + "\t" + QString("%1").arg(p2->order) + "\n";
			p_DayEXPInfo p3 = p2->hDayEXPInfo;
			while (p3 != NULL)
			{
				//printf("\t\t%d\n", p3->serialNum);
				str = str + "\t\t" + QString("%1").arg(p3->serialNum) + "\n";
				p3 = p3->nextDayEXPInfo;
			}
			p2 = p2->nextDayInfo;
		}
		p1 = p1->nextRoute;
	}
	msgBox.setText(str);
	msgBox.exec();
	return;
}


void MainWindow::deleteRouteSlot()
{
	deletedialog = new QDialog;
	deletedialog->setWindowTitle("删除行程");
	QGroupBox *box = new QGroupBox(this);
	QPushButton *submitBtn = new QPushButton("确认");
	QPushButton *cancelBtn = new QPushButton("取消");
	connect(submitBtn, SIGNAL(clicked(bool)), this, SLOT(Act_deleteRouteSlot()));
	connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(cancelBtnSlot()));

	QLabel *routNum = new QLabel("行程编号");
	routeNumLineEdit = new QLineEdit;
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(routNum, 0, 0, 1, 1); //从哪里开始 跨度
	layout->addWidget(routeNumLineEdit, 0, 1, 1, 1); //从哪里开始 跨度

	layout->addWidget(submitBtn, 1, 0, 1, 1);
	layout->addWidget(cancelBtn, 1, 1, 1, 1);
	box->setLayout(layout);
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(box);
	deletedialog->setLayout(mainLayout);
    deletedialog->show();

}

void MainWindow::Act_deleteRouteSlot()
{
    int n1 = routeNumLineEdit->text().toInt();
	QMessageBox msgBox;
	deletedialog->close();
    if (deleteRoute(n1))
	{
        showTree();
		msgBox.setText("删除成功");
		msgBox.exec();
		return;
	}
	else
	{
		msgBox.setText("删除失败");
		msgBox.exec();
		return;
	}
}


void MainWindow::deleteDayInfoSlot()
{
	deletedialog = new QDialog;
	deletedialog->setWindowTitle("删除每日信息");
	QGroupBox *box = new QGroupBox(this);
	QPushButton *submitBtn = new QPushButton("确认");
	QPushButton *cancelBtn = new QPushButton("取消");
	connect(submitBtn, SIGNAL(clicked(bool)), this, SLOT(Act_deleteDayInfoSlot()));
	connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(cancelBtnSlot()));
	QLabel *routNum = new QLabel("行程编号");
	routeNumLineEdit = new QLineEdit;
	QLabel *order = new QLabel("序号");
	orderLineEdit = new QLineEdit;
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(routNum, 0, 0, 1, 1); //从哪里开始 跨度
	layout->addWidget(routeNumLineEdit, 0, 1, 1, 1); //从哪里开始 跨度
	layout->addWidget(order, 1, 0, 1, 1); //从哪里开始 跨度
	layout->addWidget(orderLineEdit, 1, 1, 1, 1); //从哪里开始 跨度

	layout->addWidget(submitBtn, 2, 0, 1, 1);
	layout->addWidget(cancelBtn, 2, 1, 1, 1);
	box->setLayout(layout);
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(box);
	deletedialog->setLayout(mainLayout);
	deletedialog->show();
}

void MainWindow::Act_deleteDayInfoSlot()
{
	QMessageBox msgBox;
	int n1 = routeNumLineEdit->text().toInt();
	int n2 = orderLineEdit->text().toInt();
	deletedialog->close();
	if (deleteDayInfo(n1, n2))
	{
        showTree();
		msgBox.setText("删除成功");
		msgBox.exec();
		return;
	}
	else
	{
		msgBox.setText("删除失败");
		msgBox.exec();
		return;
	}
}

void MainWindow::deleteDayEXPInfoSlot()
{
	deletedialog = new QDialog;
	deletedialog->setWindowTitle("删除每日信息");
	QGroupBox *box = new QGroupBox(this);
	QPushButton *submitBtn = new QPushButton("确认");
	QPushButton *cancelBtn = new QPushButton("取消");
	connect(submitBtn, SIGNAL(clicked(bool)), this, SLOT(Act_deleteDayEXPInfoSlot()));
	connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(cancelBtnSlot()));

	QLabel *routNum = new QLabel("行程编号");
	routeNumLineEdit = new QLineEdit;
	QLabel *order = new QLabel("序号");
	orderLineEdit = new QLineEdit;
    QLabel *serial = new QLabel("消费编号");
	serialNumLineEdit = new QLineEdit;
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(routNum, 0, 0, 1, 1);
	layout->addWidget(routeNumLineEdit, 0, 1, 1, 1);
	layout->addWidget(order, 1, 0, 1, 1); //从哪里开始 跨度
	layout->addWidget(orderLineEdit, 1, 1, 1, 1);
	layout->addWidget(serial, 2, 0, 1, 1);
	layout->addWidget(serialNumLineEdit, 2, 1, 1, 1);

	layout->addWidget(submitBtn, 3, 0, 1, 1);
	layout->addWidget(cancelBtn, 3, 1, 1, 1);
	box->setLayout(layout);
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(box);
	deletedialog->setLayout(mainLayout);
	deletedialog->show();
}

void MainWindow::Act_deleteDayEXPInfoSlot()
{
	QMessageBox msgBox;
	int n1 = routeNumLineEdit->text().toInt();
	int n2 = orderLineEdit->text().toInt();
	int n3 = serialNumLineEdit->text().toInt();
	deletedialog->close();
	if (deleteDayEXPInfo(n1, n2, n3))
    {showTree();
        showTree();
		msgBox.setText("删除成功");
		msgBox.exec();
		return;
	}
	else
	{
		msgBox.setText("删除失败");
		msgBox.exec();
		return;
	}
}

void MainWindow::quitBtnSLot()
{
	deletedialog->close();
}

void MainWindow::showRouteslot()
{
    showTree();
	deletedialog = new QDialog;
	deletedialog->setWindowTitle("查询行程");
	QGroupBox *box = new QGroupBox(this);
	QPushButton *submitBtn = new QPushButton("确认");
	QPushButton *cancelBtn = new QPushButton("取消");
	connect(submitBtn, SIGNAL(clicked(bool)), this, SLOT(Act_showRouteslot()));
	connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(cancelBtSlot()));

	QLabel *routNum = new QLabel("行程编号");
	routeNumLineEdit = new QLineEdit;
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(routNum, 0, 0, 1, 1); //从哪里开始 跨度
	layout->addWidget(routeNumLineEdit, 0, 1, 1, 1); //从哪里开始 跨度
	layout->addWidget(submitBtn, 1, 0, 1, 1);
	layout->addWidget(cancelBtn, 1, 1, 1, 1);
	box->setLayout(layout);
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(box);
	deletedialog->setLayout(mainLayout);
	deletedialog->show();
}

void MainWindow::Act_showRouteslot()
{

    int n1 = routeNumLineEdit->text().toInt();
	//查询信息并显示
	QMessageBox msgBox;
    p_Route p1 = findRouteByNum(n1);
	if (p1 == NULL)
	{
		deletedialog->close();
		msgBox.setText("NOT FOUND");
		msgBox.exec();
		return;
	}
	deletedialog->close();

	showDialog = new QDialog;
	showDialog->setWindowTitle("行程信息");
    QGroupBox *box = new QGroupBox(this);

	//浩大的工程啊
    QLabel *routeNum = new QLabel(QObject::tr("行程编号"));
    QLabel *s_routeNum = new QLabel();//s代表show
    QLabel *routeName = new QLabel("主要目的地名称");
    QLabel *s_routeName = new QLabel();
    QLabel *routeCountry = new QLabel("目的地所属国家/省份");
    QLabel *s_routeCountry = new QLabel();
    QLabel *minT = new QLabel("最低温度");
    QLabel *s_minT = new QLabel();
    QLabel *maxT = new QLabel("最高温度");
    QLabel *s_maxT = new QLabel();
    QLabel *recommendedDressing = new QLabel("推荐的着装");
    QLabel *s_recommendedDressing = new QLabel();
    QLabel *bigTrans = new QLabel("大交通");
    QLabel *s_bigTrans = new QLabel();
    QLabel *mainScene = new QLabel("主要景点");
    QLabel *s_mainScene = new QLabel();
    QLabel *remoteNum = new QLabel("异地办理手续行程编号");
    QLabel *s_remoteNum = new QLabel();
    QLabel *beginDate = new QLabel("出发日期");
    QLabel *s_beginDate = new QLabel();
    QLabel *arriveDate = new QLabel("返回到达日期");
    QLabel *s_arriveDate = new QLabel();
    QLabel *totalTime = new QLabel("行程总天数");
    QLabel *s_totalTime = new QLabel();
    QLabel *totalNum = new QLabel("行程总人数");
    QLabel *s_totalNum = new QLabel();
    QLabel *totalPrice = new QLabel("行程总费用");
    QLabel *s_totalPrice = new QLabel();
    //体力活

	//str1=QString("%1").arg(p1->routeNum);
    s_routeNum->setText(QString("%1").arg(p1->routeNum));
    s_routeName->setText(QString::fromUtf8(p1->routeName));
    s_routeCountry->setText(QString::fromUtf8(p1->routeCountry));
    s_minT->setText(QString("%1").arg(p1->dressingIndex.minT));
    s_maxT->setText(QString("%1").arg(p1->dressingIndex.maxT));
    s_recommendedDressing->setText(QString::fromUtf8(p1->dressingIndex.recommendedDressing));
    s_bigTrans->setText(QString::fromUtf8(p1->bigTrans));
    s_mainScene->setText(QString::fromUtf8(p1->mainScene));
    s_remoteNum->setText(QString::fromUtf8(p1->remoteNum));
    s_beginDate->setText(QString::fromUtf8(p1->beginDate));
    s_arriveDate->setText(QString::fromUtf8(p1->arriveDate));
    s_totalTime->setText(QString("%1").arg(p1->totalTime));
    s_totalNum->setText(QString("%1").arg(p1->totalNum));
    s_totalPrice->setText(QString("%1").arg(p1->totalPrice));

	//QLineEdit *route_routeNumLineEdit  = new QLineEdit();//注意声明形式
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(routeNum, 0, 0, 1, 1);
    layout->addWidget(s_routeNum, 0, 1, 1, 1);
    layout->addWidget(routeName, 1, 0, 1, 1);
    layout->addWidget(s_routeName, 1, 1, 1, 1);
    layout->addWidget(routeCountry, 2, 0, 1, 1);
    layout->addWidget(s_routeCountry, 2, 1, 1, 1);
    layout->addWidget(minT, 3, 0, 1, 1);
    layout->addWidget(s_minT, 3, 1, 1, 1);
    layout->addWidget(maxT, 4, 0, 1, 1);
    layout->addWidget(s_maxT, 4, 1, 1, 1);
    layout->addWidget(recommendedDressing, 5, 0, 1, 1);
    layout->addWidget(s_recommendedDressing, 5, 1, 1, 1);
    layout->addWidget(bigTrans, 6, 0, 1, 1);
    layout->addWidget(s_bigTrans, 6, 1, 1, 1);
    layout->addWidget(mainScene, 7, 0, 1, 1);
    layout->addWidget(s_mainScene, 7, 1, 1, 1);
    layout->addWidget(remoteNum, 8, 0, 1, 1);
    layout->addWidget(s_remoteNum, 8, 1, 1, 1);
    layout->addWidget(beginDate, 9, 0, 1, 1);
    layout->addWidget(s_beginDate, 9, 1, 1, 1);
    layout->addWidget(arriveDate, 10, 0, 1, 1);
    layout->addWidget(s_arriveDate, 10, 1, 1, 1);
    layout->addWidget(totalTime, 11, 0, 1, 1);
    layout->addWidget(s_totalTime, 11, 1, 1, 1);
    layout->addWidget(totalNum, 12, 0, 1, 1);
    layout->addWidget(s_totalNum, 12, 1, 1, 1);
    layout->addWidget(totalPrice, 13,0, 1, 1);
    layout->addWidget(s_totalPrice, 13, 1, 1, 1);

    box->setLayout(layout);
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(box);
	showDialog->setLayout(mainLayout);
	showDialog->show();
}


void MainWindow::showDayInfoslot()
{
    deletedialog = new QDialog;
    deletedialog->setWindowTitle("查询每日信息");
    QGroupBox *box = new QGroupBox(this);
    QPushButton *submitBtn = new QPushButton("确认");
    QPushButton *cancelBtn = new QPushButton("取消");
    connect(submitBtn, SIGNAL(clicked(bool)), this, SLOT(Act_showDayInfoSlot()));
    connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(cancelBtnSlot()));

    QLabel *routNum = new QLabel("行程编号");
    routeNumLineEdit = new QLineEdit;
    QLabel *order = new QLabel("序号");
    orderLineEdit = new QLineEdit;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(routNum, 0, 0, 1, 1); //从哪里开始 跨度
    layout->addWidget(routeNumLineEdit, 0, 1, 1, 1); //从哪里开始 跨度
    layout->addWidget(order, 1, 0, 1, 1); //从哪里开始 跨度
    layout->addWidget(orderLineEdit, 1, 1, 1, 1); //从哪里开始 跨度

    layout->addWidget(submitBtn, 2, 0, 1, 1);
    layout->addWidget(cancelBtn, 2, 1, 1, 1);
    box->setLayout(layout);
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(box);
    deletedialog->setLayout(mainLayout);
    deletedialog->show();
}


void MainWindow::Act_showDayInfoSlot()
{
    QMessageBox msgBox;
    int n1 = routeNumLineEdit->text().toInt();
    int n2 = orderLineEdit->text().toInt();
    p_DayInfo p2=findDayInfoByOrder(n1,n2);
    if (p2 == NULL)
    {
        deletedialog->close();
        msgBox.setText("NOT FOUND");
        msgBox.exec();
        return;
    }
    deletedialog->close();

    showDialog = new QDialog;
    showDialog->setWindowTitle("行程信息");
    QGroupBox *box = new QGroupBox(this);

    //浩大的工程啊
    QLabel *routeNum = new QLabel(QObject::tr("所属行程编号"));
    QLabel *s_routeNum = new QLabel();//s代表show
    QLabel *order = new QLabel(QObject::tr("序号"));
    QLabel *s_order = new QLabel();//s代表show
    QLabel *breakfastLoc = new QLabel("早餐地点");
    QLabel *s_breakfastLoc = new QLabel();
    QLabel *morningScene = new QLabel("上午景点");
    QLabel *s_morningScene = new QLabel();
    QLabel *LunchLoc = new QLabel("午餐地点");
    QLabel *s_LunchLoc = new QLabel();
    QLabel *afternoonScene = new QLabel("下午景点");
    QLabel *s_afternoonScene = new QLabel();
    QLabel *dinnerLoc = new QLabel("晚餐地点");
    QLabel *s_dinnerLoc = new QLabel();
    QLabel *transInfo = new QLabel("小交通");
    QLabel *s_transInfo = new QLabel();
    QLabel *residence = new QLabel("住宿地点");
    QLabel *s_residence = new QLabel();



    //str1=QString("%1").arg(p1->routeNum);
    s_routeNum->setText(QString("%1").arg(p2->routeNum));
    s_order->setText(QString("%1").arg(p2->order));
    s_breakfastLoc->setText(QString::fromUtf8(p2->breakfastLoc));
    s_morningScene->setText(QString::fromUtf8(p2->morningScene));
    s_LunchLoc->setText(QString::fromUtf8(p2->LunchLoc));
    s_afternoonScene->setText(QString::fromUtf8(p2->afternoonScene));
    s_dinnerLoc->setText(QString::fromUtf8(p2->dinnerLoc));
    s_transInfo->setText(QString::fromUtf8(p2->transInfo));
    s_residence->setText(QString::fromUtf8(p2->residence));


    //QLineEdit *route_routeNumLineEdit  = new QLineEdit();//注意声明形式
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(routeNum, 0, 0, 1, 1);
    layout->addWidget(s_routeNum, 0, 1, 1, 1);
    layout->addWidget(order, 1, 0, 1, 1);
    layout->addWidget(s_order, 1, 1, 1, 1);
    layout->addWidget(breakfastLoc, 2, 0, 1, 1);
    layout->addWidget(s_breakfastLoc, 2, 1, 1, 1);
    layout->addWidget(morningScene, 3, 0, 1, 1);
    layout->addWidget(s_morningScene, 3, 1, 1, 1);
    layout->addWidget(LunchLoc, 4, 0, 1, 1);
    layout->addWidget(s_LunchLoc, 4, 1, 1, 1);
    layout->addWidget(afternoonScene, 5, 0, 1, 1);
    layout->addWidget(s_afternoonScene, 5, 1, 1, 1);
    layout->addWidget(dinnerLoc, 6, 0, 1, 1);
    layout->addWidget(s_dinnerLoc, 6, 1, 1, 1);
    layout->addWidget(transInfo, 7, 0, 1, 1);
    layout->addWidget(s_transInfo, 7, 1, 1, 1);
    layout->addWidget(residence, 8, 0, 1, 1);
    layout->addWidget(s_residence, 8, 1, 1, 1);


    box->setLayout(layout);
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(box);
    showDialog->setLayout(mainLayout);
    showDialog->show();

}

void MainWindow::showDayEXPInfoslot()
{
    deletedialog = new QDialog;
    deletedialog->setWindowTitle("查询每日信息");
    QGroupBox *box = new QGroupBox(this);
    QPushButton *submitBtn = new QPushButton("确认");
    QPushButton *cancelBtn = new QPushButton("取消");
    connect(submitBtn, SIGNAL(clicked(bool)), this, SLOT(Act_showDayEXPInfoSlot()));
    connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(cancelBtnSlot()));

    QLabel *routNum = new QLabel("行程编号");
    routeNumLineEdit = new QLineEdit;
    QLabel *order = new QLabel("序号");
    orderLineEdit = new QLineEdit;
    QLabel *serial = new QLabel("序列号");
    serialNumLineEdit = new QLineEdit;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(routNum, 0, 0, 1, 1);
    layout->addWidget(routeNumLineEdit, 0, 1, 1, 1);
    layout->addWidget(order, 1, 0, 1, 1); //从哪里开始 跨度
    layout->addWidget(orderLineEdit, 1, 1, 1, 1);
    layout->addWidget(serial, 2, 0, 1, 1);
    layout->addWidget(serialNumLineEdit, 2, 1, 1, 1);

    layout->addWidget(submitBtn, 3, 0, 1, 1);
    layout->addWidget(cancelBtn, 3, 1, 1, 1);
    box->setLayout(layout);
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(box);
    deletedialog->setLayout(mainLayout);
    deletedialog->show();
}

void MainWindow::Act_showDayEXPInfoSlot()
{
    QMessageBox msgBox;
    int n1 = routeNumLineEdit->text().toInt();
    int n2 = orderLineEdit->text().toInt();
    int n3 = serialNumLineEdit->text().toInt();
    deletedialog->close();
    p_DayEXPInfo p3=findDayEXPInfoByserialNum(n1,n2,n3);
    if (p3==NULL)
    {
        msgBox.setText("NOT FOUND");
        msgBox.exec();
        return;
    }

    // ();  //此处有问题
    deletedialog->close();

    showDialog = new QDialog;
    showDialog->setWindowTitle("消费信息");
    QGroupBox *box = new QGroupBox(this);

    //浩大的工程啊
    QLabel *routeNum = new QLabel(QObject::tr("所属行程编号"));
    QLabel *s_routeNum = new QLabel();//s代表show
    QLabel *order = new QLabel(QObject::tr("序号"));
    QLabel *s_order = new QLabel();//s代表show
    QLabel *serialNum = new QLabel("顺序号");
    QLabel *s_serialNum = new QLabel();
    QLabel *TxTime = new QLabel("交易时间");
    QLabel *s_TxTime = new QLabel();
    QLabel *TxKind = new QLabel("交易种类");
    QLabel *s_TxKind = new QLabel();
    QLabel *TxAmount = new QLabel("交易金额");
    QLabel *s_TxAmount = new QLabel();
    QLabel *isPrepayment = new QLabel("是否预支付");
    QLabel *s_isPrepayment = new QLabel();
    QLabel *payment = new QLabel("支付方式");
    QLabel *s_payment = new QLabel();
    QLabel *explain = new QLabel("住宿地点");
    QLabel *s_explain = new QLabel();



    //str1=QString("%1").arg(p1->routeNum);
    s_routeNum->setText(QString("%1").arg(p3->routeNum));
    s_order->setText(QString("%1").arg(p3->order));
    s_serialNum->setText(QString("%1").arg(p3->serialNum));
    s_TxTime->setText(QString::fromUtf8(p3->TxTime));
    s_TxKind->setText(QString::fromUtf8(p3->TxKind));
    s_TxAmount->setText(QString("%1").arg(p3->TxAmount));
    s_isPrepayment->setText(QString::fromUtf8(p3->isPrepayment));
    s_payment->setText(QString::fromUtf8(p3->payment));
    s_explain->setText(QString::fromUtf8(p3->explain));


    //QLineEdit *route_routeNumLineEdit  = new QLineEdit();//注意声明形式
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(routeNum, 0, 0, 1, 1);
    layout->addWidget(s_routeNum, 0, 1, 1, 1);
    layout->addWidget(order, 1, 0, 1, 1);
    layout->addWidget(s_order, 1, 1, 1, 1);
    layout->addWidget(serialNum, 2, 0, 1, 1);
    layout->addWidget(s_serialNum, 2, 1, 1, 1);
    layout->addWidget(TxTime, 3, 0, 1, 1);
    layout->addWidget(s_TxTime, 3, 1, 1, 1);
    layout->addWidget(TxKind, 4, 0, 1, 1);
    layout->addWidget(s_TxKind, 4, 1, 1, 1);
    layout->addWidget(TxAmount, 5, 0, 1, 1);
    layout->addWidget(s_TxAmount, 5, 1, 1, 1);
    layout->addWidget(isPrepayment, 6, 0, 1, 1);
    layout->addWidget(s_isPrepayment, 6, 1, 1, 1);
    layout->addWidget(payment, 7, 0, 1, 1);
    layout->addWidget(s_payment, 7, 1, 1, 1);
    layout->addWidget(explain, 8, 0, 1, 1);
    layout->addWidget(s_explain, 8, 1, 1, 1);


    box->setLayout(layout);
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(box);
    showDialog->setLayout(mainLayout);
    showDialog->show();
}

void MainWindow::saveToFileSlot()
{
    QMessageBox msgBox;
    if(saveToFile())
    {
        msgBox.setText("Save To File Successfully");
        msgBox.exec();
        return;
    }
    else
    {
        msgBox.setText("Save To File Fail");
        msgBox.exec();
        return;
    }
}

void MainWindow::loadFromFileSlot()//注意第一次保存
{
    QMessageBox msgBox;
    if(loadFromFile())
    {
        showTree();
        msgBox.setText("load From File Successfully");
        msgBox.exec();
        return;
    }
    else
    {
        showTree();
        msgBox.setText("load From File fail");
        msgBox.exec();
        return;
    }
}

void MainWindow::showTree()
{
    ui->treeWidget->clear();//first clear old tree
    QTreeWidgetItem *All = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("All")));
    p_Route p1 = hRoute;
    if (p1 == NULL)
    {
        return;
    }
    QString str;
    while (p1 != NULL)
    {
        QTreeWidgetItem *routeItem = new QTreeWidgetItem(QStringList("Route"+QString::number(p1->routeNum, 10)));
        All->addChild(routeItem);
        p_DayInfo p2 = p1->hDayInfo;
        while (p2 != NULL)
        {
            QTreeWidgetItem *dayInfoItem = new QTreeWidgetItem(QStringList("DayInfo"+QString::number(p2->order, 10)));
            routeItem->addChild(dayInfoItem);
            p_DayEXPInfo p3 = p2->hDayEXPInfo;
            while (p3 != NULL)
            {
                str = str + "\t\t" + QString("%1").arg(p3->serialNum) + "\n";
                QTreeWidgetItem *dayEXPInfoItem = new QTreeWidgetItem(QStringList("DayEXPInfo"+QString::number(p3->serialNum, 10)));
                dayInfoItem->addChild(dayEXPInfoItem);
                p3 = p3->nextDayEXPInfo;
            }
            p2 = p2->nextDayInfo;
        }
        p1 = p1->nextRoute;
    }
    ui->treeWidget->expandAll();//expend all nodes
    return;
}




void MainWindow::on_modifyButton_clicked()
{
    //Mouse_position(item);//get mouse position
    if(now_index[0] == -1 && now_index[1] == -1 && now_index[2] == -1)//未点击
    {
       return;
    }
    //Route
    if(now_index[0] != -1 && now_index[1] == -1 && now_index[2] == -1)
    {
        p_Route p1=hRoute;
        //struct college_info* college_temp = head;
        for(int i = 0; i < now_index[0]; ++i)
        {//find position
            p1 = p1->nextRoute;
        }
        if(p1 == NULL)
        {
            return ;
        }

        p1->routeNum=ui->tableWidget->item(0,1)->text().toInt();//int
        strcpy(p1->routeName, ui->tableWidget->item(1,1)->text().toStdString().c_str());
        strcpy(p1->routeCountry, ui->tableWidget->item(2,1)->text().toStdString().c_str());
        p1->dressingIndex.minT=ui->tableWidget->item(3,1)->text().toInt();
        p1->dressingIndex.maxT=ui->tableWidget->item(4,1)->text().toInt();
        strcpy(p1->dressingIndex.recommendedDressing, ui->tableWidget->item(5,1)->text().toStdString().c_str());
        strcpy(p1->bigTrans, ui->tableWidget->item(6,1)->text().toStdString().c_str());
        strcpy(p1->mainScene, ui->tableWidget->item(7,1)->text().toStdString().c_str());
        strcpy(p1->remoteNum, ui->tableWidget->item(8,1)->text().toStdString().c_str());
        strcpy(p1->beginDate, ui->tableWidget->item(9,1)->text().toStdString().c_str());
        strcpy(p1->arriveDate, ui->tableWidget->item(10,1)->text().toStdString().c_str());
        p1->totalTime=ui->tableWidget->item(11,1)->text().toInt();//int  这个也是输入的
        p1->totalNum=ui->tableWidget->item(12,1)->text().toInt();//int
        p1->totalPrice=ui->tableWidget->item(13,1)->text().toFloat();//float

    }
    //DayInfo
    if(now_index[0] != -1 && now_index[1] != -1 && now_index[2] == -1)
    {
        p_Route p1=hRoute;
        for(int i = 0; i < now_index[1]; ++i)//find position
        {
            p1 = p1->nextRoute;
        }
        p_DayInfo  p2 = p1->hDayInfo;
        for(int i = 0; i < now_index[0]; ++i)
        {
            p2 = p2->nextDayInfo;
        }
        if(p2 == NULL)
        {
            return ;
        }
        p2->routeNum=ui->tableWidget->item(0,1)->text().toInt();//int
        p2->order=ui->tableWidget->item(1,1)->text().toInt();//int
        strcpy(p2->breakfastLoc, ui->tableWidget->item(2,1)->text().toStdString().c_str());
        strcpy(p2->morningScene, ui->tableWidget->item(3,1)->text().toStdString().c_str());
        strcpy(p2->LunchLoc, ui->tableWidget->item(4,1)->text().toStdString().c_str());
        strcpy(p2->afternoonScene, ui->tableWidget->item(5,1)->text().toStdString().c_str());
        strcpy(p2->dinnerLoc, ui->tableWidget->item(6,1)->text().toStdString().c_str());
        strcpy(p2->transInfo, ui->tableWidget->item(7,1)->text().toStdString().c_str());
        strcpy(p2->residence, ui->tableWidget->item(8,1)->text().toStdString().c_str());
    }
    //DayEXPInfo
    if(now_index[0] != -1 && now_index[1] != -1 && now_index[2] != -1)
    {
        p_Route p1=hRoute;
        for(int i = 0; i < now_index[2]; ++i)//find position
        {
            p1 = p1->nextRoute;
        }
        p_DayInfo  p2 = p1->hDayInfo;
        for(int i = 0; i < now_index[1]; ++i)
        {
            p2 = p2->nextDayInfo;
        }
        p_DayEXPInfo p3=p2->hDayEXPInfo;
        for(int i = 0; i < now_index[0]; ++i)
        {
            p3 = p3->nextDayEXPInfo;
        }
        if(p3==NULL)
        {
            return;
        }
        p3->routeNum=ui->tableWidget->item(0,1)->text().toInt();//int
        p3->order=ui->tableWidget->item(1,1)->text().toInt();//int
        p3->serialNum=ui->tableWidget->item(2,1)->text().toInt();//int
        strcpy(p3->TxTime, ui->tableWidget->item(3,1)->text().toStdString().c_str());
        strcpy(p3->TxKind, ui->tableWidget->item(4,1)->text().toStdString().c_str());
        p3->TxAmount=ui->tableWidget->item(5,1)->text().toFloat();//float
        strcpy(p3->isPrepayment, ui->tableWidget->item(6,1)->text().toStdString().c_str());
        strcpy(p3->payment, ui->tableWidget->item(7,1)->text().toStdString().c_str());
        strcpy(p3->explain, ui->tableWidget->item(8,1)->text().toStdString().c_str());
    }
    showTree();
}



void MainWindow::countEXPSlot()
{
    showTree();
    QTableWidget *  tableWidget = new QTableWidget(this);
    tableWidget->setRowCount(15);
    tableWidget->setColumnCount(10);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "费用类型" <<"费用金额");
    tableWidget->verticalHeader()->setVisible(false);//hide vertical header
    tableWidget->setColumnWidth(0,200);
    tableWidget->setColumnWidth(1,200);
    float residence[10]={0};
    float bigTrans[10]={0};
    float littleTrans[10]={0};
    float food[10]={0};
    float tickets[10]={0};
    float shopping[10]={0};
    float others[10]={0};
    float pp_residence=0;
    float pp_bigTrans=0;
    float pp_litteTrans=0;
    float pp_food=0;
    float pp_tickets=0;
    float pp_shopping=0;
    float pp_others=0;
    float total;

    tableWidget->setItem(0, 0, new QTableWidgetItem("行程编号："));//show information
    tableWidget->setItem(1, 0, new QTableWidgetItem("住宿"));//show information
    tableWidget->setItem(2, 0, new QTableWidgetItem("大交通"));
    tableWidget->setItem(3, 0, new QTableWidgetItem("小交通"));
    tableWidget->setItem(4, 0, new QTableWidgetItem("餐饮"));
    tableWidget->setItem(5, 0, new QTableWidgetItem("门票"));
    tableWidget->setItem(6, 0, new QTableWidgetItem("购物"));
    tableWidget->setItem(7, 0, new QTableWidgetItem("其他"));
    tableWidget->setItem(8, 0, new QTableWidgetItem("总计"));


    //QPieSlice *slice_red = series->slices().at(0);
    //QPieSlice *slice_green = series->slices().at(1);
    //QPieSlice *slice_blue = series->slices().at(2);
    //slice_red->setColor(QColor(255,0,0,255));
    //slice_green->setColor(QColor(0,255,0,255));
    //slice_blue->setColor(QColor(0,0,255,255));
    QChart *chart[10];//最多显示10个图表
    QPieSeries *series[10];
    QChartView *chartview[10];

    showDialog = new QDialog;
    showDialog->setWindowTitle("行程信息");
    QGroupBox *box = new QGroupBox(this);
    QGridLayout *layout = new QGridLayout;
    box->setLayout(layout);
    layout->addWidget(tableWidget,0,0);



    p_Route p1 = hRoute;
    int t1=1;//最终数目为t1-1
    int t2=0;
    int t3=0;
    if (p1 == NULL)
    {

       //MessageBox msgBox;
      // msgBox.setText("当前无信息 输出错误");
       //msgBox.exec();

       return;
    }
    while (p1 != NULL)
    {
       //str = str + QString("%1").arg(p1->routeNum) + "\n";
       p_DayInfo p2 = p1->hDayInfo;
       while (p2 != NULL)
       {
           //str = str + "\t" + QString("%1").arg(p2->order) + "\n";
           p_DayEXPInfo p3 = p2->hDayEXPInfo;
           while (p3 != NULL)
           {
               //str = str + "\t\t" + QString("%1").arg(p3->serialNum) + "\n";
               if(strcmp(p3->TxKind, "住宿")==0)
               {
                    residence[t1]+=p3->TxAmount;
               }
               else
               {
                   if(strcmp(p3->TxKind, "大交通")==0)
                   {
                        bigTrans[t1]+=p3->TxAmount;
                   }
                   else
                   {
                       if(strcmp(p3->TxKind, "小交通")==0)
                       {
                            littleTrans[t1]+=p3->TxAmount;
                       }
                       else
                       {
                           if(strcmp(p3->TxKind, "餐饮")==0)
                           {
                                food[t1]+=p3->TxAmount;
                           }
                           else
                           {
                               if(strcmp(p3->TxKind, "门票")==0)
                               {
                                    tickets[t1]+=p3->TxAmount;
                               }
                               else
                               {
                                   if(strcmp(p3->TxKind, "购物")==0)
                                   {
                                        shopping[t1]+=p3->TxAmount;
                                   }
                                   else
                                   {
                                        others[t1]+=p3->TxAmount;
                                   }
                               }
                           }
                       }
                   }
               }
               p3=p3->nextDayEXPInfo;
               t3++;
           }
           p2 = p2->nextDayInfo;
           t2++;
       }
       p1 = p1->nextRoute;//为什么不显示？
       t1++;
    }

    p1=hRoute;
    int index_mostTickets=1;

    for(int i=1;i<t1;i++)
    {

        chart[i]=new QChart();
        series[i]= new QPieSeries();
        tableWidget->setItem(0, i, new QTableWidgetItem(QString("%1").arg(p1->routeNum)));
        tableWidget->setItem(1, i, new QTableWidgetItem(QString("%1").arg(residence[i])));
        tableWidget->setItem(2, i, new QTableWidgetItem(QString("%1").arg(bigTrans[i])));
        tableWidget->setItem(3, i, new QTableWidgetItem(QString("%1").arg(littleTrans[i])));
        tableWidget->setItem(4, i, new QTableWidgetItem(QString("%1").arg(food[i])));
        tableWidget->setItem(5, i, new QTableWidgetItem(QString("%1").arg(tickets[i])));
        tableWidget->setItem(6, i, new QTableWidgetItem(QString("%1").arg(shopping[i])));
        tableWidget->setItem(7, i, new QTableWidgetItem(QString("%1").arg(others[i])));
        total=residence[i]+bigTrans[i]+littleTrans[i]+food[i]+tickets[i]+shopping[i]+others[i];
        tableWidget->setItem(8, i, new QTableWidgetItem(QString("%1").arg(total)));
        pp_residence=residence[i]/total*100;
        pp_bigTrans=bigTrans[i]/total*100;
        pp_litteTrans=littleTrans[i]/total*100;
        pp_food=food[i]/total*100;
        pp_tickets=tickets[i]/total*100;
        pp_shopping=shopping[i]/total*100;
        pp_others=others[i]/total*100;
        series[i]->append("住宿"+QString("%1").arg(pp_residence)+"%",residence[i]);
        series[i]->append("大交通"+QString("%1").arg(pp_bigTrans)+"%",bigTrans[i]);
        series[i]->append("小交通"+QString("%1").arg(pp_litteTrans)+"%",littleTrans[i]);
        series[i]->append("餐饮"+QString("%1").arg(pp_food)+"%",food[i]);
        series[i]->append("门票"+QString("%1").arg(pp_tickets)+"%",tickets[i]);
        series[i]->append("购物"+QString("%1").arg(pp_shopping)+"%",shopping[i]);
        series[i]->append("其他"+QString("%1").arg(pp_others)+"%",others[i]);
        series[i]->setLabelsVisible();
        chart[i]->legend()->setAlignment(Qt::AlignRight);  // 设置图例靠右显示
        chart[i]->addSeries(series[i]);
        chart[i]->setTitle(QString("%1").arg(p1->routeNum)+"消费信息");
        chart[i]->legend()->hide();
        chartview[i]= new QChartView(chart[i]);
        chartview[i]->setRenderHint(QPainter::Antialiasing);
        layout->addWidget(chartview[i],0,i);
        p1->totalPrice=total;
        if(tickets[i]>tickets[index_mostTickets])
        {
            index_mostTickets=i;
        }
        p1=p1->nextRoute;
    }
    p1=hRoute;
    int index_mostAvg=1;
    int index_leastAvg=1;
    float avg[10];
    for(int i=1;i<t1;i++)
    {
        if(p1->totalTime!=0)
        {
               avg[i]=p1->totalPrice/p1->totalTime;
               if(avg[i]>avg[index_mostAvg])
               {
                    index_mostAvg=i;
               }
               if(avg[i]<avg[index_leastAvg])
               {
                    index_leastAvg=i;
               }
        }
        p1=p1->nextRoute;
    }

    tableWidget->setItem(9, 0, new QTableWidgetItem("门票价格最高的是"));
    tableWidget->setItem(9, 1, new QTableWidgetItem(tableWidget->item(0,index_mostTickets)->text()));
    tableWidget->setItem(9, 2, new QTableWidgetItem(QString("%1").arg(tickets[index_mostTickets])+"元"));
    tableWidget->setItem(10, 0, new QTableWidgetItem("日消费价格最高的是"));
    tableWidget->setItem(10, 1, new QTableWidgetItem(tableWidget->item(0,index_mostAvg)->text()));
    tableWidget->setItem(10, 2, new QTableWidgetItem(QString("%1").arg(avg[index_mostAvg])+"元"));
    tableWidget->setItem(10, 0, new QTableWidgetItem("日消费价格最低的是"));
    tableWidget->setItem(10, 1, new QTableWidgetItem(tableWidget->item(0,index_leastAvg)->text()));
    tableWidget->setItem(10, 2, new QTableWidgetItem(QString("%1").arg(avg[index_leastAvg])+"元"));
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(box);
    showDialog->setLayout(mainLayout);
    showDialog->show();
    //进行统计图表输出QThanzi
}

void MainWindow::showTransInfoSlot()
{
    deletedialog = new QDialog;
    deletedialog->setWindowTitle("查询小交通信息");
    QGroupBox *box = new QGroupBox(this);
    QPushButton *submitBtn = new QPushButton("确认");
    QPushButton *cancelBtn = new QPushButton("取消");
    connect(submitBtn, SIGNAL(clicked(bool)), this, SLOT(Act_showTransInfoSlot()));
    connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(cancelBtSlot()));

    QLabel *routNum = new QLabel("景点名称");
    routeNumLineEdit = new QLineEdit;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(routNum, 0, 0, 1, 1); //从哪里开始 跨度
    layout->addWidget(routeNumLineEdit, 0, 1, 1, 1); //从哪里开始 跨度

    layout->addWidget(submitBtn, 1, 0, 1, 1);
    layout->addWidget(cancelBtn, 1, 1, 1, 1);
    box->setLayout(layout);
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(box);
    deletedialog->setLayout(mainLayout);
    deletedialog->show();
}


void MainWindow::Act_showTransInfoSlot()
{
    QMessageBox msgBox;
    char Scene[50];
    strcpy(Scene, routeNumLineEdit->text().toStdString().c_str());
    deletedialog->close();
    p_DayInfo tp2=findTransInfoByScene(Scene);
    if (tp2!=NULL)
    {
        msgBox.setText("小交通信息："+QString::fromUtf8(tp2->transInfo));
        msgBox.exec();
        return;
    }
    else
    {
        msgBox.setText("查找失败");
        msgBox.exec();
        return;
    }
}

void MainWindow::showResidenceSlot()
{
    deletedialog = new QDialog;
    deletedialog->setWindowTitle("查询小交通信息");
    QGroupBox *box = new QGroupBox(this);
    QPushButton *submitBtn = new QPushButton("确认");
    QPushButton *cancelBtn = new QPushButton("取消");
    connect(submitBtn, SIGNAL(clicked(bool)), this, SLOT(Act_showResidenceSlot()));
    connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(cancelBtSlot()));

    QLabel *routNum = new QLabel("景点名称");
    routeNumLineEdit = new QLineEdit;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(routNum, 0, 0, 1, 1); //从哪里开始 跨度
    layout->addWidget(routeNumLineEdit, 0, 1, 1, 1); //从哪里开始 跨度

    layout->addWidget(submitBtn, 1, 0, 1, 1);
    layout->addWidget(cancelBtn, 1, 1, 1, 1);
    box->setLayout(layout);
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(box);
    deletedialog->setLayout(mainLayout);
    deletedialog->show();
}

void MainWindow::Act_showResidenceSlot()
{
    QMessageBox msgBox;
    char Residence[50];
    strcpy(Residence, routeNumLineEdit->text().toStdString().c_str());
    deletedialog->close();
    float EXP=findEXPByResidence(Residence);
    if (EXP!=-1)
    {
        EXP+=1;
        msgBox.setText(QString::fromUtf8(Residence)+"价格："+QString("%1").arg(EXP));
        msgBox.exec();
        return;
    }
    else
    {
        msgBox.setText("无查找旅店");
        msgBox.exec();
        return;
    }
}

void MainWindow::showDressingIndexSlot()
{
    deletedialog = new QDialog;
    deletedialog->setWindowTitle("穿衣指数");
    QGroupBox *box = new QGroupBox(this);
    QPushButton *submitBtn = new QPushButton("确认");
    QPushButton *cancelBtn = new QPushButton("取消");
    connect(submitBtn, SIGNAL(clicked(bool)), this, SLOT(Act_showDressingIndexSlot()));
    connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(cancelBtSlot()));

    QLabel *time1 = new QLabel("时间1");
    QLabel *time2 = new QLabel("时间2");
    routeNumLineEdit = new QLineEdit;
    orderLineEdit= new QLineEdit;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(time1, 0, 0, 1, 1);
    layout->addWidget(routeNumLineEdit, 0, 1, 1, 1);
    layout->addWidget(time2, 1, 0, 1, 1);
    layout->addWidget(orderLineEdit, 1, 1, 1, 1);


    layout->addWidget(submitBtn, 2, 0, 1, 1);
    layout->addWidget(cancelBtn, 2, 1, 1, 1);
    box->setLayout(layout);
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(box);
    deletedialog->setLayout(mainLayout);
    deletedialog->show();
}

void MainWindow::Act_showDressingIndexSlot()
{
    QMessageBox msgBox;
    QDateTime dateTime1 = QDateTime::fromString(routeNumLineEdit->text(), "yyyy-MM-dd");
    QDateTime dateTime2 = QDateTime::fromString(orderLineEdit->text(), "yyyy-MM-dd");
    QDateTime t_time1;
    QDateTime t_time2;
    deletedialog->close();
    p_Route p1 = hRoute;
    if (p1 == NULL)
    {

        msgBox.setText("无符合要求的行程信息");
        msgBox.exec();
        return;
    }
    QString str1;
    QString str2;
    QString printStr;
    p_Route A_p1[10]= {NULL};
    int i=1;
    while (p1 != NULL)
    {
        str1=QString::fromUtf8(p1->beginDate);
        str2=QString::fromUtf8(p1->arriveDate);
        if(str1.isEmpty()||str2.isEmpty())
        {
             p1 = p1->nextRoute;
        }
        t_time1=QDateTime::fromString(str1, "yyyy-MM-dd");
        t_time2=QDateTime::fromString(str2, "yyyy-MM-dd");
        if(dateTime1<=t_time1&&t_time2<=dateTime2&&t_time1<=t_time2)
        {
            //入p3
            A_p1[i++]=p1;
        }

        p1 = p1->nextRoute;
    }
    i=1;
    if(A_p1[1]==NULL)
    {
        msgBox.setText("无符合要求的行程信息");
        msgBox.exec();
        return;
    }
    while(A_p1[i]!=NULL)
    {
        QString qq=QString::fromUtf8(A_p1[i]->dressingIndex.recommendedDressing);
        QString tStr="行程："+QString("%1").arg(A_p1[i]->routeNum)+"\t"+QString::fromUtf8(A_p1[i]->dressingIndex.recommendedDressing)+"\n";
        printStr+=tStr;
        i++;
    }
    msgBox.setText(printStr);
    msgBox.exec();
    return;
}


void MainWindow::sortRouteSlot()
{
    //sortByRouteNum();
    //ListBubbleSort(&hRoute);
    sortRouteByNum(&hRoute);
    showTree();
}

void MainWindow::sortDayInfoSlot()
{
    p_Route p1=hRoute;
    if(p1==NULL)
    {
        return ;
    }
    while(p1!=NULL)
    {
        p_DayInfo p2=p1->hDayInfo;
        sortDayInfoByOrder(&p2);
        p1->hDayInfo=p2;
        p1=p1->nextRoute;
    }
    showTree();
}

void MainWindow::sortDayEXPInfoSlot()
{
    p_Route p1=hRoute;
    if(p1==NULL)
    {
        return ;
    }
    while(p1!=NULL)
    {
        p_DayInfo p2=p1->hDayInfo;
        if(p2!=NULL)
        {
            p_DayEXPInfo p3=p2->hDayEXPInfo;
            sortDayEXPInfoBySerial(&p3);
            p2->hDayEXPInfo=p3;
            p2=p2->nextDayInfo;
        }
        p1=p1->nextRoute;
    }
    showTree();
}



































