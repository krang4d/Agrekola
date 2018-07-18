#ifndef VIEWPLOT_H
#define VIEWPLOT_H

#include <QDialog>
#include <QDebug>
#include <QTableWidget>

#include "savefiles.h"
#include "QCustomPlot/qcustomplot.h"

namespace Ui {
class ViewPlot;
}

class ViewPlot : public QDialog
{
    Q_OBJECT

public:
    explicit ViewPlot(QDialog *parent = 0);
    ~ViewPlot();
    void initTable();
    void initPlots();
    void rePlot();
    void addData();
    QList<double> v1, v2, v3, v4, t;
    QStringList param;

private slots:
    void on_pushButton_back_clicked();
    void on_pushButton_open_clicked();

    void on_checkBox_1_stateChanged(int arg1);
    void on_checkBox_2_stateChanged(int arg1);
    void on_checkBox_3_stateChanged(int arg1);
    void on_checkBox_4_stateChanged(int arg1);
    void on_pushButton_print_clicked();

    void selectionChanged();
    void mousePress();
    void mouseWheel();
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);

private:
    Ui::ViewPlot *ui;
    QTableWidget *tb;
    QCustomPlot *customPlot;
};

#endif // VIEWPLOT_H
