#include "parametersofcalibration.h"
#include "ui_parametersofcalibration.h"

ParametersOfCalibration::ParametersOfCalibration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParametersOfCalibration)
{
    ui->setupUi(this);
}

ParametersOfCalibration::~ParametersOfCalibration()
{
    delete ui;
}

void ParametersOfCalibration::setText(QString str)
{
    ui->label->setText(str);
}
