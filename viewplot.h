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

private:
    Ui::ViewPlot *ui;
};

#endif // VIEWPLOT_H
