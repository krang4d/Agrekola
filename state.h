#ifndef STATE_H
#define STATE_H

#include <QObject>
#include <QDebug>
#include <QList>
#include <QPair>
#include <globalvalue.h>
#include <iscenario.h>
#include <impulewaiter.h>

//Состония Widget
enum State_ID{
    MotorON_ID,     //вкл. моторов
    MotorOFF_ID,    //выкл. моторов
    LaserON_ID,     //вкл. лазеров
    LaserOFF_ID,    //выкл. лазеров
    Ko_ID,          //измерение в режиме коаг
    Agr_ID,         //измерение в режиме агр
//      Avg_ID,         //определение среднего урвоня
    Btp_ID,         //определение БТП урвоня
    Otp_ID,         //определение ОТП урвоня
    Calc_ID,        //расчет параметров
    Write_ID,        //запись данных в файл
    Incubation1_ID, //инкубация 1
    Incubation2_ID,  //инкубация 2
    SelectInductor_ID, //выбор индуктора
    End_ID          //вывод результатов
};

class State : public QObject
{
    Q_OBJECT

public:
    explicit State(IScenario *, QObject *parent = 0);
    virtual ~State();

    void insertState(State_ID, QString, int level = 0);
    State_ID current();
    void next();
    bool hasNext();
    void reset();
    QString getMessage();
    int getLevel();

    void doState();
    void doScenario();

signals:
    void stateChanged();

private:
    //QVector<State_ID> state;
    IScenario *scena;
    QList<QPair<State_ID, QString>> state_list;
    QList<QPair<State_ID, QString>>::iterator it;
    int level;

    //int index;
};

class StateKo1 : public State
{
    Q_OBJECT
public:
    explicit StateKo1(IScenario *o);
    void doScenario();
};

class StateKo2 : public State
{
    Q_OBJECT
public:
    explicit StateKo2(IScenario *o);
};

class StateKo3 : public State
{
    Q_OBJECT
public:
    explicit StateKo3(IScenario *o);
};

class StateKo4 : public State
{
    Q_OBJECT
public:
    explicit StateKo4(IScenario *o);
};

class StateKo5 : public State
{
    Q_OBJECT
public:
    explicit StateKo5(IScenario *o);
};

class StateAgr1 : public State
{
    Q_OBJECT
public:
    explicit StateAgr1(IScenario *o);
};

class StateAgr2 : public State
{
    Q_OBJECT
public:
    explicit StateAgr2(IScenario *o);
};

class StateCalKo1 : public State
{
    Q_OBJECT
public:
    explicit StateCalKo1(IScenario *o);
};

class StateCalKo2 : public State
{
    Q_OBJECT
public:
    explicit StateCalKo2(IScenario *o);
};

class StateCalKo3 : public State
{
    Q_OBJECT
public:
    explicit StateCalKo3(IScenario *o);
};

class StateCalKo4 : public State
{
    Q_OBJECT
public:
    explicit StateCalKo4(IScenario *o);
};

class StateCalKo5 : public State
{
    Q_OBJECT
public:
    explicit StateCalKo5(IScenario *o);
};

class StateCalAgr1 : public State
{
    Q_OBJECT
public:
    explicit StateCalAgr1(IScenario *o);
};

class StateCalAgr2 : public State
{
    Q_OBJECT
public:
    explicit StateCalAgr2(IScenario *o);
};

class StateBuilder
{
public:
    static State *getState(Mode_ID mode, IScenario *o);
protected:
    static State *getStateTestAgr1(IScenario *o);
    static State *getStateTestAgr2(IScenario *o);
    static State *getStateTestKo1(IScenario *o);
    static State *getStateTestKo2(IScenario *o);
    static State *getStateTestKo3(IScenario *o);
    static State *getStateTestKo4(IScenario *o);
    static State *getStateTestKo5(IScenario *o);

    static State *getStateCalAgr1(IScenario *o);
    static State *getStateCalAgr2(IScenario *o);
    static State *getStateCalKo1(IScenario *o);
    static State *getStateCalKo2(IScenario *o);
    static State *getStateCalKo3(IScenario *o);
    static State *getStateCalKo4(IScenario *o);
    static State *getStateCalKo5(IScenario *o);
};

#endif // STATE_H
