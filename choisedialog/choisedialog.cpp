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

    agr1 = static_cast<Agr1 *>(ui->stackedWidget->widget(1));
    agr2 = static_cast<Agr2 *>(ui->stackedWidget->widget(2));

    ko1 = static_cast<Ko1 *>(ui->stackedWidget->widget(3));
    ko2 = static_cast<Ko2 *>(ui->stackedWidget->widget(4));
    ko3 = static_cast<Ko3 *>(ui->stackedWidget->widget(5));
    ko4 = static_cast<Ko4 *>(ui->stackedWidget->widget(6));
    ko5 = static_cast<Ko5 *>(ui->stackedWidget->widget(7));

    //create end dialog
    end_dialog = new QMessageBox(this);
    //test_dialog->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    QPushButton *ok = new QPushButton;
    QPushButton *cansel = new QPushButton;
    ok->setText("Распечатать");
    cansel->setText("Продолжить");
    end_dialog->addButton(ok, QMessageBox::AcceptRole);
    end_dialog->addButton(cansel, QMessageBox::RejectRole);
    end_dialog->setIcon(QMessageBox::Information);

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

void ChoiseDialog::CreateWidgetThread(StartMeasurement *sm)
{
    agrekola = new useE154(this);
    widget = new Widget(sm);

    QWidget::connect(widget, SIGNAL(onmixch1(bool)), agrekola, SLOT(onMixCh1(bool)));
    QWidget::connect(widget, SIGNAL(onmixch2(bool)), agrekola, SLOT(onMixCh2(bool)));
    QWidget::connect(widget, SIGNAL(onmixch3(bool)), agrekola, SLOT(onMixCh3(bool)));
    QWidget::connect(widget, SIGNAL(onmixch4(bool)), agrekola, SLOT(onMixCh4(bool)));
    QWidget::connect(widget, SIGNAL(onmixpp(bool)), agrekola, SLOT(onMixPP(bool)));
    QWidget::connect(widget, SIGNAL(onlaser(bool)), agrekola, SLOT(onLaser(bool)));
    QObject::connect(widget, SIGNAL(stop()), agrekola, SLOT(stopThread()));
    QObject::connect(widget, SIGNAL(stop()), widget, SLOT(deleteLater()));
    QObject::connect(widget, &Widget::stop, [=](){ show(); });

    QWidget::connect(agrekola, SIGNAL(update_termo(bool)), widget, SLOT(updataTermo(bool)));
    QWidget::connect(agrekola, SIGNAL(value_come(QVariantList)), widget, SLOT(realtimeDataSlot(QVariantList)));
    QWidget::connect(agrekola, SIGNAL(finished()), agrekola, SLOT(deleteLater()));

    QWidget::connect(widget, SIGNAL(destroyed(QObject*)), agrekola, SLOT(deleteLater()));


    widget->setWindowFlags(Qt::Dialog);
    agrekola->start();
    widget->show();
}

void ChoiseDialog::DeleteWidgetThread()
{
    agrekola->stopThread();
    widget->deleteLater();
    //if(widget) delete widget;
}

ChoiseDialog::~ChoiseDialog()
{
    delete ui;
    qDebug() << "call ChoiseDialog::~ChoiseDialog()";
    delete end_dialog;
    QThread::currentThread()->msleep(300);
}

void ChoiseDialog::on_testButton_clicked()
{
    CreateWidgetThread(new StartMeasurement(new TestKo1, new CalibrationKo1));
    this->hide();
    widget->show();
    widget->test();
}

void ChoiseDialog::t_singeShotConntection(MetaObj *p, MetaObj *t1, MetaObj *t2, MetaObj *t3, MetaObj *t4, Ko_impl *ko)
{
    *p = connect(widget, &Widget::end, [=]() {
        //widget->setUserMessage(ko->t_print());
        QObject::disconnect(*p);
        delete p;
        qDebug() << "Slot End";
        ko->setDate(QDate::currentDate(), Ko_impl::Test_ID);
        ko->setTime(QTime::currentTime(), Ko_impl::Test_ID);
        end_dialog->setText(ko->t_print());
        if( end_dialog->exec() == QDialog::Rejected ) {
            //createe print dialog

            QPrinter printer;
            QPointer<QPrintDialog> printDialog = QPointer<QPrintDialog>(new QPrintDialog(&printer));
            printDialog->setWindowTitle("Распечатка результата исследования");
            if (printDialog->exec() == QDialog::Accepted) {
                // print ...
                QPainter painter;
                painter.begin(&printer);
                painter.drawText(100, 100, 500, 500, Qt::AlignLeft|Qt::AlignTop, ko->t_print());
                painter.end();
            }
        }
        //DeleteWidgetThread();
        this->show();
    });
    *t1 = connect(widget, &Widget::ret_value1, [=](double d){
        ko->setT1(d);
        QObject::disconnect(*t1);
        delete t1;
    });
    *t2 = connect(widget, &Widget::ret_value2, [=](double d){
        ko->setT2(d);
        QObject::disconnect(*t2);
        delete t2;
    });
    *t3 = connect(widget, &Widget::ret_value3, [=](double d){
        ko->setT3(d);
        QObject::disconnect(*t3);
        delete t3;
    });

    *t4 = connect(widget, &Widget::ret_value4, [=](double d){
        ko->setT4(d);
        QObject::disconnect(*t4);
        delete t4;
    });
}

void ChoiseDialog::c_singeShotConntection(MetaObj *p, MetaObj *t1, MetaObj *t2, MetaObj *t3, MetaObj *t4, Ko_impl *ko)
{
    *p = connect(widget, &Widget::end, [=]() {
        //widget->setUserMessage(ko->c_print());
        QObject::disconnect(*p);
        delete p;
        qDebug() << "Slot End";
        ko->setDate(QDate::currentDate(), Ko_impl::Calib_ID);
        ko->setTime(QTime::currentTime(), Ko_impl::Calib_ID);
        end_dialog->setText(ko->c_print());
        end_dialog->show();
        DeleteWidgetThread();
        this->show();
    });
    *t1 = connect(widget, &Widget::ret_value1, [=](double d){
        ko->calibrationData1Come(d);
        QObject::disconnect(*t1);
        delete t1;
    });
    *t2 = connect(widget, &Widget::ret_value2, [=](double d){
        ko->calibrationData2Come(d);
        QObject::disconnect(*t2);
        delete t2;
    });
    *t3 = connect(widget, &Widget::ret_value3, [=](double d){
        ko->calibrationData3Come(d);
        QObject::disconnect(*t3);
        delete t3;
    });

    *t4 = connect(widget, &Widget::ret_value4, [=](double d){
        ko->calibrationData4Come(d);
        QObject::disconnect(*t4);
        delete t4;
    });
}

void ChoiseDialog::btp_singeShotConntection(MetaObj *btp1, MetaObj *btp2, MetaObj *btp3, MetaObj *btp4, Agr_impl *agr)
{
    *btp1 = connect(widget, &Widget::btp_value1, [=](double value){
        agr->btp1Come(value);
        QObject::disconnect(*btp1);
        delete btp1;
    });
    *btp2 = connect(widget, &Widget::btp_value2, [=](double value){
        agr->btp2Come(value);
        QObject::disconnect(*btp2);
        delete btp2;
    });
    *btp3 = connect(widget, &Widget::btp_value3, [=](double value){
        agr->btp3Come(value);
        QObject::disconnect(*btp3);
        delete btp3;
    });

    *btp4 = connect(widget, &Widget::btp_value4, [=](double value){
        agr->btp4Come(value);
        QObject::disconnect(*btp4);
        delete btp4;
    });
}

void ChoiseDialog::otp_singeShotConntection(MetaObj *otp1, MetaObj *otp2, MetaObj *otp3, MetaObj *otp4, Agr_impl *agr)
{
    *otp1 = connect(widget, &Widget::ret_value1, [=](double value){
        agr->otp1Come(value);
        QObject::disconnect(*otp1);
        delete otp1;
    });
    *otp2 = connect(widget, &Widget::ret_value2, [=](double value){
        agr->otp2Come(value);
        QObject::disconnect(*otp2);
        delete otp2;
    });
    *otp3 = connect(widget, &Widget::ret_value3, [=](double value){
        agr->otp3Come(value);
        QObject::disconnect(*otp3);
        delete otp3;
    });

    *otp4 = connect(widget, &Widget::ret_value4, [=](double value){
        agr->otp4Come(value);
        QObject::disconnect(*otp4);
        delete otp4;
    });
}

void ChoiseDialog::startMeasurement(StartMeasurement* sm)
{
    this->hide();
    CreateWidgetThread(sm);
    //QPointer<MainWindow> mw = new MainWindow(this);
    //widget->centerWidget->single = sw->isSingle();
    MetaObj *printConnection = new MetaObj;
    MetaObj *t1Connection = new MetaObj;
    MetaObj *t2Connection = new MetaObj;
    MetaObj *t3Connection = new MetaObj;
    MetaObj *t4Connection = new MetaObj;

    MetaObj *otp1Connection;
    MetaObj *otp2Connection;
    MetaObj *otp3Connection;
    MetaObj *otp4Connection;

    MetaObj *btp1Connection;
    MetaObj *btp2Connection;
    MetaObj *btp3Connection;
    MetaObj *btp4Connection;

    Mode_ID mode = sm->getModeID();
    if ( mode == TestAgr1_ID || mode == TestAgr2_ID) {
        otp1Connection = new MetaObj;
        otp2Connection = new MetaObj;
        otp3Connection = new MetaObj;
        otp4Connection = new MetaObj;

        btp1Connection = new MetaObj;
        btp2Connection = new MetaObj;
        btp3Connection = new MetaObj;
        btp4Connection = new MetaObj;
    }

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
        t_singeShotConntection(printConnection, t1Connection, t2Connection, t3Connection, t4Connection, agr1);
        btp_singeShotConntection( btp1Connection, btp2Connection, btp3Connection, btp4Connection, agr1);
        otp_singeShotConntection( otp1Connection, otp2Connection, otp3Connection, otp4Connection, agr1);
        break;
    case TestAgr2_ID:
        widget->setWindowTitle("Определение активности фактора Виллебранда, тест");
        widget->setUserMessage("Определение активности фактора Виллебранда, тест");
        t_singeShotConntection(printConnection, t1Connection, t2Connection, t3Connection, t4Connection, agr2);
        btp_singeShotConntection( btp1Connection, btp2Connection, btp3Connection, btp4Connection, agr2);
        otp_singeShotConntection( otp1Connection, otp2Connection, otp3Connection, otp4Connection, agr2);
        //centerWidget->setUserMessage(tr("<div style='color: blue'>Установите в рабочие каналы кюветы с пробами и нажмите \"Старт\""));
        break;
    default:
        break;
    }
}

void ChoiseDialog::calibration(StartMeasurement* sm)
{
    CreateWidgetThread(sm);
    Mode_ID mode = sm->getModeID();

    MetaObj *printConnection = new MetaObj;
    MetaObj *t1Connection = new MetaObj;
    MetaObj *t2Connection = new MetaObj;
    MetaObj *t3Connection = new MetaObj;
    MetaObj *t4Connection = new MetaObj;
    MetaObj *otp1Connection;
    MetaObj *otp2Connection;
    MetaObj *otp3Connection;
    MetaObj *otp4Connection;

    MetaObj *btp1Connection;
    MetaObj *btp2Connection;
    MetaObj *btp3Connection;
    MetaObj *btp4Connection;

    if ( mode == CalibAgr1_ID || mode == CalibAgr2_ID) {
        otp1Connection = new MetaObj;
        otp2Connection = new MetaObj;
        otp3Connection = new MetaObj;
        otp4Connection = new MetaObj;

        btp1Connection = new MetaObj;
        btp2Connection = new MetaObj;
        btp3Connection = new MetaObj;
        btp4Connection = new MetaObj;
    }

    switch (mode) {
    case CalibKo2_ID:
        widget->setWindowTitle("АЧТВ, калибровка (Ko2)");
        widget->setUserMessage("АЧТВ, калибровка (Ko2)", 0);
        widget->setUserMessage(QString("<div style='color: blue'>Установите кюветы с контрольной нормальной плазмой и нажмите \"Старт\""), 0);
        c_singeShotConntection(printConnection, t1Connection, t2Connection, t3Connection, t4Connection, ko2);
        break;
    case CalibKo3_ID:
        widget->setUserMessage("Фибриноген, калибровка (Ko3)", 0);
        widget->setUserMessage(QString("<div style='color: blue'>Установите кюветы с контрольной нормальной плазмой и ее разведением, после нажмите \"Старт\""), 0);
        widget->setUserMessage(QString("<div style='color: blue'>Первый этап разведения: Канал 1,2 - 200%, Канал 2,3 - 100%\n"
                                       "Второй этап разведения: Канал 1,2 - 50%, Канал 3,4 - 25%"), 0);
        c_singeShotConntection(printConnection, t1Connection, t2Connection, t3Connection, t4Connection, ko3);
        break;
    case CalibKo4_ID:
        widget->setUserMessage("Тромбин, калибровка (Ko4)", 0);
        widget->setUserMessage(QString("<div style='color: blue'>Установите кюветы с контрольной нормальной плазмой и нажмите \"Старт\""), 0);
        c_singeShotConntection(printConnection, t1Connection, t2Connection, t3Connection, t4Connection, ko4);
        break;
    case CalibKo5_ID:
        widget->setUserMessage(QString("Протромбиновый комплекс, калибровка (Ko5)"), 0);
        widget->setUserMessage(QString("<div style='color: blue'>Установите кюветы с контрольной нормальной плазмой и ее разведением, после нажмите \"Старт\""), 0);
        widget->setUserMessage(QString("<div style='color: blue'>Разведения: Канал 1 - 100%, Канал 2 - 50%, Канал 3 - 25%, Канал 4 - 12.5%"), 0);
        c_singeShotConntection(printConnection, t1Connection, t2Connection, t3Connection, t4Connection, ko5);
        break;
    case CalibAgr1_ID:
        widget->setUserMessage(QString("Определение параметров агрегации, калибровка (Agr1 1)"), 0);
        widget->setUserMessage(QString("<div style='color: blue'>Установите кюветы с контрольной нормальной плазмой и нажмите \"Старт\""), 0);
        c_singeShotConntection(printConnection, t1Connection, t2Connection, t3Connection, t4Connection, agr1);
        btp_singeShotConntection( btp1Connection, btp2Connection, btp3Connection, btp4Connection, agr1);
        otp_singeShotConntection( otp1Connection, otp2Connection, otp3Connection, otp4Connection, agr1);
        break;
    case CalibAgr2_ID:
        widget->setUserMessage(QString("<div style='color: blue'>Установите кюветы с контрольной нормальной плазмой и ее разведением, после нажмите \"Старт\""), 0);
        widget->setUserMessage(QString("<div style='color: blue'>Разведения: Канал 1 - 200%, Канал 2 - 100%, Канал 3 - 50%, Канал 4 - 25%"), 0);
        c_singeShotConntection(printConnection, t1Connection, t2Connection, t3Connection, t4Connection, agr2);
        btp_singeShotConntection( btp1Connection, btp2Connection, btp3Connection, btp4Connection, agr2);
        otp_singeShotConntection( otp1Connection, otp2Connection, otp3Connection, otp4Connection, agr2);
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
    agr1->setTab(1);
}

void ChoiseDialog::on_agr2Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    agr2->setTab(1);
}

void ChoiseDialog::on_ko1Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ko1->setTab(1);
}

void ChoiseDialog::on_ko2Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ko2->setTab(1);
    ko2->open();
}

void ChoiseDialog::on_ko3Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ko3->setTab(1);
}

void ChoiseDialog::on_ko4Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    ko4->setTab(1);
}

void ChoiseDialog::on_ko5Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    ko5->setTab(1);
}

//void ChoiseDialog::on_viewPlotsButton_clicked()
//{
//    QPointer<ViewPlot> vp = new ViewPlot(this);
//    vp->show();
//}

void ChoiseDialog::on_exitButton_clicked()
{
    accept();
}
