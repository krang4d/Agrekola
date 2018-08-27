#include <QApplication>
#include <QDebug>
#include <QThread>
#include "choisedialog.h"
#include "calculatedata.h"
#include "savefiles.h"
#include "QMap"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QMap<double, double> map;
//    SaveFiles file;
//    file.openDataMap(map);

//    CalcData *p = CalcData::createCalc(Ko1_ID);
//    p->calc(map);
    qDebug() << "main thread ID: " << QThread::currentThreadId();
    ChoiseDialog *dlg_menu = new ChoiseDialog;
    dlg_menu->show();

    return a.exec();
}
