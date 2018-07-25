#ifndef CHOISEDIALOG_H
#define CHOISEDIALOG_H

#include <QDialog>
#include <QTimer>

//dialog include
#include "agr1.h"
#include "agr2.h"
#include "ko1.h"
#include "ko2.h"
#include "ko3.h"
#include "ko4.h"
#include "ko5.h"
#include "testkoagr.h"
#include "widget.h"
#include "mainwindow.h"
#include "useE154.h"
#include"viewplot.h"

class MainWindow;

namespace Ui {
class ChoiseDialog;
}

class ChoiseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChoiseDialog(QDialog *parent = 0);
    int getTypeOfWidget() const;
    ~ChoiseDialog();

private slots:
    void startMeasurement();
    void calibration();
    void on_agr1Button_clicked();
    void on_agr2Button_clicked();
    void on_ko1Button_clicked();
    void on_ko2Button_clicked();
    void on_ko3Button_clicked();
    void on_ko4Button_clicked();
    void on_ko5Button_clicked();
    void on_testButton_clicked();
    void on_viewPlotsButton_clicked();

private:

    Ui::ChoiseDialog *ui;
};

#endif // CHOISEDIALOG_H
