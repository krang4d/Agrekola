#include "choisedialog.h"
#include "ui_choisedialog.h"
#include <QDebug>

ChoiseDialog::ChoiseDialog(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::ChoiseDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    agr1 = static_cast<Agr1 *>(ui->stackedWidget->widget(1));
    agr2 = static_cast<Agr2 *>(ui->stackedWidget->widget(2));

    ko1 = static_cast<Ko1 *>(ui->stackedWidget->widget(3));
    ko2 = static_cast<Ko2 *>(ui->stackedWidget->widget(4));
    ko3 = static_cast<Ko3 *>(ui->stackedWidget->widget(5));
    ko4 = static_cast<Ko4 *>(ui->stackedWidget->widget(6));
    ko5 = static_cast<Ko5 *>(ui->stackedWidget->widget(7));

    connect(agr1, SIGNAL(measurement()), SLOT(startMeasurement()));
    //connect(agr2, SIGNAL(measurement()), SLOT(accept()));
    connect(ko1, SIGNAL(measurement()), SLOT(startMeasurement()));
    connect(ko2, SIGNAL(measurement()), SLOT(startMeasurement()));
    connect(ko3, SIGNAL(measurement()), SLOT(startMeasurement()));
    connect(ko4, SIGNAL(measurement()), SLOT(startMeasurement()));
    connect(ko5, SIGNAL(measurement()), SLOT(startMeasurement()));

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
    qDebug() << "call ChoiseDialog::~ChoiseDialog()";
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
    useE154 *agrekola = new useE154;
    Widget *widget =new Widget;
    //ChoiseDialog choiseDlg;
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

    widget->setTestMode(true);
    widget->show();
    agrekola->start();
}

void ChoiseDialog::calibration()
{
    int i = ui->stackedWidget->currentIndex();
    QMessageBox t(QMessageBox::Warning, "calibration", QString("calibration #") + QString(std::to_string(i).c_str()), QMessageBox::Ok);
    t.exec();
    //if(i == 2) kalibragr2->show();
}

void ChoiseDialog::startMeasurement()
{
    //QMessageBox msg_accept(QMessageBox::Warning, "accept", QString("i =") + QString(std::to_string(i).c_str()), QMessageBox::Ok);
    //msg_accept.exec();
    MainWindow *mw = new MainWindow(this);
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
