#include "selectcalibrationagr1.h"
#include "ui_selectcalibrationagr1.h"

SelectCalibrationAgr1::SelectCalibrationAgr1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectCalibrationAgr1)
{
    ui->setupUi(this);
}

SelectCalibrationAgr1::~SelectCalibrationAgr1()
{
    delete ui;
}
