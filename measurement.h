#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QWidget>
#include <QTimer>
#include "QDateTime"

namespace Ui {
class Measurement;
}

class Measurement : public QWidget
{
    Q_OBJECT

public:
    explicit Measurement(QWidget *parent = 0, int i = 0);
    ~Measurement();

public slots:
    void updatetime();

private:
    int index;
    Ui::Measurement *ui;
    QTimer *timer;
    QDateTime dt;
};

#endif // MEASUREMENT_H
