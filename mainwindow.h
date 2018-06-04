#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widget.h"
#include "choisedialog.h"
#include "measurement.h"
#include "viewgraph.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Widget *cw;
    ChoiseDialog *ch;
    Measurement *m;
    ViewGraph *vg;
};

#endif // MAINWINDOW_H
