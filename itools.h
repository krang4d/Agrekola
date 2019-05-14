#ifndef ITOOLS_H
#define ITOOLS_H

class ITools
{
public:
    //ITools() = delete;
    virtual double getSTART_DX() const = 0;
    virtual void setSTART_DX(double value) = 0;

    virtual double getSTOP_DX() const = 0;
    virtual void setSTOP_DX(double value) = 0;

    virtual double getMIN() const = 0;
    virtual void setMIN(double value) = 0;

    virtual double getMAX() const = 0;
    virtual void setMAX(double value) = 0;

    virtual double getMIX() const = 0;
    virtual void setMIX(double value) = 0;
};

#endif // ITOOLS_H
