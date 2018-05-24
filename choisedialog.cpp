#include "choisedialog.h"
#include "ui_choisedialog.h"
#include "QMessageBox"

#include "agr1.h"
#include "agr2.h"
#include "ko1.h"
#include "ko2.h"
#include "ko3.h"
#include "ko4.h"
#include "ko5.h"
#include "measurement.h"

ChoiseDialog::ChoiseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoiseDialog)
{
    ui->setupUi(this);
    Agr1 *agr1 = static_cast<Agr1 *>(ui->stackedWidget->widget(1));
    Agr2 *agr2 = static_cast<Agr2 *>(ui->stackedWidget->widget(2));
    Ko1 *ko1 = static_cast<Ko1 *>(ui->stackedWidget->widget(3));
    Ko2 *ko2 = static_cast<Ko2 *>(ui->stackedWidget->widget(4));
    Ko3 *ko3 = static_cast<Ko3 *>(ui->stackedWidget->widget(5));
    Ko4 *ko4 = static_cast<Ko4 *>(ui->stackedWidget->widget(6));
    Ko5 *ko5 = static_cast<Ko5 *>(ui->stackedWidget->widget(7));

    connect(agr1, SIGNAL(measurement()), SLOT(accept()));
    connect(agr2, SIGNAL(measurement()), SLOT(accept()));
    connect(ko1, SIGNAL(measurement()), SLOT(accept()));
    connect(ko2, SIGNAL(measurement()), SLOT(accept()));
    connect(ko3, SIGNAL(measurement()), SLOT(accept()));
    connect(ko4, SIGNAL(measurement()), SLOT(accept()));
    connect(ko5, SIGNAL(measurement()), SLOT(accept()));
}

ChoiseDialog::~ChoiseDialog()
{
    delete ui;
}

void ChoiseDialog::accept()
{
    int i = ui->stackedWidget->currentIndex();
    QMessageBox err(QMessageBox::Warning, "aceept", QString("i =") + QString(std::to_string(i).c_str()), QMessageBox::Ok);
    err.exec();
    Measurement *m  = new Measurement(NULL, i);
    m->show();
    //QDialog::accept();
}

void ChoiseDialog::on_agr1Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void ChoiseDialog::on_agr2Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void ChoiseDialog::on_ko1Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void ChoiseDialog::on_ko2Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void ChoiseDialog::on_ko3Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void ChoiseDialog::on_ko4Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void ChoiseDialog::on_ko5Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

