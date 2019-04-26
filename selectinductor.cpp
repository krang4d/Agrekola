#include "selectinductor.h"
#include "ui_selectinductor.h"
#include "QMessageBox"

SelectInductor::SelectInductor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectInductor)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

SelectInductor::~SelectInductor()
{
    delete ui;
}

void SelectInductor::on_radioButton_other_toggled(bool checked)
{
    if(checked)
        ui->lineEdit_other->setEnabled(true);
    else ui->lineEdit_other->setEnabled(false);
}

void SelectInductor::on_pushButton_ok_clicked()
{
    if(ui->radioButton_other->isChecked() && (ui->lineEdit_other->text().isEmpty())){
        QMessageBox::information(this ,"Внимание!", "Пожалуйста введите название индуктора.");
    }
    else {
        accept();
        //msg.setText("OK"); msg.exec();
    }
}
