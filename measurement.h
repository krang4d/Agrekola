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
    explicit Measurement( int i = 0, QWidget *parent = 0);
    ~Measurement();
public slots:
    void updatetime();

private slots:
    void on_pushButton_return_clicked();
    void on_pushButton_viewGraph_clicked();

private:
    int index;
    QWidget *p;
    Ui::Measurement *ui;
    QTimer *timer;
    QDateTime dt;
    QWidget *viewplot;
};

#endif // MEASUREMENT_H
