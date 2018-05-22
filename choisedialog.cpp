#include "choisedialog.h"
#include "ui_choisedialog.h"

ChoiseDialog::ChoiseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoiseDialog)
{
    ui->setupUi(this);
}

ChoiseDialog::~ChoiseDialog()
{
    delete ui;
}

void ChoiseDialog::on_agr1Button_clicked()
{
//    agr1 = new Agr1;
//    ui->widget = agr1;
//    agr1->show();
}
