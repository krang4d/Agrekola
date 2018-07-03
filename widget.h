#ifndef WIDGET_H
#define WIDGET_H

#include <QString>
#include <QVector>
#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include "useE154.h"
#include "startmeasurment.h"
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
    void onMixCh1(bool);
    void onMixCh2(bool);
    void onMixCh3(bool);
    void onMixCh4(bool);
    void onMixPP(bool);
    void onLaser(bool);
    void setUserMessage(QString, bool withtime = 1, bool tofile = 0);
    void setAgrekola(useE154 *agr);

private:
    bool eventFilter(QObject *watched, QEvent *event);
    void setupQuadraticPlot(QVector<double> data = {0});
    void setupRealtimeData(bool duo = 0);
    void setupTimers();
    void setupFile();

public slots:
    void getData();

private slots:
    void realtimeDataSlotSingle();
    void realtimeDataSlotDuo();
    void writeData();
    void on_checkBox_1_stateChanged(int arg1);
    void on_checkBox_2_stateChanged(int arg1);
    void on_checkBox_3_stateChanged(int arg1);
    void on_checkBox_4_stateChanged(int arg1);
    void on_checkBox_PP_stateChanged(int arg1);
    void on_checkBox_L_stateChanged(int arg1);
    void on_pushButton_clicked();
    void updataTermo();
    void updateTime();

private:
    Ui::Widget *ui;
    QString text;
    useE154 *agrekola;
    StartMeasurment *startWin;
    QTimer dataTimer, plotTimer, TDTimer, *currenttime;
    QDateTime dt;
    QCustomPlot *customPlot1;
    QCustomPlot *customPlot2;
    QCustomPlot *customPlot3;
    QCustomPlot *customPlot4;

    bool data;
    QVector<double> x;
    QVector<double> y1, y2, y3, y4;

    QString path;
    QFile file;
    QTextStream out;
};

#endif // WIDGET_H
