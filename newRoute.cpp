#include "newRoute.h"
#include "ui_newRoute.h"
#include"mainwindow.h"


newRoute::newRoute(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newRoute)
{
    ui->setupUi(this);
}

newRoute::~newRoute()
{
    delete ui;
}

void newRoute::on_saveRouteButton_clicked()
{
    p_Route cur = (p_Route)malloc(sizeof(Route));
    //字符串赋值
    cur->routeNum=ui->lineEdit->text().toInt();//int
    strcpy(cur->routeName, ui->lineEdit_2->text().toStdString().c_str());
    strcpy(cur->routeCountry, ui->lineEdit_3->text().toStdString().c_str());
    cur->dressingIndex.minT=ui->lineEdit_4->text().toInt();
    cur->dressingIndex.maxT=ui->lineEdit_5->text().toInt();
    strcpy(cur->dressingIndex.recommendedDressing, ui->lineEdit_6->text().toStdString().c_str());
    strcpy(cur->bigTrans, ui->lineEdit_7->text().toStdString().c_str());
    strcpy(cur->mainScene, ui->lineEdit_8->text().toStdString().c_str());
    strcpy(cur->remoteNum, ui->lineEdit_9->text().toStdString().c_str());
    strcpy(cur->beginDate, ui->lineEdit_10->text().toStdString().c_str());
    strcpy(cur->arriveDate, ui->lineEdit_11->text().toStdString().c_str());
    cur->totalTime=ui->lineEdit_12->text().toInt();//int  这个也是输入的
    cur->totalNum=ui->lineEdit_13->text().toInt();//int
    cur->totalPrice=ui->lineEdit_14->text().toFloat();//float
    //此处需加判断是否为空
    QMessageBox msgBox;
    if(insertRoute(&cur))
    {
        msgBox.setText("Save Successfully");
        msgBox.exec();
    }
    else
    {
        msgBox.setText("Save Fail!!!");
        msgBox.exec();
    }

    //插入当前输入的route
    //MainWindow().showTree();
    //弹出如果退出


    this->close();

}

