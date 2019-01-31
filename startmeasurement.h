#ifndef STARTMEASUREMENT_H
#define STARTMEASUREMENT_H

#include <QDialog>
#include <QString>
#include <QCheckBox>
#include <QMessageBox>
#include "savefiles.h"
#include "globalvalue.h"

namespace Ui {
class StartMeasurement;
}

class StartMeasurement : public QDialog
{
    Q_OBJECT

public:
    explicit StartMeasurement(QDialog *parent = 0);
    ~StartMeasurement();

    bool isCancel();
    bool isSingle();
    bool isChannel(int = 0);
    void setChannels(bool ch1, bool ch2, bool ch3, bool ch4);

    Mode_ID getModeID() const;
    void setModeID(const Mode_ID &value);

    void setProbe(bool is_single = true);

    QString getNum(const int ch);
    void setNum(const int ch, const QString num);

    int getTime();
    void setTime(int);

    int getTimeIncube(int = 1);
    void setTimeIncube(int incube_number, int time_s);

    QString getStringStatus();

    void saveData();
    void openData();

    int num;

public slots:
    void on_checkBox_ch1_stateChanged(int arg1);
    void on_checkBox_ch2_stateChanged(int arg1);
    void on_checkBox_ch3_stateChanged(int arg1);
    void on_checkBox_ch4_stateChanged(int arg1);
    void on_radioButton_single_toggled(bool checked);
    void on_pushButton_next_clicked();
    inline void setCheckState2(int i) {
        //QMessageBox::information(0, "StartMeasurment", QString("setCheckState2(%1)").arg(i));
        if(i == 0)
            channel_2 = false;
        else channel_2 = true;
    }
    inline void setCheckState4(int i) {
        if(i == 0)
            channel_4 = false;
        else channel_4 = true;
    }
    //  void on_pushButton_cancel_clicked();

signals:
    startMeasurment(StartMeasurement*);

private slots:
    void on_comboBox_inductor_currentIndexChanged(const QString &arg1);

private:
    Ui::StartMeasurement *ui;
    SaveFiles file;
    QStringList param;
    bool cancel;
    bool single;       //пробы одиночные?
    bool channel_1, channel_2, channel_3, channel_4;
    QString num_1, num_2, num_3, num_4;
    int time;           //время записи
    int time_incube, time_incube_2; //время инкубации
    Mode_ID modeID;
};

#endif // STARTMEASUREMENT_H
