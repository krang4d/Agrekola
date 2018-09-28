#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <QThread>
#include <memory>
#include <functional>
#include <options.h>

using namespace std::placeholders;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    agrekola(new useE154),
    centerWidget(new Widget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setCentralWidget(centerWidget);
    ch = qobject_cast<ChoiseDialog *>(parentWidget());
    if (!ch){
        QMessageBox test(QMessageBox::Critical, "qobject_cast", QString("qobject_cast in MainWindow::newShow()"), QMessageBox::Ok); test.exec();
    }
    installEventFilter(this);
    connect(centerWidget, SIGNAL(status(QString)), this->statusBar(), SLOT(showMessage(QString)));
    setupThread();
}

MainWindow::~MainWindow()
{   
    agrekola->stopThread();
    QThread::currentThread()->msleep(100); //ожидание завершения работы потока useE154
    if(agrekola->isFinished()) {
        delete agrekola;
    } else qDebug() << "the Agrekoal can not stoped form the ~MainWindow()";
    delete ui;
}

void MainWindow::newShow(StartMeasurment* sw)
{
    show();
    int i = ch->getTypeOfWidget();
    //else  {QMessageBox test(QMessageBox::Warning, "qobject_cast", QString("qobject_cast"), QMessageBox::Ok); test.exec();}
    QString str;
    switch (i) {
    case 1: {
        str = tr("Определение параметров агрегации, измерение (1)");
        setWindowTitle(str);
        centerWidget->setUserMessage(str);

        centerWidget->setStartWindow(StartCalibrationAgr1::getBTP100());
        centerWidget->setMode(Level_ID);

        QMessageBox *imessageBox = new QMessageBox(this);
        imessageBox->setText(QString("Фиксация «100%» и «0%» уровней. Подготовьте и пронумеруйте пробы с БТП и ОТП"));
        imessageBox->exec();

        std::function<void(void)> fun = [this, sw, i](){ qDebug() << "getBTP100() done";
            centerWidget->setStartWindow(StartCalibrationAgr1::getOTP0());
            centerWidget->getLevelOTP();
            disconnect(centerWidget, &Widget::done, 0, 0);
            connect(centerWidget, &Widget::done, [&](){
                centerWidget->setMode(i);
                centerWidget->setStartWindow(sw);
            });
        };
        connect(centerWidget, &Widget::done, fun);

        centerWidget->getLevelBTP();
    }
        break;
    case 2:
        centerWidget->setMode(i);
        centerWidget->setStartWindow(sw);
        str = tr("Определение активности фактора Виллебранда, измерение (2)");
        setWindowTitle(str);
        centerWidget->setUserMessage(str);
        break;
    case 3:
        centerWidget->setMode(i);
        centerWidget->setStartWindow(sw);
        str = tr("Время свертывания, измерение (3)");
        setWindowTitle(str);
        centerWidget->setUserMessage(str);
        break;
    case 4:
        centerWidget->setMode(i);
        centerWidget->setStartWindow(sw);
        str = tr("АЧТВ, измерение (4)");
        setWindowTitle(str);
        centerWidget->setUserMessage(str);
        break;
    case 5:
        centerWidget->setMode(i);
        centerWidget->setStartWindow(sw);
        str = tr("Фибриноген, измерение (5)");
        setWindowTitle(str);
        centerWidget->setUserMessage(tr("Установите в каналы кюветы с пробами и мешалками, укажите используемые каналы, выберите парные или одиночные пробы и введите номера проб. Для парных выберайте каналы 1 и 2, либо 3 и 4, номера проб в них должны быть одинаковыми. Измените, если нужно время инкубации затем нажмите кнопку Старт."));
        break;
    case 6:
        centerWidget->setMode(i);
        centerWidget->setStartWindow(sw);
        str = tr("Тромбин, измерние (6)");
        setWindowTitle(str);
        centerWidget->setUserMessage(str);
        break;
    case 7:
        centerWidget->setMode(i);
        centerWidget->setStartWindow(sw);
        str = tr("Протромбиновый комплекс, измерение (7)");
        setWindowTitle(str);
        centerWidget->setUserMessage(str);
        break;
    default:
        break;
    }
}

void MainWindow::setupThread()
{
    qDebug() << "MainWindow thread ID: " << QThread::currentThreadId();
    //ChoiseDialog choiseDlg;
    QWidget::connect(centerWidget, SIGNAL(onmixch1(bool)), agrekola, SLOT(onMixCh1(bool)));
    QWidget::connect(centerWidget, SIGNAL(onmixch2(bool)), agrekola, SLOT(onMixCh2(bool)));
    QWidget::connect(centerWidget, SIGNAL(onmixch3(bool)), agrekola, SLOT(onMixCh3(bool)));
    QWidget::connect(centerWidget, SIGNAL(onmixch4(bool)), agrekola, SLOT(onMixCh4(bool)));
    QWidget::connect(centerWidget, SIGNAL(onmixpp(bool)), agrekola, SLOT(onMixPP(bool)));
    QWidget::connect(centerWidget, SIGNAL(onlaser(bool)), agrekola, SLOT(onLaser(bool)));
    QObject::connect(centerWidget, SIGNAL(stop()), agrekola, SLOT(stopThread()));
    QObject::connect(centerWidget, SIGNAL(stop()), centerWidget, SLOT(deleteLater()));

    QWidget::connect(agrekola, SIGNAL(update_termo(bool)), centerWidget, SLOT(updataTermo(bool)));
    QWidget::connect(agrekola, SIGNAL(value_come(QVariantList)), centerWidget, SLOT(realtimeDataSlot(QVariantList)));
    QWidget::connect(agrekola, SIGNAL(finished()), agrekola, SLOT(deleteLater()));
    agrekola->start();
}

//void MainWindow::getOTP()
//{
//    //определение ОТП
//    centerWidget->setMode(Level_ID);
//    centerWidget->setStartWindow(StartCalibrationAgr1::getOTP0());
//    centerWidget->setUserMessage(QString("Установите пробы с ОТП в рабочие  каналы и нажмите \"Старт\""), 0);

//    auto saveotp2 = [&](int n, double d) {
//        static int i = 0;
//        i++;
//            QStringList btp100;
//            SaveFiles file_btp;
//            qDebug() << QString("retavlue = %1, index = %2").arg(d).arg(n);
//            file_btp.openBTP100(btp100);
//            if (btp100.isEmpty() || btp100.count() != 4) {
//                btp100 = QStringList({"0", "0", "0", "0"});
//            }
//            btp100.replace(n, QString("%1").arg(d));
//            file_btp.saveBTP100(btp100);
//        qDebug() << "Определение ОТП контрольной плазмы";
//        if(i == 4) {
//            i = 0;
//            emit otp_done();
//        }
//    };

//    connect(centerWidget, &Widget::ret_value1, [&](double x){ disconnect(centerWidget, &Widget::ret_value1, 0, 0);
//            saveotp2(0, x); } );
//    connect(centerWidget, &Widget::ret_value2, [&](double x){ disconnect(centerWidget, &Widget::ret_value2, 0, 0);
//            saveotp2(1, x); } );
//    connect(centerWidget, &Widget::ret_value3, [&](double x){ disconnect(centerWidget, &Widget::ret_value3, 0, 0);
//            saveotp2(2, x); } );
//    connect(centerWidget, &Widget::ret_value4, [&](double x){ disconnect(centerWidget, &Widget::ret_value4, 0, 0);
//            saveotp2(3, x); } );
//}

//void MainWindow::getBTP()
//{
//    //определение БТП
//    centerWidget->setMode(Level_ID);
//    centerWidget->setStartWindow(StartCalibrationAgr1::getBTP100());
//    centerWidget->setUserMessage(QString("Установите пробы с БТП в рабочие  каналы и нажмите \"Старт\""), 0);

//    auto savebtp2 = [&](int n, double d) {
//        static int i = 0;
//        i++;
//        QStringList btp100;
//        SaveFiles file_btp;
//        qDebug() << QString("retavlue = %1, index = %2").arg(d).arg(n);
//        file_btp.openBTP100(btp100);
//        if (btp100.isEmpty() || btp100.count() != 4) {
//            btp100 = QStringList({"0", "0", "0", "0"});
//        }
//        btp100.replace(n, QString("%1").arg(d));
//        file_btp.saveBTP100(btp100);
//        if(i == 4) {
//            i = 0;
//            emit btp_done();
//        }
//    };

//    connect(centerWidget, &Widget::ret_value1, [&](double x){ disconnect(centerWidget, &Widget::ret_value1, 0, 0);
//            savebtp2(0, x); } );
//    connect(centerWidget, &Widget::ret_value2, [&](double x){ disconnect(centerWidget, &Widget::ret_value2, 0, 0);
//            savebtp2(1, x); } );
//    connect(centerWidget, &Widget::ret_value3, [&](double x){ disconnect(centerWidget, &Widget::ret_value3, 0, 0);
//            savebtp2(2, x); } );
//    connect(centerWidget, &Widget::ret_value4, [&](double x){ disconnect(centerWidget, &Widget::ret_value4, 0, 0);
//            savebtp2(3, x); } );
//}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *kayEvent = static_cast<QKeyEvent *>(event);
        if(kayEvent->key() == Qt::Key_Space)
        {
            QMessageBox::about(this, "Event is emmited", "Key_Space is pressed!");
            return true;
        }
    }
    if(event->type() == QEvent::Close)
    {
        //centerWidget->stop();
        ch->show();
        qDebug() << "Event Close is come!";
        //return true;
        return QMainWindow::eventFilter(watched, event);
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::on_menu_triggered()
{
    ch->show();
    close();
}

void MainWindow::on_plots_triggered()
{
    QPointer<ViewPlot> plots = new ViewPlot(this);
    plots->show();
}

void MainWindow::on_action_triggered()
{
    QPointer<options> opt(new options);
    opt->setWidget(this->centerWidget);
    opt->show();
}
