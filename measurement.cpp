#include "measurement.h"
#include "ui_measurement.h"
//windows include
#include "choisedialog.h"
#include "viewgraph.h"

Measurement::Measurement(int i, QWidget *parent) :
    index(i),
    p(parent),
    ui(new Ui::Measurement)
{
    ui->setupUi(this);
    viewgraph = new ViewGraph(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(updatetime()));
    timer->start(1000);
    dt = QDateTime::currentDateTime();
    if(i == 1)
    {
        setWindowTitle(QString("Определение параметров агрегации"));
    }
    else if(i == 2)
    {
        setWindowTitle(QString("Определение активности фактора Виллебранда"));
    }
    else if(i == 3)
    {
        setWindowTitle(QString("Время свертывания"));
    }
    else if(i == 4)
    {
        setWindowTitle(QString("АЧТВ"));
    }
    else if(i == 5)
    {
        setWindowTitle(QString("Фибриноген"));
        ui->textBrowser->setText("Установите в каналы кюветы с пробами и мешалками, укажите используемые каналы, выберите парные или одиночные пробы и введите номера проб. Для парных выберайте каналы 1 и 2, либо 3 и 4, номера проб в них должны быть одинаковыми. Измените, если нужно время инкубации затем нажмите кнопку Старт.");
    }
    else if(i == 6)
    {
        setWindowTitle(QString("Тромбин"));
    }
    else if(i == 7)
    {
        setWindowTitle(QString("Протромбиновый комплекс"));
    }
    //ui->label_type->setText(QString(std::to_string(i).c_str()));
}

Measurement::~Measurement()
{
    timer->stop();
    delete timer;
    delete ui;
}

void Measurement::updatetime()
{
    dt = QDateTime::currentDateTime();
    ui->label_time->setText("Время: " + dt.toString("hh:mm:ss"));
    ui->label_date->setText("Дата: " + dt.toString("dd.MM.yyyy"));
}

void Measurement::on_pushButton_return_clicked()
{
    //QWidget *p = static_cast<QWidget*>(this->parent());
    //p->show();
    p->show();
    this->hide();
}

void Measurement::on_pushButton_viewGraph_clicked()
{
    //if(viewplot) {delete viewplot; viewplot = NULL;}
    viewgraph->show();
    this->hide();
}
