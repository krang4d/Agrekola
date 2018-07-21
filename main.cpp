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
//    SaveFiles *file = new SaveFiles;
//    QStringList param;
//  param << "4" << "5" << "6";
//    file->openAgr1(param);
//    file.openAgr1(param);
//    foreach (QString str, param) {
//        qDebug() << str;
//    }
    // << param.at(1) << param.at(3);
    qDebug() << "main thread ID: " << QThread::currentThreadId();
    ChoiseDialog *dlg_menu = new ChoiseDialog;
    dlg_menu->show();
//    ViewPlot *gr = new ViewPlot;
//    gr->show();
//    gr->addData();

    return a.exec();
}
