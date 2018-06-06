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

public slots:
    void updatetime();

private:
    Ui::Measurement *ui;
    QTimer *timer;
    QDateTime dt;
};

#endif // MEASUREMENT_H
