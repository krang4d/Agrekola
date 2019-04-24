#include "options.h"
#include "ui_options.h"
#include <QDoubleValidator>

Options::Options(ITools *tool, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Options),
    widget(tool)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::Window);
    setWindowTitle(tr("Настройки"));
    ui->lineEdit_StartDX->setInputMask("0.9");
    ui->lineEdit_MAX->setValidator(new QDoubleValidator(-5.1, 5.1, 2));
    ui->lineEdit_MIN->setValidator(new QDoubleValidator(-5.1, 5.1, 2));

    ui->lineEdit_StartDX->setText(QString("%1").arg(tool->getSTART_DX()));
    ui->lineEdit_StopDX->setText(QString("%1").arg(tool->getSTOP_DX()));
    ui->lineEdit_MAX->setText(QString("%1").arg(tool->getMAX()));
    ui->lineEdit_MIN->setText(QString("%1").arg(tool->getMIN()));
}

Options::~Options()
{
    delete ui;
}

void Options::on_pushButton_Next_clicked()
{
    widget->setSTART_DX(ui->lineEdit_StartDX->text().toDouble());
    widget->setSTOP_DX(ui->lineEdit_StopDX->text().toDouble());
    widget->setMIN(ui->lineEdit_MIN->text().toDouble());
    widget->setMAX(ui->lineEdit_MAX->text().toDouble());
    close();
}
