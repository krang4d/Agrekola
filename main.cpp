#include "widget.h"
#include <QApplication>
#include <QString>
#include "useE154.h"
#include "mainwindow.h"
#include <QMessageBox>

void setUserMessage(Widget *w, string str){
    w->setText(QString(str.c_str()));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow;
    //Widget *w = new Widget();
    w->show();
    //w->centralWidget()->setText("Module E-154\n");
    //w->setText("Console example for ADC Synchro Stream \n");
    ChoiseDialog *choiseDlg = new ChoiseDialog();
    choiseDlg->show();
    try{
        UseE154 *agrecola = new UseE154();
        //w->setAgrekola(agrecola);
        //setUserMessage(w, agrecola->GetVersion()); //"myGetDllVersion-->ERRORE!\n");
        //setUserMessage(w, agrecola->GetUsbSpeed());
        //setUserMessage(w, agrecola->GetInformation());
        //if(agrecola->GetStatusTD()){
        //    setUserMessage(w, "Прибор вошел в режиме тепловой готовности\r\n");
        //} else setUserMessage(w, "Прибор <style color:red>не вошел</style> в режиме тепловой готовности\r\n");
    }
    catch(Errore_E154 &e){
        //w->setText(QString(e.err_msg.c_str()));
        QMessageBox err(QMessageBox::Warning, "Ошибка", QString(e.err_msg.c_str()), QMessageBox::Ok);
        err.exec();
    }
    return a.exec();
}
