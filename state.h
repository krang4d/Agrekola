#ifndef STATE_H
#define STATE_H

#include <QObject>
#include <QDebug>
#include <QList>
#include <QPair>
#include <globalvalue.h>

//Состония Widget
enum State_ID{
    MotorON_ID,     //вкл. моторов
    MotorOFF_ID,    //выкл. моторов
    LaserON_ID,     //вкл. лазеров
    LaserOFF_ID,    //выкл. лазеров
    Ko_ID,          //измерение в режиме коаг
    Agr_ID,         //измерение в режиме агр
    Avg_ID,         //определение среднего урвоня
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
    explicit State(QObject *parent = 0);
    virtual ~State();

    void insertState(State_ID, QString, int level = 0);
    State_ID current();
    int next();
    bool hasNext();
    void reset();
    QString getMessage();
    int getLevel();

signals:
    void stateChanged();

private:
    //QVector<State_ID> state;
    QList<QPair<State_ID, QString>> state_map;
    QList<QPair<State_ID, QString>>::iterator it;
    int level;
    //int index;
};

class StateKo1 : public State
{
public:
    explicit StateKo1();
};

class StateKo2 : public State
{
public:
    explicit StateKo2();
};

class StateKo3 : public State
{
public:
    explicit StateKo3();
};

class StateKo4 : public State
{
public:
    explicit StateKo4();
};

class StateKo5 : public State
{
public:
    explicit StateKo5();
};

class StateAgr1 : public State
{
public:
    explicit StateAgr1();
};

class StateAgr2 : public State
{
public:
    explicit StateAgr2();
};

class StateCalKo1 : public State
{
public:
    explicit StateCalKo1();
};

class StateCalKo2 : public State
{
public:
    explicit StateCalKo2();
};

class StateCalKo3 : public State
{
public:
    explicit StateCalKo3();
};

class StateCalKo4 : public State
{
public:
    explicit StateCalKo4();
};

class StateCalKo5 : public State
{
public:
    explicit StateCalKo5();
};

class StateCalAgr1 : public State
{
public:
    explicit StateCalAgr1();
};

class StateCalAgr2 : public State
{
public:
    explicit StateCalAgr2();
};

class StateBuilder
{
public:
    static State *getState(Mode_ID mode);
protected:
    static State *getStateTestAgr1();
    static State *getStateTestAgr2();
    static State *getStateTestKo1();
    static State *getStateTestKo2();
    static State *getStateTestKo3();
    static State *getStateTestKo4();
    static State *getStateTestKo5();

    static State *getStateCalAgr1();
    static State *getStateCalAgr2();
    static State *getStateCalKo1();
    static State *getStateCalKo2();
    static State *getStateCalKo3();
    static State *getStateCalKo4();
    static State *getStateCalKo5();
};

#endif // STATE_H
