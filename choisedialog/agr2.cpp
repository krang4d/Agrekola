#include "agr2.h"
#include "ui_agr2.h"

Agr2::Agr2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Agr2)
{
    ui->setupUi(this);
    selcalibrAgr1 = new SelectCalibrationAgr1();
    selInductor = new SelectInductor();
}

Agr2::~Agr2()
{
    delete ui;
    delete kalibragr2;
    delete selInductor;
    delete selcalibrAgr1;
}

void Agr2::on_startButton_clicked()
{
    selcalibrAgr1->show();
    emit measurement();
}

void Agr2::on_calibrButton_clicked()
{
    kalibragr2 = new KalibrAgr2();
    kalibragr2->show();
    emit calibration();
}
