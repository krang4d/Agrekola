#ifndef WIDGET_H
#define WIDGET_H
#include <QString>
#include <QWidget>
#include "useE154.h"
#include "QCustomPlot/qcustomplot.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void setText(QString str);
    void setAgrekola(useE154 *agr);
    void setupQuadraticPlot(QCustomPlot *customPlot, QVector<double> data = {0});
    ~Widget();

private slots:
    void on_AdcSample_clicked();
    void on_AdcKadr_clicked();
    void on_AdcSynchro_clicked();

private:
    Ui::Widget *ui;
    QString text;
    useE154 *Agrecola;
};

#endif // WIDGET_H
