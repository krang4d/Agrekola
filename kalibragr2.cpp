#include "kalibragr2.h"
#include "ui_kalibragr2.h"
#include <QEvent>
#include <QDebug>

KalibrAgr2::KalibrAgr2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KalibrAgr2)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(QString("Определение активности фактора Виллебранда. Калибровка"));
    setAttribute(Qt::WA_DeleteOnClose);
    installEventFilter(this);
    ui->widget->setUserMessage("Определение активности фактора Виллебранда, калибровка (2)");
}

KalibrAgr2::~KalibrAgr2()
{
    delete ui;
}

bool KalibrAgr2::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::Close)
    {
        qDebug() << "KalibrAgr2::eventFilter!";
    }
    return QWidget::eventFilter(watched, event);
}
