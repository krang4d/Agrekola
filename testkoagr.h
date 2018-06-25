#ifndef TESTKOAGR_H
#define TESTKOAGR_H

#include <QDialog>

namespace Ui {
class TestKoAgr;
}

class TestKoAgr : public QDialog
{
    Q_OBJECT

public:
    explicit TestKoAgr(QWidget *parent = 0);
    ~TestKoAgr();

private slots:

    void on_pushButton_back_clicked();

    void on_pushButton_onlaser_clicked();

    void on_pushButton_offlaser_clicked();

    void on_pushButton_onmotor_clicked();

    void on_pushButton_offmotor_clicked();

    void on_pushButton_poll_clicked();

private:
    Ui::TestKoAgr *ui;
};

#endif // TESTKOAGR_H
