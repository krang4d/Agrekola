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

    void newShow();

private slots:
    void on_action_start_triggered();

private:
    Ui::MainWindow *ui;
    Measurement *m;
};

#endif // MAINWINDOW_H
