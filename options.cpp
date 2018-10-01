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
    ui->lineEdit_StartDX->setInputMask("0.9");
    ui->lineEdit_MAX->setValidator(new QDoubleValidator(-5.1, 5.1, 2));
    ui->lineEdit_MIN->setValidator(new QDoubleValidator(-5.1, 5.1, 2));
}

void Options::setWidget(Widget *w)
{
    widget = w;
    ui->lineEdit_StartDX->setText(QString("%1").arg(w->Start_DX));
    ui->lineEdit_StopDX->setText(QString("%1").arg(w->Stop_DX));
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
    double start_dx = ui->lineEdit_StartDX->text().toDouble();
    double stop_dx = ui->lineEdit_StopDX->text().toDouble();

    widget->Start_DX = start_dx;
    widget->Stop_DX = stop_dx;
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
    qDebug() << "Start_DX:" << widget->Start_DX<< "Stop_DX: " << widget->Stop_DX << "MAX:" << widget->MAX << "MIN:" << widget->MIN;
    close();
}
