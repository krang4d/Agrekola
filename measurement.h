#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QWidget>
#include <QTimer>
#include <QString>
#include "QDateTime"

namespace Ui {
class Measurement;
}

class Measurement : public QWidget
{
    Q_OBJECT

public:
    explicit Measurement(QWidget *parent = 0);
    ~Measurement();
    void setUserMessage(QString);
    void setFreq(double);
    void setTime(int);

public slots:
    void updatetime();
    void getData();

private:
    Ui::Measurement *ui;
    QTimer *timer;
    QDateTime dt;

    //параметры измерения//
    double freq; //интервал между точками
    int time;    //время записи
};

#endif // MEASUREMENT_H
