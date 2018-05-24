#include "measurement.h"
#include "ui_measurement.h"

Measurement::Measurement(QWidget *parent, int i) :
    QWidget(parent),
    index(i),
    ui(new Ui::Measurement)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(updatetime()));
    timer->start(1000);
    dt = QDateTime::currentDateTime();
    ui->label_type->setText(QString(std::to_string(i).c_str()));
}

Measurement::~Measurement()
{
    timer->stop();
    delete timer;
    delete ui;
}

void Measurement::updatetime()
{
    dt = QDateTime::currentDateTime();
    ui->label_time->setText("Время: " + dt.toString("hh:mm:ss"));
    ui->label_date->setText("Дата: " + dt.toString("dd.MM.yyyy"));
}
