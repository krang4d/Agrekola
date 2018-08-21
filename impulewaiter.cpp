#include "impulewaiter.h"
#include "ui_impulewaiter.h"
#include <QDebug>

ImpuleWaiter::ImpuleWaiter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImpuleWaiter),
    count(0)
{
    ui->setupUi(this);
    ui->pushButton_1->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
}

void ImpuleWaiter::startWait()
{
    connect(&loop, SIGNAL(timeout()), SLOT(loopslot()));
    loop.start(300);
    show();
}

void ImpuleWaiter::addWaiter(int n)
{
    count++;
    switch (n) {
    case 1:
        ui->pushButton_1->setEnabled(true);
        break;
    case 2:
        ui->pushButton_2->setEnabled(true);
        break;
    case 3:
        ui->pushButton_3->setEnabled(true);
        break;
    case 4:
        ui->pushButton_4->setEnabled(true);
        break;
    default: qDebug() << "ImpuleWaiter::addImpulse out of range!";
        break;
    }
}

ImpuleWaiter::~ImpuleWaiter()
{
    delete ui;
}

void ImpuleWaiter::on_pushButton_1_clicked()
{
    has_pulse_1();
    emit press_1();
}

void ImpuleWaiter::on_pushButton_2_clicked()
{
    has_pulse_2();
    emit press_2();
}

void ImpuleWaiter::on_pushButton_3_clicked()
{
    has_pulse_3();
    emit press_3();
}

void ImpuleWaiter::on_pushButton_4_clicked()
{
    has_pulse_4();
    emit press_4();
}

void ImpuleWaiter::loopslot()
{
    ui->lcdNumber->display(count);
    if(count == 0 ) {
        loop.stop();
        hide();
        emit alldone();
        destroy(true, true);
        deleteLater();
    }
}

void ImpuleWaiter::has_pulse_1()
{
    ui->pushButton_1->setEnabled(false);
    ui->pushButton_1->setText("Запущен");
    count--;
}

void ImpuleWaiter::has_pulse_2()
{
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_2->setText("Запущен");
    count--;
}

void ImpuleWaiter::has_pulse_3()
{
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_3->setText("Запущен");
    count--;
}

void ImpuleWaiter::has_pulse_4()
{
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_4->setText("Запущен");
    count--;
}
