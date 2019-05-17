#ifndef ISTARTWIN_H
#define ISTARTWIN_H

class QString;
class Test;
class Calibration;
class Widget::Channel_ID;
class Widget::Mode_ID;

class IStartWin
{
public:
    //virtual void setModeID(const Mode_ID &value) = 0;
    virtual Mode_ID getModeID() const = 0;

    //virtual void setChannels(bool ch1, bool ch2, bool ch3, bool ch4) = 0;
    virtual bool isChannel(Widget::Channel_ID);

    //virtual void setNum(const int ch, const QString num) = 0;
    virtual QString getNum(const int ch) = 0;

    //virtual void setBtp_time(double value) = 0;
    virtual double getBtp_time() const = 0;

    //void setOtp_time(double value) = 0;
    double getOtp_time() const = 0;

    //virtual void setTimeWrite(double s) = 0;
    virtual double getTimeWrite() = 0;

    //virtual double setTimeIncube(int incube_number, double time_s) = 0;
    virtual double getTimeIncube(int = 1) = 0;

    //virtual void setCalib(Calibration *value) = 0;
    virtual Calibration *getCalib() const = 0;

    //virtual void setTest(Test *value) = 0;
    virtual Test *getTest() const = 0;
};
#endif // ISTARTWIN_H
