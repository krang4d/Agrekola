#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "choisedialog.h"
#include "measurement.h"
#include "viewgraph.h"
#include "choisedialog.h"
#include "startmeasurment.h"

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
    void on_action_menu_triggered();

private:
    Ui::MainWindow *ui;
    Measurement *m;
    StartMeasurment *st;
    ChoiseDialog *ch;
};

#endif // MAINWINDOW_H
