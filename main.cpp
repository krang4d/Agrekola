#include <QApplication>
#include <QDebug>
#include <QThread>
#include "choisedialog.h"
#include "enddialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setlocale(LC_ALL, "Russian");
    qDebug() << "main thread ID: " << QThread::currentThreadId();
    ChoiseDialog *dlg_menu = new ChoiseDialog;
    dlg_menu->show();
//    myDialog::EndDialog *end1 = new myDialog::EndDialog;
//    end1->show();
    return a.exec();
}
