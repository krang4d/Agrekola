#ifndef STARTMEASURMENT_H
#define STARTMEASURMENT_H

#include <QDialog>

namespace Ui {
class StartMeasurment;
}

class StartMeasurment : public QDialog
{
    Q_OBJECT

public:
    explicit StartMeasurment(QDialog *parent = 0);
    ~StartMeasurment();
    bool isCancel();
    bool isSingle();
    bool isChannel_1();
    bool isChannel_2();
    bool isChannel_3();
    bool isChannel_4();

    int getNum_1();
    int getNum_2();
    int getNum_3();
    int getNum_4();
    int getTime();
    QString getStringStatus();

public slots:
    void on_checkBox_ch1_stateChanged(int arg1);
    void on_checkBox_ch2_stateChanged(int arg1);
    void on_checkBox_ch3_stateChanged(int arg1);
    void on_checkBox_ch4_stateChanged(int arg1);
    void on_radioButton_single_toggled(bool checked);
    void on_pushButton_next_clicked();
    void on_pushButton_cancel_clicked();

signals:
    startMeasurment();

private:
    Ui::StartMeasurment *ui;
    bool cancel;
    bool single;       //пробы одиночные?
    bool channel_1, channel_2, channel_3, channel_4;
    int num_1, num_2, num_3, num_4;
    int time;           //время записи
};

#endif // STARTMEASURMENT_H
