#include <QApplication>
#include <QDebug>

#include "choisedialog.h"
#include "mainwindow.h"
#include "viewplot.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    qDebug() << "main thread ID: " << QThread::currentThreadId();
//    ChoiseDialog *dlg_menu = new ChoiseDialog;
//    dlg_menu->show();
    ViewPlot *gr = new ViewPlot;
    gr->show();
    gr->addData();
    return a.exec();
}
