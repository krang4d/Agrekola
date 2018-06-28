#ifndef WIDGET_H
#define WIDGET_H
#include <QString>
#include <QWidget>
#include <QTimer>
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
    void setupQuadraticPlot(QVector<double> data = {0});
    void setupRealtimeData();
    ~Widget();

private slots:
    void on_AdcSample_clicked();
    void on_AdcKadr_clicked();
    void on_AdcSynchro_clicked();
    void realtimeDataSlot();

    void on_checkBox_1_stateChanged(int arg1);
    void on_checkBox_2_stateChanged(int arg1);
    void on_checkBox_3_stateChanged(int arg1);
    void on_checkBox_4_stateChanged(int arg1);

    void updataTD();

private:
    Ui::Widget *ui;
    QString text;
    useE154 *Agrecola;
    QTimer dataTimer, TDTimer;
    QCustomPlot *customPlot1;
    QCustomPlot *customPlot2;
    QCustomPlot *customPlot3;
    QCustomPlot *customPlot4;
};

#endif // WIDGET_H
