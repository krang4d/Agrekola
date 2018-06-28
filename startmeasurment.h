#ifndef STARTMEASURMENT_H
#define STARTMEASURMENT_H

#include <QWidget>

namespace Ui {
class StartMeasurment;
}

class StartMeasurment : public QWidget
{
    Q_OBJECT

public:
    explicit StartMeasurment(QWidget *parent = 0);
    ~StartMeasurment();

    bool isSingle();
    bool isChannel_1();
    bool isChannel_2();
    bool isChannel_3();
    bool isChannel_4();

    int getNum_1();
    int getNum_2();
    int getNum_3();
    int getNum_4();

    double getFreq();
    int getTime();

private slots:
    void on_checkBox_ch1_stateChanged(int arg1);
    void on_checkBox_ch2_stateChanged(int arg1);
    void on_checkBox_ch3_stateChanged(int arg1);
    void on_checkBox_ch4_stateChanged(int arg1);
    void on_pushButton_next_clicked();
    void on_radioButton_single_toggled(bool checked);
    void on_pushButton_cancel_clicked();

signals:
    startMeasurment();

private:
    bool single;       //пробы одиночные?
    bool channel_1, channel_2, channel_3, channel_4;
    int num_1, num_2, num_3, num_4;
    double freq;        //интервал между точками
    int time;           //время записи

    Ui::StartMeasurment *ui;
};

#endif // STARTMEASURMENT_H
