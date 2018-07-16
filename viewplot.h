#ifndef VIEWPLOT_H
#define VIEWPLOT_H

#include <QWidget>
#include <QDebug>
#include <QTableWidget>

#include "savefiles.h"
#include "QCustomPlot/qcustomplot.h"

namespace Ui {
class ViewPlot;
}

class ViewPlot : public QWidget
{
    Q_OBJECT

public:
    explicit ViewPlot(QWidget *parent = 0);
    ~ViewPlot();
    void initTable();
    void initPlot();
    void addData();
    QList<double> v1, v2, v3, v4, t;

private slots:
    void on_pushButton_back_clicked();
    void on_pushButton_open_clicked();
    void on_pushButton_view_clicked();

    void on_checkBox_1_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_4_stateChanged(int arg1);

private:
    Ui::ViewPlot *ui;
    QTableWidget *tb;
    QCustomPlot *customPlot;

};

#endif // VIEWPLOT_H
