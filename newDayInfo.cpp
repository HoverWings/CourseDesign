#include "newDayInfo.h"
#include "ui_newDayInfo.h"
#include"Personaltrip.h"

newDayInfo::newDayInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newDayInfo)
{
    ui->setupUi(this);
    this->setWindowTitle("插入每日信息");
}

newDayInfo::~newDayInfo()
{
    delete ui;
}

void newDayInfo::on_saveDayInfoButton_clicked()
{
    p_DayInfo cur= (p_DayInfo)malloc(sizeof(DayInfo));
    cur->routeNum=ui->lineEdit->text().toInt();//int
    cur->order=ui->lineEdit_2->text().toInt();//int
    strcpy(cur->breakfastLoc, ui->lineEdit_3->text().toStdString().c_str());
    strcpy(cur->morningScene, ui->lineEdit_4->text().toStdString().c_str());
    strcpy(cur->LunchLoc, ui->lineEdit_5->text().toStdString().c_str());
    strcpy(cur->afternoonScene, ui->lineEdit_6->text().toStdString().c_str());
    strcpy(cur->dinnerLoc, ui->lineEdit_7->text().toStdString().c_str());
    strcpy(cur->transInfo, ui->lineEdit_8->text().toStdString().c_str());
    strcpy(cur->residence, ui->lineEdit_9->text().toStdString().c_str());

    //直接赋值

    //此处需加判断是否为空
    QMessageBox msgBox;
    if(insertDayInfo(&cur))
    {
        msgBox.setText("Save Successfully");
        msgBox.exec();
    }
    else
    {
        msgBox.setText("Save fail");
        msgBox.exec();
    }
    //insert(&cur);//插入当前输入的route
    //弹出如果退出


    this->close();
}
