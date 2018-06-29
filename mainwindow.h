#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "choisedialog.h"
#include "measurement.h"
#include "viewgraph.h"
#include "choisedialog.h"
#include "startmeasurment.h"
#include "widget.h"

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

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::MainWindow *ui;
    Widget *centerWidget;
    StartMeasurment *st;
    ChoiseDialog *ch;
};

#endif // MAINWINDOW_H
