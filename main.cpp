#include <QApplication>
#include <QString>
#include "mainwindow.h"

#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChoiseDialog *choiseDlg = new ChoiseDialog();
    choiseDlg->show();
    return a.exec();
}
