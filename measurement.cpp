#include "measurement.h"
#include "ui_measurement.h"

Measurement::Measurement(QWidget *parent, int i) :
    QWidget(parent),
    index(i),
    ui(new Ui::Measurement)
{
    ui->setupUi(this);
    ui->label_type->setText(QString(std::to_string(index).c_str()));
}

Measurement::~Measurement()
{
    delete ui;
}
