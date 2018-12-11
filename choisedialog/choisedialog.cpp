#include "choisedialog.h"
#include "ui_choisedialog.h"
#include <QDebug>
#include <QThread>
#include "startmeasurment.h"
#include "globalvalue.h"

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

    connect(agr1, SIGNAL(measurement(StartMeasurment*)), SLOT(startMeasurement(StartMeasurment*)));
    connect(agr2, SIGNAL(measurement(StartMeasurment*)), SLOT(startMeasurement(StartMeasurment*)));
    connect(ko1, SIGNAL(measurement(StartMeasurment*)), SLOT(startMeasurement(StartMeasurment*)));
    connect(ko2, SIGNAL(measurement(StartMeasurment*)), SLOT(startMeasurement(StartMeasurment*)));
    connect(ko3, SIGNAL(measurement(StartMeasurment*)), SLOT(startMeasurement(StartMeasurment*)));
    connect(ko4, SIGNAL(measurement(StartMeasurment*)), SLOT(startMeasurement(StartMeasurment*)));
    connect(ko5, SIGNAL(measurement(StartMeasurment*)), SLOT(startMeasurement(StartMeasurment*)));

    connect(agr1, SIGNAL(calibration(StartMeasurment*)), SLOT(calibration(StartMeasurment*)));
    connect(agr2, SIGNAL(calibration(StartMeasurment*)), SLOT(calibration(StartMeasurment*)));
    connect(ko2, SIGNAL(calibration(StartMeasurment*)), SLOT(calibration(StartMeasurment*)));
    connect(ko3, SIGNAL(calibration(StartMeasurment*)), SLOT(calibration(StartMeasurment*)));
    connect(ko5, SIGNAL(calibration(StartMeasurment*)), SLOT(calibration(StartMeasurment*)));
    connect(ko4, SIGNAL(calibration(StartMeasurment*)), SLOT(calibration(StartMeasurment*)));
    qDebug() << "ChoiseDialog thread ID: " << QThread::currentThreadId();
}

int ChoiseDialog::getTypeOfWidget() const
{
    return ui->stackedWidget->currentIndex();
}

QPointer<Widget> ChoiseDialog::CreateWidgetThread(StartMeasurment *sm)
{
    QPointer<useE154> agrekola = new useE154;
    QPointer<Widget> widget;
    if(sm != 0)
        widget = QPointer<Widget>(new Widget(sm, this));
    else widget = QPointer<Widget>(new Widget(this));

    widget->setWindowFlags(Qt::Dialog);

    QWidget::connect(widget, SIGNAL(onmixch1(bool)), agrekola, SLOT(onMixCh1(bool)));
    QWidget::connect(widget, SIGNAL(onmixch2(bool)), agrekola, SLOT(onMixCh2(bool)));
    QWidget::connect(widget, SIGNAL(onmixch3(bool)), agrekola, SLOT(onMixCh3(bool)));
    QWidget::connect(widget, SIGNAL(onmixch4(bool)), agrekola, SLOT(onMixCh4(bool)));
    QWidget::connect(widget, SIGNAL(onmixpp(bool)), agrekola, SLOT(onMixPP(bool)));
    QWidget::connect(widget, SIGNAL(onlaser(bool)), agrekola, SLOT(onLaser(bool)));
    QObject::connect(widget, SIGNAL(stop()), agrekola, SLOT(stopThread()));
    QObject::connect(widget, SIGNAL(stop()), widget, SLOT(deleteLater()));

    QWidget::connect(agrekola, SIGNAL(update_termo(bool)), widget, SLOT(updataTermo(bool)));
    QWidget::connect(agrekola, SIGNAL(value_come(QVariantList)), widget, SLOT(realtimeDataSlot(QVariantList)));
    QWidget::connect(agrekola, SIGNAL(finished()), agrekola, SLOT(deleteLater()));
    QWidget::connect(widget, SIGNAL(destroyed(QObject*)), agrekola, SLOT(deleteLater()));
    agrekola->start();
    //widget->setUserMessage(agrekola->GetInformation());
    return widget;
}

ChoiseDialog::~ChoiseDialog()
{
    delete ui;
    qDebug() << "call ChoiseDialog::~ChoiseDialog()";
    QThread::currentThread()->msleep(300);
}

void ChoiseDialog::on_testButton_clicked()
{
    QPointer<Widget> widget = CreateWidgetThread();
    widget->setMode(Test_ID); //Test
    widget->show();
    hide();
}

void ChoiseDialog::startMeasurement(StartMeasurment* sw)
{
    QPointer<MainWindow> mw = new MainWindow(this);
    mw->newShow(sw);
    hide();
}

void ChoiseDialog::calibration(StartMeasurment* sw)
{
    int i = ui->stackedWidget->currentIndex();
    QPointer<Widget> widget= CreateWidgetThread(sw);

    widget->show();
    hide();

    switch (i){
    case 1:{
        widget->setMode(TestAgr1_ID);
        widget->setUserMessage(QString("Определение параметров агрегации, калибровка (Agr1 1)"), 0);
        widget->setUserMessage(QString("<div style='color: blue'>Установите кюветы с контрольной нормальной плазмой и нажмите \"Старт\""), 0);
        connect(widget.data(), SIGNAL(ret_value1(double)), agr1.data(), SLOT(calibrationData1Come(double)));
        connect(widget.data(), SIGNAL(ret_value2(double)), agr1.data(), SLOT(calibrationData2Come(double)));
        connect(widget.data(), SIGNAL(ret_value3(double)), agr1.data(), SLOT(calibrationData3Come(double)));
        connect(widget.data(), SIGNAL(ret_value4(double)), agr1.data(), SLOT(calibrationData4Come(double)));
    }break;
    case 2:{
        widget->setMode(TestAgr1_ID);
        widget->setUserMessage(QString("<div style='color: blue'>Установите кюветы с контрольной нормальной плазмой и ее разведением, после нажмите \"Старт\""), 0);
        widget->setUserMessage(QString("<div style='color: blue'>Разведения: Канал 1 - 200%, Канал 2 - 100%, Канал 3 - 50%, Канал 4 - 25%"), 0);
        connect(widget.data(), SIGNAL(ret_value1(double)), agr2.data(), SLOT(calibrationData1Come(double)));
        connect(widget.data(), SIGNAL(ret_value2(double)), agr2.data(), SLOT(calibrationData2Come(double)));
        connect(widget.data(), SIGNAL(ret_value3(double)), agr2.data(), SLOT(calibrationData3Come(double)));
        connect(widget.data(), SIGNAL(ret_value4(double)), agr2.data(), SLOT(calibrationData4Come(double)));
    }break;
    case 4:{
        widget->setMode(TestKo1_ID);
        widget->setUserMessage("АЧТВ, калибровка (Ko2 4)", 0);
        widget->setUserMessage(QString("<div style='color: blue'>Установите кюветы с контрольной нормальной плазмой и нажмите \"Старт\""), 0);
        connect(widget.data(), SIGNAL(ret_value1(double)), ko2.data(), SLOT(calibrationData1Come(double)));
        connect(widget.data(), SIGNAL(ret_value2(double)), ko2.data(), SLOT(calibrationData2Come(double)));
        connect(widget.data(), SIGNAL(ret_value3(double)), ko2.data(), SLOT(calibrationData3Come(double)));
        connect(widget.data(), SIGNAL(ret_value4(double)), ko2.data(), SLOT(calibrationData4Come(double)));
    }break;
    case 5:{
        widget->setMode(TestKo1_ID);
        widget->setUserMessage("Фибриноген, калибровка (Ko3 5)", 0);
        widget->setUserMessage(QString("<div style='color: blue'>Установите кюветы с контрольной нормальной плазмой и ее разведением, после нажмите \"Старт\""), 0);
        widget->setUserMessage(QString("<div style='color: blue'>Разведения: Канал 1 - 200%, Канал 2 - 100%, Канал 3 - 50%, Канал 4 - 25%"), 0);
        connect(widget.data(), SIGNAL(ret_value1(double)), ko3.data(), SLOT(calibrationData1Come(double)));
        connect(widget.data(), SIGNAL(ret_value2(double)), ko3.data(), SLOT(calibrationData2Come(double)));
        connect(widget.data(), SIGNAL(ret_value3(double)), ko3.data(), SLOT(calibrationData3Come(double)));
        connect(widget.data(), SIGNAL(ret_value4(double)), ko3.data(), SLOT(calibrationData4Come(double)));
    }break;
    case 6:{
        widget->setMode(TestKo1_ID);
        widget->setUserMessage("Тромбин, калибровка (Ko4 6)", 0);
        widget->setUserMessage(QString("<div style='color: blue'>Установите кюветы с контрольной нормальной плазмой и нажмите \"Старт\""), 0);
        connect(widget.data(), SIGNAL(ret_value1(double)), ko4.data(), SLOT(calibrationData1Come(double)));
        connect(widget.data(), SIGNAL(ret_value2(double)), ko4.data(), SLOT(calibrationData2Come(double)));
        connect(widget.data(), SIGNAL(ret_value3(double)), ko4.data(), SLOT(calibrationData3Come(double)));
        connect(widget.data(), SIGNAL(ret_value4(double)), ko4.data(), SLOT(calibrationData4Come(double)));
    }break;
    case 7:{
        widget->setMode(TestKo1_ID);
        widget->setUserMessage(QString("Протромбиновый комплекс, калибровка (Ko5 7)"), 0);
        widget->setUserMessage(QString("<div style='color: blue'>Установите кюветы с контрольной нормальной плазмой и ее разведением, после нажмите \"Старт\""), 0);
        widget->setUserMessage(QString("<div style='color: blue'>Разведения: Канал 1 - 100%, Канал 2 - 50%, Канал 3 - 25%, Канал 4 - 12.5%"), 0);
        connect(widget.data(), SIGNAL(ret_value1(double)), ko5.data(), SLOT(calibrationData1Come(double)));
        connect(widget.data(), SIGNAL(ret_value2(double)), ko5.data(), SLOT(calibrationData2Come(double)));
        connect(widget.data(), SIGNAL(ret_value3(double)), ko5.data(), SLOT(calibrationData3Come(double)));
        connect(widget.data(), SIGNAL(ret_value4(double)), ko5.data(), SLOT(calibrationData4Come(double)));
    }break;
    default:
        break;
    }
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

void ChoiseDialog::on_exitButton_clicked()
{

    accept();
}
