#ifndef ITOOLS_H
#define ITOOLS_H

class ITools
{
public:
    ITools() = default;
    virtual ~ITools()  {}
    virtual double getSTART_DX1() const = 0;
    virtual void setSTART_DX1(double value) = 0;

    virtual double getSTART_DX2() const = 0;
    virtual void setSTART_DX2(double value) = 0;

    virtual double getSTART_DX3() const = 0;
    virtual void setSTART_DX3(double value) = 0;

    virtual double getSTART_DX4() const = 0;
    virtual void setSTART_DX4(double value) = 0;

    virtual double getSTOP_DX1() const = 0;
    virtual void setSTOP_DX1(double value) = 0;

    virtual double getSTOP_DX2() const = 0;
    virtual void setSTOP_DX2(double value) = 0;

    virtual double getSTOP_DX3() const = 0;
    virtual void setSTOP_DX3(double value) = 0;

    virtual double getSTOP_DX4() const = 0;
    virtual void setSTOP_DX4(double value) = 0;

    virtual double getMIN() const = 0;
    virtual void setMIN(double value) = 0;

    virtual double getMAX() const = 0;
    virtual void setMAX(double value) = 0;

    virtual double getMIX() const = 0;
    virtual void setMIX(double value) = 0;
};

#endif // ITOOLS_H
