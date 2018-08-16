#ifndef PROGRESSTIMERBAR_H
#define PROGRESSTIMERBAR_H

#include <QWidget>
#include <QTimer>
#include <functional>

//typedef void (*Function)(void);

namespace Ui {
class ProgressTimerBar;
}

class ProgressTimerBar : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressTimerBar(QWidget *parent = 0);
    ~ProgressTimerBar();
    void startProgress(QString format, int timer_tic_ms, int time_ms);
    void startProgress(QString format, int timer_tic_ms, int time_ms, std::function<void (void)> f);

private:
    Ui::ProgressTimerBar *ui;
    QTimer progressTimer;

public slots:
    void updateProgress();

private:
    std::function<void (void)> func;
};

#endif // PROGRESSTIMERBAR_H
