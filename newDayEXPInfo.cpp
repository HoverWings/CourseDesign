#include "newDayEXPInfo.h"
#include "ui_newDayEXPInfo.h"

newDayEXPInfo::newDayEXPInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newDayEXPInfo)
{
    ui->setupUi(this);
    this->setWindowTitle("插入消费信息");
}

newDayEXPInfo::~newDayEXPInfo()
{
    delete ui;
}
//在插入的时候加

void newDayEXPInfo::on_saveDayEXPInfoButton_clicked()
{
    //字符串赋值
    p_DayEXPInfo cur= (p_DayEXPInfo)malloc(sizeof(DayEXPInfo));
    cur->routeNum=ui->lineEdit->text().toInt();//int
    cur->order=ui->lineEdit_2->text().toInt();//int
    int order=cur->order;
    cur->serialNum=ui->lineEdit_3->text().toInt();//int
    strcpy(cur->TxTime, ui->lineEdit_4->text().toStdString().c_str());
    strcpy(cur->TxKind, ui->lineEdit_5->text().toStdString().c_str());
    cur->TxAmount=ui->lineEdit_6->text().toFloat();//float
    strcpy(cur->isPrepayment, ui->lineEdit_7->text().toStdString().c_str());
    strcpy(cur->payment, ui->lineEdit_8->text().toStdString().c_str());
    strcpy(cur->explain, ui->lineEdit_9->text().toStdString().c_str());
    QMessageBox msgBox;
    p_Route p1=findRouteByNum(cur->routeNum);
    if(p1==NULL)
    {
        msgBox.setText("routeNum error");
        msgBox.exec();
        this->close();
    }
    int routeNum=cur->routeNum;
    p_DayInfo p2=findDayInfoByOrder(routeNum,order);
    if(p2==NULL)
    {
        msgBox.setText("order error");
        msgBox.exec();
        this->close();
    }
    if(insertDayEXPInfo(&p1,&p2,&cur))
    {
        msgBox.setText("Success");
        msgBox.exec();
        this->close();
    }
    else
    {
        msgBox.setText("fail");
        msgBox.exec();
        this->close();
    }
}
