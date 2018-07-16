#ifndef VIEWPLOT_H
#define VIEWPLOT_H

#include <QWidget>
#include <QTableWidget>

#include "savefiles.h"

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
    void addData();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_print_clicked();

    void on_pushButton_view_clicked();

private:
    Ui::ViewPlot *ui;
    QTableWidget *tb;
    QVector<double> v1, v2, v3, v4, t;
};

#endif // VIEWPLOT_H
