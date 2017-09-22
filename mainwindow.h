#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include<QGroupBox>
#include<QTreeWidget>
#include<QTreeWidgetItem>
#include<QLabel>
#include<QDebug>
#include<QDialog>
#include<QLineEdit>
#include<QGridLayout>
#include<QPushButton>
#include<QDebug>
#include<string>
#include<QDateTime>
#include"newRoute.h"
#include"newDayInfo.h"
#include"newDayEXPInfo.h"
#include"personaltrip.h"

#include <QtWidgets>
#include <QtCharts>//use this to draw pie pict
#include <QPieSeries>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    //p_Route hRoute;//
    ~MainWindow();


    void showTree();

private slots:
    //展示所有信息
    void showAllslot();
    //插入节点
    void newRouteSlot();
    void newDayInfoSlot();
    void newDayEXPInfoSlot();

    //获取所需删除信息
    //Act表示执行删除操作
    void deleteRouteSlot();
    void Act_deleteRouteSlot();
    void deleteDayInfoSlot();
    void Act_deleteDayInfoSlot();
    void deleteDayEXPInfoSlot();
    void Act_deleteDayEXPInfoSlot();

    //查询操作
    //其中Act表示执行显示查询结果
    void showRouteslot();
    void Act_showRouteslot();
    void showDayInfoslot();
    void Act_showDayInfoSlot();
    void showDayEXPInfoslot();
    void Act_showDayEXPInfoSlot();

    //文件操作
    void saveToFileSlot();
    void loadFromFileSlot();
    //退出窗口操作
    void quitBtnSLot();
    //统计报表
    void countEXPSlot();

    void Mouse_position(QTreeWidgetItem* item);//获取当前鼠标所在的链表级别及具体节点顺序
    void Show_info(QTreeWidgetItem* item,int n);//显示当前鼠标所在节点的信息

    void showTransInfoSlot();//查询小交通信息
    void Act_showTransInfoSlot();

    void showResidenceSlot();//查询住宿信息
    void Act_showResidenceSlot();

    void showDressingIndexSlot();//查询着装信息
    void Act_showDressingIndexSlot();

    //排序操作
    void sortRouteSlot();
    void sortDayInfoSlot();
    void sortDayEXPInfoSlot();

    void on_modifyButton_clicked();//执行修改操作

private:
    Ui::MainWindow *ui;
    int now_index[3];//now_index to record the mouse position
    QDialog *newDialog;
    QDialog *deletedialog;
    QDialog *showDialog;
    QLineEdit *routeNumLineEdit;//不同槽之间需要调用
    QLineEdit *orderLineEdit;//不同槽之间需要调用
    QLineEdit *serialNumLineEdit;//不同槽之间需要调用

};

#endif // MAINWINDOW_H
