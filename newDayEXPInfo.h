#ifndef NEWDAYEXPINFO_H
#define NEWDAYEXPINFO_H

#include <QDialog>
#include<QMessageBox>
#include"mainwindow.h"
#include"Personaltrip.h"

namespace Ui {
class newDayEXPInfo;
}

class newDayEXPInfo : public QDialog
{
    Q_OBJECT

public:
    explicit newDayEXPInfo(QWidget *parent = 0);
    ~newDayEXPInfo();

private slots:
    void on_saveDayEXPInfoButton_clicked();

private:
    Ui::newDayEXPInfo *ui;
};

#endif // NEWDAYEXPINFO_H
