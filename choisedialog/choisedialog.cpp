#include "choisedialog.h"
#include "ui_choisedialog.h"
#include <QDebug>
#include <QThread>

ChoiseDialog::ChoiseDialog(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::ChoiseDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    //    Agr1 *agr1; //Определение параметров агрегации
    //    Agr2 *agr2; //Определение активности фактора Виллебранда
    //    Ko1 *ko1;   //Время свертывания
    //    Ko2 *ko2;   //АЧТВ
    //    Ko3 *ko3;   //Фибриноген
    //    Ko4 *ko4;   //Тромбин
    //    Ko5 *ko5;   //Протромбиновый комплекс

    agr1 = static_cast<Agr1 *>(ui->stackedWidget->widget(1));
    agr2 = static_cast<Agr2 *>(ui->stackedWidget->widget(2));

    ko1 = static_cast<Ko1 *>(ui->stackedWidget->widget(3));
    ko2 = static_cast<Ko2 *>(ui->stackedWidget->widget(4));
    ko3 = static_cast<Ko3 *>(ui->stackedWidget->widget(5));
    ko4 = static_cast<Ko4 *>(ui->stackedWidget->widget(6));
    ko5 = static_cast<Ko5 *>(ui->stackedWidget->widget(7));

    connect(agr1, SIGNAL(measurement()), SLOT(startMeasurement()));
    connect(agr2, SIGNAL(measurement()), SLOT(startMeasurement()));
    connect(ko1, SIGNAL(measurement()), SLOT(startMeasurement()));
    connect(ko2, SIGNAL(measurement()), SLOT(startMeasurement()));
    connect(ko3, SIGNAL(measurement()), SLOT(startMeasurement()));
    connect(ko4, SIGNAL(measurement()), SLOT(startMeasurement()));
    connect(ko5, SIGNAL(measurement()), SLOT(startMeasurement()));

    connect(agr1, SIGNAL(calibration()), SLOT(calibration()));
    connect(agr2, SIGNAL(calibration()), SLOT(calibration()));
    connect(ko2, SIGNAL(calibration()), SLOT(calibration()));
    connect(ko3, SIGNAL(calibration()), SLOT(calibration()));
    connect(ko5, SIGNAL(calibration()), SLOT(calibration()));
    connect(ko4, SIGNAL(calibration()), SLOT(calibration()));
    qDebug() << "ChoiseDialog thread ID: " << QThread::currentThreadId();
}

int ChoiseDialog::getTypeOfWidget() const
{
    QString str;
    int i = ui->stackedWidget->currentIndex();
    return i;
}

ChoiseDialog::~ChoiseDialog()
{
    delete ui;
    qDebug() << "call ChoiseDialog::~ChoiseDialog()";
    QThread::currentThread()->msleep(200);

}

void ChoiseDialog::on_testButton_clicked()
{
    QPointer<useE154> agrekola = new useE154;
    QPointer<Widget> widget =new Widget(this);
    widget->setWindowFlags(Qt::Dialog);
    //ChoiseDialog choiseDlg;
    QWidget::connect(widget, SIGNAL(onmixch1(bool)), agrekola, SLOT(onMixCh1(bool)));
    QWidget::connect(widget, SIGNAL(onmixch2(bool)), agrekola, SLOT(onMixCh2(bool)));
    QWidget::connect(widget, SIGNAL(onmixch3(bool)), agrekola, SLOT(onMixCh3(bool)));
    QWidget::connect(widget, SIGNAL(onmixch4(bool)), agrekola, SLOT(onMixCh4(bool)));
    QWidget::connect(widget, SIGNAL(onmixpp(bool)), agrekola, SLOT(onMixPP(bool)));
    QWidget::connect(widget, SIGNAL(onlaser(bool)), agrekola, SLOT(onLaser(bool)));
    QObject::connect(widget, SIGNAL(stop()), agrekola, SLOT(stopThread()));
    //QObject::connect(widget, SIGNAL(stop()), widget, SLOT(deleteLater());

    QWidget::connect(agrekola, SIGNAL(update_termo(bool)), widget, SLOT(updataTermo(bool)));
    QWidget::connect(agrekola, SIGNAL(value_come(QVariantList)), widget, SLOT(realtimeDataSlot(QVariantList)));
    QWidget::connect(agrekola, SIGNAL(finished()), agrekola, SLOT(deleteLater()));
    QWidget::connect(widget, SIGNAL(destroyed(QObject*)), agrekola, SLOT(deleteLater()));

    widget->setMode(0); //Test
    widget->show();
    hide();
    agrekola->start();
    widget->setUserMessage(agrekola->GetInformation());
}

void ChoiseDialog::startMeasurement()
{
    //QMessageBox msg_accept(QMessageBox::Warning, "accept", QString("i =") + QString(std::to_string(i).c_str()), QMessageBox::Ok);
    //msg_accept.exec();
    QPointer<MainWindow> mw = new MainWindow(this);
    mw->newShow();
    hide();
}

void ChoiseDialog::calibration()
{
    int i = ui->stackedWidget->currentIndex();
    QString str;
    switch (i){
    case 1:{
        str = tr("Определение параметров агрегации, калибровка (Agr1 1)");
    }break;
    case 2:{
        str = tr("Определение активности фактора Виллебранда, калибровка (Agr2 2)");
    }break;
    case 3:{
        str = tr("Время свертывания, калибровка (Ko1 3)");
    }break;
    case 4:{
        str = tr("АЧТВ, калибровка (Ko2 4)");     
        QPointer<useE154> agrekola = new useE154;
        QPointer<Widget> widget =new Widget(this);
        widget->setWindowFlags(Qt::Dialog);
        //ChoiseDialog choiseDlg;
        QWidget::connect(widget, SIGNAL(onmixch1(bool)), agrekola, SLOT(onMixCh1(bool)));
        QWidget::connect(widget, SIGNAL(onmixch2(bool)), agrekola, SLOT(onMixCh2(bool)));
        QWidget::connect(widget, SIGNAL(onmixch3(bool)), agrekola, SLOT(onMixCh3(bool)));
        QWidget::connect(widget, SIGNAL(onmixch4(bool)), agrekola, SLOT(onMixCh4(bool)));
        QWidget::connect(widget, SIGNAL(onmixpp(bool)), agrekola, SLOT(onMixPP(bool)));
        QWidget::connect(widget, SIGNAL(onlaser(bool)), agrekola, SLOT(onLaser(bool)));
        QObject::connect(widget, SIGNAL(stop()), agrekola, SLOT(stopThread()));
        //QObject::connect(widget, SIGNAL(stop()), widget, SLOT(deleteLater());

        QWidget::connect(agrekola, SIGNAL(update_termo(bool)), widget, SLOT(updataTermo(bool)));
        QWidget::connect(agrekola, SIGNAL(value_come(QVariantList)), widget, SLOT(realtimeDataSlot(QVariantList)));
        QWidget::connect(agrekola, SIGNAL(finished()), agrekola, SLOT(deleteLater()));
        QWidget::connect(widget, SIGNAL(destroyed(QObject*)), agrekola, SLOT(deleteLater()));

        widget->setMode(Ko1_ID); //
        widget->show();
        hide();
        agrekola->start();
        widget->setUserMessage(str);
        //QMessageBox::information(this, "АЧТВ калибровка", "Установите кювету с контрольной нормальной плазмой и нажмите \"Старт\"");
        widget->setUserMessage(QString("Установите кювету с контрольной нормальной плазмой и нажмите \"Старт\""));
        connect(widget.data(), SIGNAL(ret_value(double)), ko2.data(), SLOT(calibration_data_come(double)));
        //connect(w.data(), SIGNAL(ret_value(double)), w.data(), SLOT(deleteLater()));
//        connect(w.data(), &Widget::destroyed, [=](){
//            disconnect(w.data(), SIGNAL(ret_value(double)), ko2.data(), SLOT(calibration_data_come(double)));
//        });
    }break;
    case 5:{
        str = tr("Фибриноген, калибровка (Ko3 5)");
    }
    case 6:{
        str = tr("Тромбин, калибровка (Ko4 6)");
        QPointer<useE154> agrekola = new useE154;
        QPointer<Widget> widget =new Widget(this);
        widget->setWindowFlags(Qt::Dialog);
        //ChoiseDialog choiseDlg;
        QWidget::connect(widget, SIGNAL(onmixch1(bool)), agrekola, SLOT(onMixCh1(bool)));
        QWidget::connect(widget, SIGNAL(onmixch2(bool)), agrekola, SLOT(onMixCh2(bool)));
        QWidget::connect(widget, SIGNAL(onmixch3(bool)), agrekola, SLOT(onMixCh3(bool)));
        QWidget::connect(widget, SIGNAL(onmixch4(bool)), agrekola, SLOT(onMixCh4(bool)));
        QWidget::connect(widget, SIGNAL(onmixpp(bool)), agrekola, SLOT(onMixPP(bool)));
        QWidget::connect(widget, SIGNAL(onlaser(bool)), agrekola, SLOT(onLaser(bool)));
        QObject::connect(widget, SIGNAL(stop()), agrekola, SLOT(stopThread()));
        //QObject::connect(widget, SIGNAL(stop()), widget, SLOT(deleteLater());

        QWidget::connect(agrekola, SIGNAL(update_termo(bool)), widget, SLOT(updataTermo(bool)));
        QWidget::connect(agrekola, SIGNAL(value_come(QVariantList)), widget, SLOT(realtimeDataSlot(QVariantList)));
        QWidget::connect(agrekola, SIGNAL(finished()), agrekola, SLOT(deleteLater()));
        QWidget::connect(widget, SIGNAL(destroyed(QObject*)), agrekola, SLOT(deleteLater()));

        widget->setMode(Ko1_ID); //
        widget->show();
        hide();
        agrekola->start();
        widget->setUserMessage(str);
        //QMessageBox::information(this, "АЧТВ калибровка", "Установите кювету с контрольной нормальной плазмой и нажмите \"Старт\"");
        widget->setUserMessage(QString("Установите кювету с контрольной нормальной плазмой и нажмите \"Старт\""));
        connect(widget.data(), SIGNAL(ret_value(double)), ko4.data(), SLOT(calibration_data_come(double)));
        //connect(w.data(), SIGNAL(ret_value(double)), w.data(), SLOT(deleteLater()));
//        connect(w.data(), &Widget::destroyed, [=](){
//            disconnect(w.data(), SIGNAL(ret_value(double)), ko2.data(), SLOT(calibration_data_come(double)));
//        });
    }break;
    case 7:{
        str = tr("Протромбиновый комплекс, калибровка (Ko5 7)");
    }break;
    default:
        break;
    }
    //QMessageBox::warning(this, "calibration", QString("calibration #%1").arg(i), QMessageBox::Ok);
    //if(i == 2) kalibragr2->show();
}

void ChoiseDialog::on_agr1Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void ChoiseDialog::on_agr2Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void ChoiseDialog::on_ko1Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void ChoiseDialog::on_ko2Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void ChoiseDialog::on_ko3Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void ChoiseDialog::on_ko4Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void ChoiseDialog::on_ko5Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void ChoiseDialog::on_viewPlotsButton_clicked()
{
    QPointer<ViewPlot> vp = new ViewPlot(this);
    vp->show();
}
