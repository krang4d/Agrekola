#include "progresstimerbar.h"
#include "ui_progresstimerbar.h"
#include <QDebug>

ProgressTimerBar::ProgressTimerBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgressTimerBar),
    func(nullptr)
{
    ui->setupUi(this);
    //ui->progressBar->setInvertedAppearance(true);
    ui->progressBar->setValue(0);
    ui->progressBar->setFormat("В ожидании");
    ui->progressBar->setMaximum(0);
    ui->progressBar->setMinimum(0);
    state = Ui::Ready_ID;
    time = 0;
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
    time = 0;
    progressTimer.start(TIMER_PERIOD_MS);
    setState(Ui::Busy_ID);
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
    if(ui->progressBar->value() == ui->progressBar->maximum())
        ui->progressBar->setFormat("Готов");
}

void ProgressTimerBar::setMaximum(int maximum)
{
    ui->progressBar->setMaximum(maximum);
}

int ProgressTimerBar::getMaximum()
{
    return ui->progressBar->maximum();
}

void ProgressTimerBar::setFormat(QString format)
{
    ui->progressBar->setFormat(format);
}

void ProgressTimerBar::Wait()
{
    ui->progressBar->setMaximum(0);
    ui->progressBar->setMinimum(0);
    progressTimer.stop();
    setState(Ui::Ready_ID);
}

int ProgressTimerBar::getTime_ms()
{
    return time;
}

void ProgressTimerBar::updateProgress()
{
    time += TIMER_PERIOD_MS;
    //ui->progressBar->setMaximum(progress_t-progressTimer.interval());
    if(ui->progressBar->value() < ui->progressBar->maximum()) {
        ui->progressBar->setValue((ui->progressBar->value()+progressTimer.interval()));
    }
    else {
        progressTimer.stop();
        //ui->progressBar->setFormat("Готово");
        //ui->progressBar->setValue(0);
        setState(Ui::Ready_ID);
        emit done();
        if(func) {
            qDebug() << "progress bar is stopped and to start the func()";
            func();            
        }
        //hide();
    }
}

void ProgressTimerBar::stopProgress()
{
    progressTimer.stop();
    //ui->progressBar->setFormat("Готово");
    //ui->progressBar->setValue(0);
    setState(Ui::Ready_ID);
    emit done();
    if(func) {
        qDebug() << "progress bar is stopped and to start the funk()";
        func();      
    }
    //hide();
}
