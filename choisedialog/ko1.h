#ifndef KO1_H
#define KO1_H

#include <QWidget>
#include "savefiles.h"
#include "startmeasurement.h"
#include "globalvalue.h"
#include "ko_impl.h"

namespace Ui {
class Ko1;
}

class Ko1 : public QWidget, public Ko_impl
{
    Q_OBJECT

public:
    explicit Ko1(QWidget *parent = 0);
    void setTab(int);
    ~Ko1();

private slots:
    void on_pushButton_test_clicked();
    void on_radioButton_testSingle_toggled(bool checked);

    void on_checkBox_testCh1_toggled(bool checked);
    void on_checkBox_testCh2_toggled(bool checked);
    void on_checkBox_testCh3_toggled(bool checked);
    void on_checkBox_testCh4_toggled(bool checked);

    void on_lineEdit_testCh1_textChanged(const QString &arg1);
    void on_lineEdit_testCh3_textChanged(const QString &arg1);

    // Ko_impl interface
public slots:
    void open();
    void close();
    void setDate(QDate, SaveTo) override;
    void setTime(QTime, SaveTo) override;

    QString t_print() override;
    void setT1(double value) override;
    void setT2(double value) override;
    void setT3(double value) override;
    void setT4(double value) override;

    QString c_print() override { return 0; }
    void calibrationData1Come(double) override {}
    void calibrationData2Come(double) override {}
    void calibrationData3Come(double) override {}
    void calibrationData4Come(double) override {}

signals:
    void measurement(StartMeasurement*);

private:
    Ui::Ko1 *ui;
    TestKo1 *t_ko1;
    CalibrationKo1 *c_ko1;
};

class StartTestKo1 : public StartMeasurement
{
    Q_OBJECT
public:
    StartTestKo1() = delete;
    static StartMeasurement* getStart(Test* t_ko1);
};

#endif // KO1_H
