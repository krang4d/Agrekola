#ifndef PROGRESSTIMERBAR_H
#define PROGRESSTIMERBAR_H

#include <QWidget>
#include <QTimer>
#include <QString>
#include <functional>

#define TIMER_PERIOD_MS 100
enum State_ID { Ready = 0, Incube_1, Incube_2, WaitImp, Measur, Write, Calc };
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
    void startProgress(QString format, int time_ms);
    void startProgress(QString format, int time_ms, std::function<void (void)> f);
    void setMaximum(int maximum);
    void setFormat(QString format);

    inline State_ID getState() {
        return state;
    }

    inline void setState(State_ID s) {
        state = s;
    }

signals:
    done();

public slots:
    void updateProgress();
    void setValue(int value);

private:
    Ui::ProgressTimerBar *ui;
    std::function<void (void)> func;
    QTimer progressTimer;
    State_ID state;
};

#endif // PROGRESSTIMERBAR_H
