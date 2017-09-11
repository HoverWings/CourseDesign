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
    void showAllslot();
    void newRouteSlot();
    void newDayInfoSlot();
    void newDayEXPInfoSlot();
    //void showRouteslot();
    void deleteRouteSlot();//获取所需删除信息
    void Act_deleteRouteSlot();//执行删除操作
    void deleteDayInfoSlot();
    void Act_deleteDayInfoSlot();
    void deleteDayEXPInfoSlot();
    void Act_deleteDayEXPInfoSlot();

    void showRouteslot();
    void Act_showRouteslot();
    void showDayInfoslot();
    void Act_showDayInfoSlot();
    void showDayEXPInfoslot();
    void Act_showDayEXPInfoSlot();

    void saveToFileSlot();
    void loadFromFileSlot();


    void clearSlot();
    void quitBtnSLot();

    void modifyRouteSlot();
    void modifyDayInfoSlot();
    void modifyDayEXPInfoSlot();

    void countEXPSlot();

    void Mouse_position(QTreeWidgetItem* item);
    void Show_info(QTreeWidgetItem* item,int n);






    void on_modifyButton_clicked();

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
