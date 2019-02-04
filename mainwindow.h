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
    void setupThread();

    Widget *centerWidget;
private:
    bool eventFilter(QObject *watched, QEvent *event);

public slots:
//    void getOTP();
//    void getBTP();

private slots:
    void on_menu_triggered();
    void on_plots_triggered();
    void on_action_triggered();
    void on_action_propety_triggered();

signals:
    btp_done();
    otp_done();

private:
    Ui::MainWindow *ui;
    useE154 *agrekola;
    ChoiseDialog *ch;

    friend class ChoiseDialog;
};

#endif // MAINWINDOW_H
