#include "widget.h"
#include <QApplication>
#include <QString>
#include "useE154.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget *w = new Widget();
    w->show();
    w->setText("Module E-154\n");
    w->setText("Console example for ADC Synchro Stream \n");
    useE154 *agrecola = new useE154();
    w->setText(QString(agrecola->GetVertion().c_str())); //"myGetDllVersion-->ERRORE!\n");

//    }
//    else w->setText("myGetDllVersion-->OK\n");

//    if((DllVersion = myGetDllVersion()) != CURRENT_VERSION_LUSBAPI)
//    {
//         w->setText(QString("Lusbapi.dll Version Error!!!\n"));
//    }
//    else w->setText(QString("Lusbapi.dll Version --> OK\n"));
    return a.exec();
}
