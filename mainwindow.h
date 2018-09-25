#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "choisedialog.h"
#include "widget.h"
#include "useE154.h"
#include "viewplot.h"
//#include "startmeasurment.h"

class ChoiseDialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void newShow(StartMeasurment*sw);
    void setupThread();
    void getOTP();
    void getBTP();

private:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_menu_triggered();
    void on_plots_triggered();

signals:
    btp_done();

private:
    Ui::MainWindow *ui;
    useE154 *agrekola;
    Widget *centerWidget;
    ChoiseDialog *ch;
};

#endif // MAINWINDOW_H
