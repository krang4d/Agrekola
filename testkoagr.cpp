#include "testkoagr.h"
#include "ui_testkoagr.h"

TestKoAgr::TestKoAgr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestKoAgr)
{
    ui->setupUi(this);
}

TestKoAgr::~TestKoAgr()
{
    delete ui;
}


void TestKoAgr::on_pushButton_back_clicked()
{
    accept();
}
