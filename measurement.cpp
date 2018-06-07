#include "measurement.h"
#include "ui_measurement.h"

Measurement::Measurement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Measurement)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(updatetime()));
    timer->start(1000);
    dt = QDateTime::currentDateTime();
}

Measurement::~Measurement()
{
    timer->stop();
    delete timer;
    delete ui;
}

void Measurement::setUserMessage(QString s)
{
    ui->textBrowser->setText(s);
}

void Measurement::setFreq(double f)
{
    freq = f;
    setUserMessage(QString("Интервал между точками: %1").arg(freq));
}

void Measurement::setTime(int t)
{
    time = t;
    setUserMessage(QString("Время записи: %1").arg(time));
}

void Measurement::updatetime()
{
    dt = QDateTime::currentDateTime();
    ui->label_time->setText("Время: " + dt.toString("hh:mm:ss"));
    ui->label_date->setText("Дата: " + dt.toString("dd.MM.yyyy"));
}

void Measurement::getData()
{
    setUserMessage(tr("signal come startMeasurment()"));
}

