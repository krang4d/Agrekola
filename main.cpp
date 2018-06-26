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
    //RealtimeDemo *demo = new RealtimeDemo();
    useE154 *agrecola = new useE154();
    Widget *w = new Widget();
    //QObject::connect(agrecola, SIGNAL(ValueCome(std::list<double>*)), demo, SLOT(getData(std::list<double>*)) );
    //demo->show();
    w->show();
    w->setText("Module E-154\n");
    w->setText("Console example for ADC Synchro Stream \n");
    try{
        //agrecola = new useE154();
        w->setAgrekila(agrecola);
        setUserMessage(w, agrecola->GetVersion());
        setUserMessage(w, agrecola->GetUsbSpeed());
        setUserMessage(w, agrecola->GetInformation());
        setUserMessage(w, agrecola->AdcSynchro());
        if(agrecola->GetStatusTD()){
            setUserMessage(w, "Прибор вышел в режиме тепловой готовности\r\n");
        } else setUserMessage(w, "Прибор <style color:red>не вышел</style> в режиме тепловой готовности\r\n");
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
