#include "widget.h"
#include <QApplication>
#include <QString>
#include "useE154.h"

void setUserMessage(Widget *w, string str){
    w->setText(QString(str.c_str()));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget *w = new Widget();
    w->show();
    w->setText("Module E-154\n");
    w->setText("Console example for ADC Synchro Stream \n");
    try{
        useE154 *agrecola = new useE154();
        setUserMessage(w, agrecola->GetVertion()); //"myGetDllVersion-->ERRORE!\n");
        setUserMessage(w, agrecola->GetUsbSpeed());
        setUserMessage(w, agrecola->GetInformation());
        for(int i = 0; i < 100; i++)
            setUserMessage(w, std::to_string(agrecola->AdcSample()) + "\r\n");
    }
    catch(Errore_E154 &e){
        w->setText(QString(e.err_msg.c_str()));
    }
    catch(...){
        w->setText(QString("Неизвестная ошибка"));
    }

//    }
//    else w->setText("myGetDllVersion-->OK\n");

//    if((DllVersion = myGetDllVersion()) != CURRENT_VERSION_LUSBAPI)
//    {
//         w->setText(QString("Lusbapi.dll Version Error!!!\n"));
//    }
//    else w->setText(QString("Lusbapi.dll Version --> OK\n"));
    return a.exec();
}
