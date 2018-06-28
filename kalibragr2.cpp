#include "kalibragr2.h"
#include "ui_kalibragr2.h"

KalibrAgr2::KalibrAgr2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KalibrAgr2)
{
    ui->setupUi(this);
    setWindowTitle(QString("Определение активности фактора Виллебранда. Калибровка"));
}

KalibrAgr2::~KalibrAgr2()
{
    delete ui;
}
