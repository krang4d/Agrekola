#ifndef ISCENARIO_H
#define ISCENARIO_H


class IScenario
{
public:
    //IScenario(); // = delete
    virtual void getBTP() = 0;
    virtual void getOTP() = 0;
    virtual void onMixChls(bool) = 0;
    virtual void onMixPP(bool) = 0;
    virtual void onLazer(bool) = 0;
    virtual void incubation1() = 0;
    virtual void incubation2() = 0;
    virtual void selectInductor() =0;
    virtual void finish() = 0;

    virtual void agr() = 0;
    virtual void ko() = 0;
    virtual void calc() = 0;
    virtual void write() = 0;
};

#endif // ISCENARIO_H
