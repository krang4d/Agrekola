#include "progresstimerbar.h"
#include "ui_progresstimerbar.h"
#include <QDebug>

#define TIMER_PERIOD_MS 100

ProgressTimerBar::ProgressTimerBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgressTimerBar),
    func(nullptr)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    ui->progressBar->setFormat("В ожидании");
    //таймер для отображения процесса сбора данных
    connect(&progressTimer, SIGNAL(timeout()), SLOT(updateProgress()));
}

ProgressTimerBar::~ProgressTimerBar()
{
    delete ui;
}

void ProgressTimerBar::startProgress(QString format, int time_ms)
{
    ui->progressBar->setFormat(format);
    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(time_ms);
    progressTimer.start(TIMER_PERIOD_MS);
    show();
}

void ProgressTimerBar::startProgress(QString format, int time_ms, std::function<void(void)> f)
{
    startProgress(format, time_ms);
    func = f;
}

void ProgressTimerBar::setValue(int value)
{
    ui->progressBar->setValue(value);
}

void ProgressTimerBar::setMaximum(int maximum)
{
    ui->progressBar->setMaximum(maximum);
}

void ProgressTimerBar::setFormat(QString format)
{
    ui->progressBar->setFormat(format);
}

void ProgressTimerBar::updateProgress()
{
    //ui->progressBar->setMaximum(progress_t-progressTimer.interval());
    if(ui->progressBar->value() < ui->progressBar->maximum()) {
        ui->progressBar->setValue(ui->progressBar->value()+progressTimer.interval());
    }
    else {
        progressTimer.stop();
        if(func) {
            func();
            qDebug() << "Выплнение func";
        }
        ui->progressBar->setFormat("В ожидании");
        ui->progressBar->setValue(0);
        emit done();
        //hide();
    }
}
