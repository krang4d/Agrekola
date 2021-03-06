#ifndef PROGRESSTIMERBAR_H
#define PROGRESSTIMERBAR_H

#include <QWidget>
#include <QTimer>
#include <QString>
#include <functional>

#define TIMER_PERIOD_MS 10

//typedef void (*Function)(void);

namespace Ui {
class ProgressTimerBar;
enum State_ID { Busy_ID = 0, Ready_ID };
}

class ProgressTimerBar : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressTimerBar(QWidget *parent = nullptr);
    ~ProgressTimerBar();
    void startProgress(QString format, int time_ms);
    void startProgress(QString format, int time_ms, std::function<void (void)> f);
    void setMaximum(int maximum);
    int getMaximum();
    void setFormat(QString format);
    void Wait();
    int getTime_ms();

    inline Ui::State_ID getState() {
        return state;
    }

    inline void setState(Ui::State_ID s) {
        state = s;
    }

signals:
    void done();

public slots:
    void updateProgress();
    void setValue(int value);
    void stopProgress();

private:
    Ui::ProgressTimerBar *ui;
    std::function<void (void)> func;
    QTimer progressTimer;
    Ui::State_ID state;
    int time;
};

#endif // PROGRESSTIMERBAR_H
