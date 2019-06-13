#include "options.h"
#include "ui_options.h"
//#include <QDoubleValidator>

Options::Options(ITools *tool, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Options),
    widget(tool)
{
    ui->setupUi(this);
    //setAttribute(Qt::WA_DeleteOnClose);
    setWindowModality(Qt::WindowModal);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle(tr("Настройки"));
//    ui->lineEdit_StartDX->setInputMask("0.999");
//    ui->lineEdit_StopDX->setInputMask("0.999");
//    ui->lineEdit_MAX->setInputMask("0.9");
//    ui->lineEdit_MIN->setInputMask("-0.9");
//    ui->lineEdit_MAX->setInputMask("6.0");
//    ui->lineEdit_MIN->setInputMask("-6.0");
//    ui->lineEdit_MAX->setValidator(new QDoubleValidator(-5.1, 5.1, 2));
//    ui->lineEdit_MIN->setValidator(new QDoubleValidator(-5.1, 5.1, 2));
//    ui->lineEdit_MIX->setValidator(new QDoubleValidator(0, 100, 1));
    ui->start_dx_doubleSpinBox_1->setValue(widget->getSTART_DX1());
    ui->start_dx_doubleSpinBox_2->setValue(widget->getSTART_DX2());
    ui->start_dx_doubleSpinBox_3->setValue(widget->getSTART_DX3());
    ui->start_dx_doubleSpinBox_4->setValue(widget->getSTART_DX4());

    ui->stop_dx_doubleSpinBox_1->setValue(widget->getSTOP_DX1());
    ui->stop_dx_doubleSpinBox_2->setValue(widget->getSTOP_DX2());
    ui->stop_dx_doubleSpinBox_3->setValue(widget->getSTOP_DX3());
    ui->stop_dx_doubleSpinBox_4->setValue(widget->getSTOP_DX4());

    ui->max_doubleSpinBox->setValue(widget->getMAX());
    ui->min_doubleSpinBox->setValue(widget->getMIN());
//    ui->lineEdit_StartDX->setText(QString("%1").arg());
//    ui->lineEdit_StopDX->setText(QString("%1").arg(tool->getSTOP_DX()));
//    ui->lineEdit_MAX->setText(QString("%1").arg(tool->getMAX()));
//    ui->lineEdit_MIN->setText(QString("%1").arg(tool->getMIN()));
//    ui->lineEdit_MIX->setText(QString("%1").arg(tool->getMIX()));
}

Options::~Options()
{
    delete ui;
}

void Options::on_pushButton_Next_clicked()
{
    widget->setSTART_DX1(ui->start_dx_doubleSpinBox_1->value());
    widget->setSTART_DX2(ui->start_dx_doubleSpinBox_2->value());
    widget->setSTART_DX3(ui->start_dx_doubleSpinBox_3->value());
    widget->setSTART_DX4(ui->start_dx_doubleSpinBox_4->value());

    widget->setSTOP_DX1(ui->stop_dx_doubleSpinBox_1->value());
    widget->setSTOP_DX2(ui->stop_dx_doubleSpinBox_2->value());
    widget->setSTOP_DX3(ui->stop_dx_doubleSpinBox_3->value());
    widget->setSTOP_DX4(ui->stop_dx_doubleSpinBox_4->value());

    widget->setMAX(ui->max_doubleSpinBox->value());
    widget->setMIN(ui->min_doubleSpinBox->value());

//    widget->setSTART_DX(ui->lineEdit_StartDX->text().toDouble());
//    widget->setSTOP_DX(ui->lineEdit_StopDX->text().toDouble());
//    widget->setMIN(ui->lineEdit_MIN->text().toDouble());
//    widget->setMAX(ui->lineEdit_MAX->text().toDouble());
//    widget->setMIX(ui->lineEdit_MIX->text().toDouble());
    close();
}

void Options::closeEvent(QCloseEvent *event)
{
    //deleteLater();
    this->hide();
    event->ignore();
}
