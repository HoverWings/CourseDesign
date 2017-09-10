#ifndef NEWROUTE_H
#define NEWROUTE_H

#include <QDialog>
#include<QMessageBox>
#include<QCloseEvent>
#include<QDialog>
#include"PersonalTrip.h"
#include"mainwindow.h"

namespace Ui
{
    class newRoute;
}

class newRoute : public QDialog
{
    Q_OBJECT

public:
    explicit newRoute(QWidget *parent = 0);
    ~newRoute();

private slots:
    void on_saveRouteButton_clicked();

private:
    Ui::newRoute *ui;
protected:
    //void closeEvent(QCloseEvent *event);
};

#endif // NEWROUTE_H
