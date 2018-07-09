#include "choisedialog.h"
#include "ui_choisedialog.h"

#include "mainwindow.h"
#include "QMessageBox"
#include "widget.h"

ChoiseDialog::ChoiseDialog(useE154 *a, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::ChoiseDialog),
    agrekola(a)
{
    ui->setupUi(this);

    agr1 = static_cast<Agr1 *>(ui->stackedWidget->widget(1));
    agr2 = static_cast<Agr2 *>(ui->stackedWidget->widget(2));

    ko1 = static_cast<Ko1 *>(ui->stackedWidget->widget(3));
    ko2 = static_cast<Ko2 *>(ui->stackedWidget->widget(4));
    ko3 = static_cast<Ko3 *>(ui->stackedWidget->widget(5));
    ko4 = static_cast<Ko4 *>(ui->stackedWidget->widget(6));
    ko5 = static_cast<Ko5 *>(ui->stackedWidget->widget(7));

    //test = new TestKoAgr(this);

    connect(agr1, SIGNAL(measurement()), SLOT(accept()));
    //connect(agr2, SIGNAL(measurement()), SLOT(accept()));
    connect(ko1, SIGNAL(measurement()), SLOT(accept()));
    connect(ko2, SIGNAL(measurement()), SLOT(accept()));
    connect(ko3, SIGNAL(measurement()), SLOT(accept()));
    connect(ko4, SIGNAL(measurement()), SLOT(accept()));
    connect(ko5, SIGNAL(measurement()), SLOT(accept()));

    connect(agr1, SIGNAL(calibration()), SLOT(calibration()));
    //connect(agr2, SIGNAL(calibration()), SLOT(calibration()));
    connect(ko2, SIGNAL(calibration()), SLOT(calibration()));
    connect(ko3, SIGNAL(calibration()), SLOT(calibration()));
    connect(ko5, SIGNAL(calibration()), SLOT(calibration()));
    connect(ko4, SIGNAL(calibration()), SLOT(calibration()));
}

int ChoiseDialog::getTypeOfWidget() const
{
    return ui->stackedWidget->currentIndex();
}

ChoiseDialog::~ChoiseDialog()
{
    delete mw;
    delete test;
    delete agr1;
    delete agr2;
    delete ko1;
    delete ko2;
    delete ko3;
    delete ko4;
    delete ko5;
    delete ui;
}

void ChoiseDialog::on_testButton_clicked()
{
    //TestKoAgr *test = new TestKoAgr(this);
    //hide();
    test = new Widget;
    agrekola->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, agrekola, &QObject::deleteLater);
    connect(agrekola, SIGNAL(value_come(QVector<double>)), test, SLOT(realtimeDataSlotDuo(QVector<double>)));
    connect(agrekola, SIGNAL(update_termo(bool)), test, SLOT(updataTermo(bool)));
    connect(test, SIGNAL(onMixCh1(bool)), agrekola, SLOT(onMixCh1(bool)));
    connect(test, SIGNAL(onMixCh2(bool)), agrekola, SLOT(onMixCh2(bool)));
    connect(test, SIGNAL(onMixCh1(bool)), agrekola, SLOT(onMixCh3(bool)));
    connect(test, SIGNAL(onMixCh1(bool)), agrekola, SLOT(onMixCh4(bool)));
    connect(test, SIGNAL(onMixPP(bool)), agrekola, SLOT(onMixPP(bool)));
    connect(test, SIGNAL(onLaser(bool)), agrekola, SLOT(onLaser(bool)));
    connect(test, SIGNAL(stop()), agrekola, SLOT(stopThread()));
    workerThread.start();
    test->setTestMode(true);
    test->setWindowModality(Qt::ApplicationModal);
    test->show();
}

void ChoiseDialog::calibration()
{
    int i = ui->stackedWidget->currentIndex();
    QMessageBox test(QMessageBox::Warning, "calibration", QString("calibration #") + QString(std::to_string(i).c_str()), QMessageBox::Ok);
    test.exec();
    //if(i == 2) kalibragr2->show();
}

void ChoiseDialog::accept()
{
    //QMessageBox msg_accept(QMessageBox::Warning, "accept", QString("i =") + QString(std::to_string(i).c_str()), QMessageBox::Ok);
    //msg_accept.exec();
    mw = new MainWindow(this);
    mw->newShow();
    hide();
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
