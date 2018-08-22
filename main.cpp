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
    qDebug() << "main thread ID: " << QThread::currentThreadId();
    ChoiseDialog *dlg_menu = new ChoiseDialog;
    dlg_menu->show();
    return a.exec();
}
