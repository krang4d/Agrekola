#include "choisedialog.h"
#include "ui_choisedialog.h"
#include <QDebug>
#include <QThread>
#include "startmeasurement.h"
#include "globalvalue.h"

ChoiseDialog::ChoiseDialog(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::ChoiseDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    CreateWidgetThread();

    agr1 = static_cast<Agr1 *>(ui->stackedWidget->widget(1));
    agr2 = static_cast<Agr2 *>(ui->stackedWidget->widget(2));

    ko1 = static_cast<Ko1 *>(ui->stackedWidget->widget(3));
    ko2 = static_cast<Ko2 *>(ui->stackedWidget->widget(4));
    ko3 = static_cast<Ko3 *>(ui->stackedWidget->widget(5));
    ko4 = static_cast<Ko4 *>(ui->stackedWidget->widget(6));
    ko5 = static_cast<Ko5 *>(ui->stackedWidget->widget(7));

    connect(agr1, SIGNAL(measurement(StartMeasurement*)), SLOT(startMeasurement(StartMeasurement*)));
    connect(agr2, SIGNAL(measurement(StartMeasurement*)), SLOT(startMeasurement(StartMeasurement*)));
    connect(ko1, SIGNAL(measurement(StartMeasurement*)), SLOT(startMeasurement(StartMeasurement*)));
    connect(ko2, SIGNAL(measurement(StartMeasurement*)), SLOT(startMeasurement(StartMeasurement*)));
    connect(ko3, SIGNAL(measurement(StartMeasurement*)), SLOT(startMeasurement(StartMeasurement*)));
    connect(ko4, SIGNAL(measurement(StartMeasurement*)), SLOT(startMeasurement(StartMeasurement*)));
    connect(ko5, SIGNAL(measurement(StartMeasurement*)), SLOT(startMeasurement(StartMeasurement*)));

    connect(agr1, SIGNAL(calibration(StartMeasurement*)), SLOT(calibration(StartMeasurement*)));
    connect(agr2, SIGNAL(calibration(StartMeasurement*)), SLOT(calibration(StartMeasurement*)));
    connect(ko2, SIGNAL(calibration(StartMeasurement*)), SLOT(calibration(StartMeasurement*)));
    connect(ko3, SIGNAL(calibration(StartMeasurement*)), SLOT(calibration(StartMeasurement*)));
    connect(ko5, SIGNAL(calibration(StartMeasurement*)), SLOT(calibration(StartMeasurement*)));
    connect(ko4, SIGNAL(calibration(StartMeasurement*)), SLOT(calibration(StartMeasurement*)));
    qDebug() << "ChoiseDialog thread ID: " << QThread::currentThreadId();
}

int ChoiseDialog::getTypeOfWidget() const
{
    return ui->stackedWidget->currentIndex();
}

void ChoiseDialog::CreateWidgetThread()
{
    agrekola = QSharedPointer<useE154>(new useE154, &ChoiseDialog::deleteLater);
    widget = QSharedPointer<Widget>(new Widget(this), &ChoiseDialog::deleteLater);

    widget->setWindowFlags(Qt::Dialog);

    QWidget::connect(widget.data(), SIGNAL(onmixch1(bool)), agrekola.data(), SLOT(onMixCh1(bool)));
    QWidget::connect(widget.data(), SIGNAL(onmixch2(bool)), agrekola.data(), SLOT(onMixCh2(bool)));
    QWidget::connect(widget.data(), SIGNAL(onmixch3(bool)), agrekola.data(), SLOT(onMixCh3(bool)));
    QWidget::connect(widget.data(), SIGNAL(onmixch4(bool)), agrekola.data(), SLOT(onMixCh4(bool)));
    QWidget::connect(widget.data(), SIGNAL(onmixpp(bool)), agrekola.data(), SLOT(onMixPP(bool)));
    QWidget::connect(widget.data(), SIGNAL(onlaser(bool)), agrekola.data(), SLOT(onLaser(bool)));
    QObject::connect(widget.data(), SIGNAL(stop()), agrekola.data(), SLOT(stopThread()));
    QObject::connect(widget.data(), SIGNAL(stop()), widget.data(), SLOT(deleteLater()));

    QWidget::connect(agrekola.data(), SIGNAL(update_termo(bool)), widget.data(), SLOT(updataTermo(bool)));
    QWidget::connect(agrekola.data(), SIGNAL(value_come(QVariantList)), widget.data(), SLOT(realtimeDataSlot(QVariantList)));
    QWidget::connect(agrekola.data(), SIGNAL(finished()), agrekola.data(), SLOT(deleteLater()));

    QWidget::connect(widget.data(), SIGNAL(destroyed(QObject*)), agrekola.data(), SLOT(deleteLater()));
    agrekola->start();
    //widget->setUserMessage(agrekola->GetInformation());
}

ChoiseDialog::~ChoiseDialog()
{
    delete ui;
    qDebug() << "call ChoiseDialog::~ChoiseDialog()";
    QThread::currentThread()->msleep(300);
}

void ChoiseDialog::on_testButton_clicked()
{
    widget->startWin = new StartMeasurement; //Test
    widget->startWin->setModeID(Test_ID);
    widget->state = StateBuilder::getState(Test_ID);
    widget->show();
    hide();
}

void ChoiseDialog::t_singeShotConntection(QMetaObject::Connection *p, QMetaObject::Connection *t1,
                                          QMetaObject::Connection *t2, QMetaObject::Connection *t3,
                                          QMetaObject::Connection *t4, Ko_impl *ko)
{
    *p = connect(widget.data(), &Widget::end, [=]() {
        widget->setUserMessage(ko->t_print());
        QObject::disconnect(*p);
        delete p;
    });
    *t1 = connect(widget.data(), &Widget::ret_value1, [=](double d){
        ko->setT1(d);
        QObject::disconnect(*t1);
        delete t1;
    });
    *t2 = connect(widget.data(), &Widget::ret_value2, [=](double d){
        ko->setT2(d);
        QObject::disconnect(*t2);
        delete t2;
    });
    *t3 = connect(widget.data(), &Widget::ret_value3, [=](double d){
        ko->setT3(d);
        QObject::disconnect(*t3);
        delete t3;
    });

    *t4 = connect(widget.data(), &Widget::ret_value4, [=](double d){
        ko->setT4(d);
        QObject::disconnect(*t4);
        delete t4;
    });
}

void ChoiseDialog::startMeasurement(StartMeasurement* sw)
{
    Mode_ID mode = sw->getModeID();
    widget->startWin = sw;
    this->hide();
    widget->show();
    //QPointer<MainWindow> mw = new MainWindow(this);
    //widget->centerWidget->single = sw->isSingle();
    QMetaObject::Connection *printConnection = new QMetaObject::Connection;
    QMetaObject::Connection *t1Connection = new QMetaObject::Connection;
    QMetaObject::Connection *t2Connection = new QMetaObject::Connection;
    QMetaObject::Connection *t3Connection = new QMetaObject::Connection;
    QMetaObject::Connection *t4Connection = new QMetaObject::Connection;

    switch (mode) {
    case TestKo1_ID:
        widget->setWindowTitle("Время свертывания, тест");
        widget->setUserMessage("Время свертывания, тест");
        widget->setUserMessage(tr("<div style='color: blue'>Установите в рабочие каналы кюветы с пробами и нажмите \"Старт\""));
        t_singeShotConntection(printConnection, t1Connection, t2Connection, t3Connection, t4Connection, ko1);
        break;
    case TestKo2_ID:
        widget->setWindowTitle("АЧТВ, тест");
        widget->setUserMessage("АЧТВ, тест");
        widget->setUserMessage(tr("<div style='color: blue'>Установите в рабочие каналы кюветы с пробами и нажмите \"Старт\""));
        t_singeShotConntection(printConnection, t1Connection, t2Connection, t3Connection, t4Connection, ko2);
        break;
    case TestKo3_ID:
        widget->setWindowTitle("Фибриноген, тест");
        widget->setUserMessage("Фибриноген, тест)");
        widget->setUserMessage(tr("<div style='color: blue'>Установите в рабочие каналы кюветы с пробами и нажмите \"Старт\""));
        t_singeShotConntection(printConnection, t1Connection, t2Connection, t3Connection, t4Connection, ko3);
        break;
    case TestKo4_ID:
        widget->setWindowTitle("Тромбин, тест");
        widget->setUserMessage("Тромбин, тест");
        widget->setUserMessage(tr("<div style='color: blue'>Установите в рабочие каналы кюветы с пробами и нажмите \"Старт\""));
        t_singeShotConntection(printConnection, t1Connection, t2Connection, t3Connection, t4Connection, ko4);
        break;
    case TestKo5_ID:
        widget->setWindowTitle("Протромбиновый комплекс, тест");
        widget->setUserMessage("Протромбиновый комплекс, тест");
        widget->setUserMessage(tr("<div style='color: blue'>Установите в рабочие каналы кюветы с пробами и нажмите \"Старт\""));
        t_singeShotConntection(printConnection, t1Connection, t2Connection, t3Connection, t4Connection, ko5);
        break;
    case TestAgr1_ID:
        widget->setWindowTitle("<div style='color: blue'>Определение параметров агрегации, тест");
        widget->setUserMessage("<div style='color: blue'>Определение параметров агрегации, тест");

        break;
    case TestAgr2_ID:
        widget->setWindowTitle("Определение активности фактора Виллебранда, тест");
        widget->setUserMessage("Определение активности фактора Виллебранда, тест");
        //centerWidget->setUserMessage(tr("<div style='color: blue'>Установите в рабочие каналы кюветы с пробами и нажмите \"Старт\""));
        break;
    default:
        break;
    }
}

void ChoiseDialog::c_singeShotConntection(QMetaObject::Connection *p, QMetaObject::Connection *t1,
                                          QMetaObject::Connection *t2, QMetaObject::Connection *t3,
                                          QMetaObject::Connection *t4, Ko_impl *ko)
{
    *p = connect(widget.data(), &Widget::end, [=]() {
        widget->setUserMessage(ko->c_print());
        QObject::disconnect(*p);
        delete p;
    });
    *t1 = connect(widget.data(), &Widget::ret_value1, [=](double d){
        ko->calibrationData1Come(d);
        QObject::disconnect(*t1);
        delete t1;
    });
    *t2 = connect(widget.data(), &Widget::ret_value2, [=](double d){
        ko->calibrationData2Come(d);
        QObject::disconnect(*t2);
        delete t2;
    });
    *t3 = connect(widget.data(), &Widget::ret_value3, [=](double d){
        ko->calibrationData3Come(d);
        QObject::disconnect(*t3);
        delete t3;
    });

    *t4 = connect(widget.data(), &Widget::ret_value4, [=](double d){
        ko->calibrationData4Come(d);
        QObject::disconnect(*t4);
        delete t4;
    });
}

void ChoiseDialog::calibration(StartMeasurement* sw)
{
    widget->startWin = sw;
    Mode_ID mode = sw->getModeID();

    QMetaObject::Connection *printConnection = new QMetaObject::Connection;
    QMetaObject::Connection *t1Connection = new QMetaObject::Connection;
    QMetaObject::Connection *t2Connection = new QMetaObject::Connection;
    QMetaObject::Connection *t3Connection = new QMetaObject::Connection;
    QMetaObject::Connection *t4Connection = new QMetaObject::Connection;

    switch (mode) {
    case CalibKo2_ID:
        widget->setWindowTitle("АЧТВ, калибровка (Ko2)");
        widget->setUserMessage("АЧТВ, калибровка (Ko2)", 0);
        widget->setUserMessage(QString("<div style='color: blue'>Установите кюветы с контрольной нормальной плазмой и нажмите \"Старт\""), 0);
        c_singeShotConntection(printConnection, t1Connection, t2Connection, t3Connection, t4Connection, ko2);
//        connect(widget.data(), SIGNAL(ret_value1(double)), ko2, SLOT(calibrationData1Come(double)));
//        connect(widget.data(), SIGNAL(ret_value2(double)), ko2, SLOT(calibrationData2Come(double)));
//        connect(widget.data(), SIGNAL(ret_value3(double)), ko2, SLOT(calibrationData3Come(double)));
//        connect(widget.data(), SIGNAL(ret_value4(double)), ko2, SLOT(calibrationData4Come(double)));
        break;
    case CalibKo3_ID:
        widget->setUserMessage("Фибриноген, калибровка (Ko3)", 0);
        widget->setUserMessage(QString("<div style='color: blue'>Установите кюветы с контрольной нормальной плазмой и ее разведением, после нажмите \"Старт\""), 0);
        widget->setUserMessage(QString("<div style='color: blue'>Первый этап разведения: Канал 1,2 - 200%, Канал 2,3 - 100%\n"
                                       "Второй этап разведения: Канал 1,2 - 50%, Канал 3,4 - 25%"), 0);
        c_singeShotConntection(printConnection, t1Connection, t2Connection, t3Connection, t4Connection, ko3);
//        connect(widget.data(), SIGNAL(ret_value1(double)), ko3, SLOT(calibrationData1Come(double)));
//        connect(widget.data(), SIGNAL(ret_value2(double)), ko3, SLOT(calibrationData2Come(double)));
//        connect(widget.data(), SIGNAL(ret_value3(double)), ko3, SLOT(calibrationData3Come(double)));
//        connect(widget.data(), SIGNAL(ret_value4(double)), ko3, SLOT(calibrationData4Come(double)));
        break;
    case CalibKo4_ID:
        widget->setUserMessage("Тромбин, калибровка (Ko4)", 0);
        widget->setUserMessage(QString("<div style='color: blue'>Установите кюветы с контрольной нормальной плазмой и нажмите \"Старт\""), 0);
        c_singeShotConntection(printConnection, t1Connection, t2Connection, t3Connection, t4Connection, ko4);
//        connect(widget.data(), SIGNAL(ret_value1(double)), ko4, SLOT(calibrationData1Come(double)));
//        connect(widget.data(), SIGNAL(ret_value2(double)), ko4, SLOT(calibrationData2Come(double)));
//        connect(widget.data(), SIGNAL(ret_value3(double)), ko4, SLOT(calibrationData3Come(double)));
//        connect(widget.data(), SIGNAL(ret_value4(double)), ko4, SLOT(calibrationData4Come(double)));
        break;
    case CalibKo5_ID:
        widget->setUserMessage(QString("Протромбиновый комплекс, калибровка (Ko5)"), 0);
        widget->setUserMessage(QString("<div style='color: blue'>Установите кюветы с контрольной нормальной плазмой и ее разведением, после нажмите \"Старт\""), 0);
        widget->setUserMessage(QString("<div style='color: blue'>Разведения: Канал 1 - 100%, Канал 2 - 50%, Канал 3 - 25%, Канал 4 - 12.5%"), 0);
        c_singeShotConntection(printConnection, t1Connection, t2Connection, t3Connection, t4Connection, ko5);
//        connect(widget.data(), SIGNAL(ret_value1(double)), ko5, SLOT(calibrationData1Come(double)));
//        connect(widget.data(), SIGNAL(ret_value2(double)), ko5, SLOT(calibrationData2Come(double)));
//        connect(widget.data(), SIGNAL(ret_value3(double)), ko5, SLOT(calibrationData3Come(double)));
//        connect(widget.data(), SIGNAL(ret_value4(double)), ko5, SLOT(calibrationData4Come(double)));
        break;
    case CalibAgr1_ID:
        widget->setUserMessage(QString("Определение параметров агрегации, калибровка (Agr1 1)"), 0);
        widget->setUserMessage(QString("<div style='color: blue'>Установите кюветы с контрольной нормальной плазмой и нажмите \"Старт\""), 0);
//        connect(widget.data(), SIGNAL(ret_value1(double)), agr1.data(), SLOT(btpData1Come(double)));
//        connect(widget.data(), SIGNAL(ret_value2(double)), agr1.data(), SLOT(btpData2Come(double)));
//        connect(widget.data(), SIGNAL(ret_value3(double)), agr1.data(), SLOT(btpData3Come(double)));
//        connect(widget.data(), SIGNAL(ret_value4(double)), agr1.data(), SLOT(btpData4Come(double)));
        break;
    case CalibAgr2_ID:
        widget->setUserMessage(QString("<div style='color: blue'>Установите кюветы с контрольной нормальной плазмой и ее разведением, после нажмите \"Старт\""), 0);
        widget->setUserMessage(QString("<div style='color: blue'>Разведения: Канал 1 - 200%, Канал 2 - 100%, Канал 3 - 50%, Канал 4 - 25%"), 0);
//        connect(widget.data(), SIGNAL(ret_value1(double)), agr2, SLOT(calibrationData1Come(double)));
//        connect(widget.data(), SIGNAL(ret_value2(double)), agr2, SLOT(calibrationData2Come(double)));
//        connect(widget.data(), SIGNAL(ret_value3(double)), agr2, SLOT(calibrationData3Come(double)));
//        connect(widget.data(), SIGNAL(ret_value4(double)), agr2, SLOT(calibrationData4Come(double)));
        break;
    default:
        break;
    }
    this->hide();
    widget->show();
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
