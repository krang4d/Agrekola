#ifndef VIEWPLOT_H
#define VIEWPLOT_H

#include <QWidget>

namespace Ui {
class ViewPlot;
}

class ViewPlot : public QWidget
{
    Q_OBJECT

public:
    explicit ViewPlot(QWidget *parent = 0);
    ~ViewPlot();

private slots:
    void on_pushButton_back_clicked();

private:
    Ui::ViewPlot *ui;
    QWidget *p;
};

#endif // VIEWPLOT_H
