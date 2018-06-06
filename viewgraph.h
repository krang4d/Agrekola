#ifndef VIEWGRAPH_H
#define VIEWGRAPH_H

#include <QWidget>

namespace Ui {
class ViewGraph;
}

class ViewGraph : public QWidget
{
    Q_OBJECT

public:
    explicit ViewGraph(QWidget *parent = 0);
    ~ViewGraph();

private slots:


    void on_pushButton_back_clicked();

private:
    Ui::ViewGraph *ui;
};

#endif // VIEWGRAPH_H
