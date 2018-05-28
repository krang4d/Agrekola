#include "measurement.h"
#include "choisedialog.h"
#include "ui_measurement.h"

Measurement::Measurement(int i, QWidget *parent) :
    index(i),
    QWidget(parent),
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

void Measurement::on_pushButton_return_clicked()
{
    ChoiseDialog *ch = new ChoiseDialog;
    //QWidget *p = static_cast<QWidget*>(this->parent());
    //p->show();
    ch->show();
    this->hide();
}
