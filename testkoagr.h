#ifndef TESTKOAGR_H
#define TESTKOAGR_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include "testkoagr.h"
#include "useE154.h"

namespace Ui {
class TestKoAgr;
}

class TestKoAgr : public QDialog
{
    Q_OBJECT

public:
    explicit TestKoAgr(IuseE154 *e, QWidget *parent = 0);
    ~TestKoAgr();
    void setup();

private slots:
    void on_pushButton_onLaser_clicked();
    void on_pushButton_offLaser_clicked();
    void on_pushButton_onMix1_clicked();
    void on_pushButton_offMix1_clicked();
    void on_pushButton_onMix2_clicked();
    void on_pushButton_offMix2_clicked();
    void on_pushButton_onMix3_clicked();
    void on_pushButton_offMix4_clicked();
    void on_pushButton_offMix3_clicked();
    void on_pushButton_onMix4_clicked();
    void on_pushButton_onMixPP_clicked();
    void on_pushButton_offMixPP_clicked();
    void on_pushButton_poll_clicked();
    void on_pushButton_back_clicked();

private:
    Ui::TestKoAgr *ui;
    IuseE154 *e154;
};

#endif // TESTKOAGR_H

