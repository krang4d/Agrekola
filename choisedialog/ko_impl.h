#ifndef KO_IMPL_H
#define KO_IMPL_H

class QString;
class QDate;
class QTime;

class Ko_impl
{
public:
    enum SaveTo {Test_ID, Calib_ID };
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void setDate(QDate , SaveTo) = 0;
    virtual void setTime(QTime, SaveTo) = 0;

    virtual QString t_print() = 0;
    virtual void setT1(double) = 0;
    virtual void setT2(double) = 0;
    virtual void setT3(double) = 0;
    virtual void setT4(double) = 0;

    virtual QString c_print() = 0;
    virtual void calibrationData1Come(double) = 0;
    virtual void calibrationData2Come(double) = 0;
    virtual void calibrationData3Come(double) = 0;
    virtual void calibrationData4Come(double) = 0;
};

#endif // KO_IMPL_H
