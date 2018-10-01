#include "options.h"
#include "ui_options.h"
#include <QDoubleValidator>

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::Window);
    setWindowTitle(tr("Настройки"));
    ui->lineEdit_DX->setInputMask("0.9");
    ui->lineEdit_MAX->setValidator(new QDoubleValidator(-5.1, 5.1, 2));
    ui->lineEdit_MIN->setValidator(new QDoubleValidator(-5.1, 5.1, 2));
}

void Options::setWidget(Widget *w)
{
    widget = w;
    ui->lineEdit_DX->setText(QString("%1").arg(w->Start_DX));
    ui->lineEdit_MAX->setText(QString("%1").arg(w->MAX));
    ui->lineEdit_MIN->setText(QString("%1").arg(w->MIN));
}

Options::~Options()
{
    delete ui;
}

void Options::on_pushButton_Next_clicked()
{
    double max = ui->lineEdit_MAX->text().toDouble();
    double min = ui->lineEdit_MIN->text().toDouble();
    double dx = ui->lineEdit_DX->text().toDouble();
    widget->Start_DX =dx;
    widget->MIN = min;
    widget->MAX =max;
    widget->customPlot1->yAxis->setRange(min, max);
    widget->customPlot1->replot();
    widget->customPlot2->yAxis->setRange(min, max);
    widget->customPlot2->replot();
    widget->customPlot3->yAxis->setRange(min, max);
    widget->customPlot3->replot();
    widget->customPlot4->yAxis->setRange(min, max);
    widget->customPlot4->replot();
    qDebug() << "DX:" << widget->Start_DX << "MAX:" << widget->MAX << "MIN:" << widget->MIN;
    close();
}
