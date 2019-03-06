#ifndef KO1_H
#define KO1_H

#include <QWidget>
#include "savefiles.h"
#include "startmeasurement.h"
#include "globalvalue.h"

namespace Ui {
class Ko1;
}

class Ko1 : public QWidget
{
    Q_OBJECT

public:
    explicit Ko1(QWidget *parent = 0);
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

signals:
    void measurement(StartMeasurement*);

private:
    Ui::Ko1 *ui;
    TestKo1 t_ko1;
    CalibrationKo1 c_ko1;
};

class StartTestKo1 : public StartMeasurement
{
    Q_OBJECT
public:
    StartTestKo1() = delete;
    static StartMeasurement* getStart(Test* t_ko1);
};

#endif // KO1_H
