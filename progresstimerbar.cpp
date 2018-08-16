#include "progresstimerbar.h"
#include "ui_progresstimerbar.h"
#include <QDebug>

ProgressTimerBar::ProgressTimerBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgressTimerBar),
    func(nullptr)
{
    ui->setupUi(this);
    //таймер для отображения процесса сбора данных
    connect(&progressTimer, SIGNAL(timeout()), SLOT(updateProgress()));
}

ProgressTimerBar::~ProgressTimerBar()
{
    delete ui;
}

void ProgressTimerBar::startProgress(QString format, int timer_tic_ms, int time_ms)
{
    ui->progressBar->setFormat(format);
    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(time_ms);
    progressTimer.start(timer_tic_ms);
    show();
}

void ProgressTimerBar::startProgress(QString format, int timer_tic_ms, int time_ms, std::function<void(void)> f)
{
    startProgress(format, timer_tic_ms, time_ms);
    func = f;
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
        hide();
    }
}
