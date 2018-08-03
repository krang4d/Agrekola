#ifndef VIEWPLOT_H
#define VIEWPLOT_H

#include <QDialog>
#include <QDebug>
#include <QTableWidget>

#include "savefiles.h"
#include "QCustomPlot/qcustomplot.h"
#include "calculatedata.h"

namespace Ui {
class ViewPlot;
}

class ViewPlot : public QDialog
{
    Q_OBJECT

public:
    explicit ViewPlot(QWidget *parent = 0);
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
    void on_pushButton_select_clicked();
    void on_pushButton_print_clicked();
    void on_pushButton_calc_clicked();

    void selectionChanged();
    void mousePress();
    void mouseWheel();
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);

    void calcSelected(int ngraph, QCPDataSelection selection);
    void hasGraph0Selected(QCPDataSelection);
    void hasGraph1Selected(QCPDataSelection);
    void hasGraph2Selected(QCPDataSelection);
    void hasGraph3Selected(QCPDataSelection);
    void hasSelected(QCP::SelectionType);
    //void hasSelected(bool);
    void hasSelectedRect(QRect,QMouseEvent*);

private:
    Ui::ViewPlot *ui;
    QTableWidget *tb;
    QCustomPlot *customPlot;
};

#endif // VIEWPLOT_H
