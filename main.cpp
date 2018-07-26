#include <QApplication>
#include <QDebug>
#include <QStringList>

#include "choisedialog.h"
#include "mainwindow.h"
#include "viewplot.h"
#include "savefiles.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    qDebug() << "main thread ID: " << QThread::currentThreadId();
//    ChoiseDialog *dlg_menu = new ChoiseDialog;
//    dlg_menu->show();
    useE154 first;
    qDebug().noquote() << first.GetInformation();
//    Sleep(1000);
//    useE154 second;
//    qDebug().noquote() << second.GetInformation();
    return a.exec();
}
