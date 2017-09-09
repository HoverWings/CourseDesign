#ifndef NEWDAYINFO_H
#define NEWDAYINFO_H

#include <QDialog>
#include<QMessageBox>
#include"Personaltrip.h"

namespace Ui {
class newDayInfo;
}

class newDayInfo : public QDialog
{
    Q_OBJECT

public:
    explicit newDayInfo(QWidget *parent = 0);
    ~newDayInfo();

private slots:
    void on_saveDayInfoButton_clicked();

private:
    Ui::newDayInfo *ui;
};

#endif // NEWDAYINFO_H
