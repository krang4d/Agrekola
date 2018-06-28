#include "widget.h"
#include <QApplication>
#include <QString>
#include "useE154.h"
#include <QMessageBox>

void setUserMessage(Widget *w, string str)
{
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
        w->setAgrekola(agrecola);
        setUserMessage(w, agrecola->GetVersion());
        setUserMessage(w, agrecola->GetUsbSpeed());
        setUserMessage(w, agrecola->GetInformation());
        setUserMessage(w, agrecola->AdcSynchro());
    }
    catch(Errore_E154 &e){
        w->setText(QString(e.err_msg.c_str()));
        QMessageBox err(QMessageBox::Warning, "Ошибка", QString(e.err_msg.c_str()), QMessageBox::Ok);
        err.exec();
    }
    catch(...){
        w->setText(QString("Неизвестная ошибка"));
    }
    return a.exec();
}
