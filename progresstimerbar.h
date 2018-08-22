#ifndef PROGRESSTIMERBAR_H
#define PROGRESSTIMERBAR_H

#include <QWidget>
#include <QTimer>
#include <QString>
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
    void startProgress(QString format, int time_ms);
    void startProgress(QString format, int time_ms, std::function<void (void)> f);
    void setMaximum(int maximum);
    void setFormat(QString format);

private:
    Ui::ProgressTimerBar *ui;
    QTimer progressTimer;
signals:
    done();

public slots:
    void updateProgress();
    void setValue(int value);

private:
    std::function<void (void)> func;
};

#endif // PROGRESSTIMERBAR_H
