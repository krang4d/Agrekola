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
    bool isChannel(Channel_ID = ChannelAll_ID);
    void setChannels(bool ch1, bool ch2, bool ch3, bool ch4);

    Mode_ID getModeID() const;
    void setModeID(const Mode_ID &value);

    void setProbe(bool is_single = true);

    QString getNum(const int ch);
    void setNum(const int ch, const QString num);

    double getTimeWrite();
    void setTimeWrite(double s);

    double getTimeIncube(int = 1);
    double setTimeIncube(int incube_number, double time_s);

    QString getStringStatus();

    void saveData();
    void openData();

    int num;

    QObject *getObj() const;
    void setObj(QObject *value);

    QWidget *getWgt() const;
    void setWgt(QWidget *value);

    double getBtp_time() const;
    void setBtp_time(double value);

    double getOtp_time() const;
    void setOtp_time(double value);

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
    double time;                        //время записи
    double time_incube, time_incube_2, btp_time, otp_time;  //время инкубации
    Mode_ID modeID;
    QWidget *wgt;
};

#endif // STARTMEASUREMENT_H
