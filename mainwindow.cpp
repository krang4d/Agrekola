#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <QThread>
#include <memory>
#include <functional>
#include <options.h>
#include <calibparam.h>
#include "globalvalue.h"

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
        QMessageBox test(QMessageBox::Critical,
                         "qobject_cast",
                         QString("qobject_cast in MainWindow::newShow()"),
                         QMessageBox::Ok);
        test.exec();
    }
    installEventFilter(this);

    //connect(centerWidget, SIGNAL(status(QString)), this->statusBar(), SLOT(showMessage(QString)));
    connect(centerWidget, &Widget::status,
            [this](QString str){ this->statusBar()->showMessage(str, 2000); });
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

void MainWindow::newShow(StartMeasurement* sw)
{

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
    QPointer<Options> opt = new Options(this);
    opt->setWidget(this->centerWidget);
    opt->exec();
}

void MainWindow::on_action_propety_triggered()
{
    QPointer<CalibParam> par = new CalibParam(this);
    CalcData *p = CalcData::createCalc( centerWidget->getMode() );
    par->setCalc(p);
    par->setText();
    par->createPlot();
    par->show();
    //delete p;
}
