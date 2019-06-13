#include "testkoagr.h"
#include "ui_testkoagr.h"

TestKoAgr::TestKoAgr(IuseE154 *e, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestKoAgr),
    e154(e)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    setup();
}

TestKoAgr::~TestKoAgr()
{
    setup();
    //delete e154;
    delete ui;
}

void TestKoAgr::setup()
{
    e154->onLaser(false);
    e154->onMixCh1(false);
    e154->onMixCh2(false);
    e154->onMixCh3(false);
    e154->onMixCh4(false);
    e154->onMixPP(false);
}

void TestKoAgr::on_pushButton_onLaser_clicked()
{
    e154->onLaser(true);
}

void TestKoAgr::on_pushButton_offLaser_clicked()
{
    e154->onLaser(false);
}

void TestKoAgr::on_pushButton_onMix1_clicked()
{
    e154->onMixCh1(true);
}

void TestKoAgr::on_pushButton_offMix1_clicked()
{
    e154->onMixCh1(false);
}

void TestKoAgr::on_pushButton_onMix2_clicked()
{
    e154->onMixCh2(true);
}

void TestKoAgr::on_pushButton_offMix2_clicked()
{
    e154->onMixCh2(false);
}

void TestKoAgr::on_pushButton_onMix3_clicked()
{
    e154->onMixCh3(true);
}

void TestKoAgr::on_pushButton_offMix3_clicked()
{
    e154->onMixCh3(false);
}

void TestKoAgr::on_pushButton_onMix4_clicked()
{
    e154->onMixCh4(true);
}

void TestKoAgr::on_pushButton_offMix4_clicked()
{
    e154->onMixCh4(false);
}

void TestKoAgr::on_pushButton_onMixPP_clicked()
{
    e154->onMixPP(true);
}

void TestKoAgr::on_pushButton_offMixPP_clicked()
{
    e154->onMixPP(false);
}

void TestKoAgr::on_pushButton_poll_clicked()
{
    QVariantList a = e154->AdcKADR();
    double p1 = a[0].toDouble();
    double p2 = a[1].toDouble();
    double p3 = a[2].toDouble();
    double p4 = a[3].toDouble();
    qDebug() << QString("Получены данные: %1, %2, %3, %4").arg(p1).arg(p2).arg(p3).arg(p4);
    QMessageBox::information(this, "Данные от АЦП",
                             QString("%1\nКанал 1: %2\nКанал 2: %3\nКанал 3: %4\nКанал 4: %5\n")
                             .arg(e154->GetInformation()).arg(p1).arg(p2).arg(p3).arg(p4));
}

void TestKoAgr::on_pushButton_back_clicked()
{
    accept();
}

