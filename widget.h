#ifndef WIDGET_H
#define WIDGET_H

#include <QString>
#include <QWidget>
#include <QTimer>
#include <QDateTime>
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
    ~Widget();

    void setUserMessage(QString);
    void setAgrekola(useE154 *agr);
    void setupQuadraticPlot(QVector<double> data = {0});
    void setupRealtimeData();

private:
    void setupTimers();

private slots:
    void realtimeDataSlot();

    void on_checkBox_1_stateChanged(int arg1);
    void on_checkBox_2_stateChanged(int arg1);
    void on_checkBox_3_stateChanged(int arg1);
    void on_checkBox_4_stateChanged(int arg1);

    void updataTermo();
    void updateTime();
    void getData();

private:
    Ui::Widget *ui;
    QString text;
    useE154 *agrekola;
    QTimer dataTimer, TDTimer, *currenttime;
    QDateTime dt;
    QCustomPlot *customPlot1;
    QCustomPlot *customPlot2;
    QCustomPlot *customPlot3;
    QCustomPlot *customPlot4;
};

#endif // WIDGET_H
