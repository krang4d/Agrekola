#include "measurement.h"
#include "ui_measurement.h"

#include <QScrollBar>

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
    QString text;
    list_usrmsg.push_back(QString(tr("%1, время \"%2\"")).arg(s).arg(dt.toString("hh:mm:ss")));
    for(int i = 0; i < list_usrmsg.length(); i++) {
        text += QString(tr("%1\n").arg(list_usrmsg.at(i)));
    }
    ui->textBrowser->setText(text);
    QScrollBar *vb = ui->textBrowser->verticalScrollBar();
    vb->setValue(vb->maximum());
}

void Measurement::updatetime()
{
    dt = QDateTime::currentDateTime();
    ui->label_time->setText("Время: " + dt.toString("hh:mm:ss"));
    ui->label_date->setText("Дата: " + dt.toString("dd.MM.yyyy"));
}

void Measurement::getData()
{
    //parentWidget()->
    setUserMessage(tr("signal come \"startMeasurment()\""));
}
