#include "mainwindow.h"
#include"newRoute.h"
#include"Personaltrip.h"
#include <QApplication>
#include<QTextCodec>

int main(int argc, char *argv[])
{
    //此处可执行调试
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
