#ifndef STATE_H
#define STATE_H

#include <QObject>
#include <globalvalue.h>

class State : public QObject
{
protected:
    QVector<Mode_ID> state;
    QMap<int, QString> state_map;
    int index;

public:
    explicit State(QObject *parent = 0);
    virtual ~State() {}
    Mode_ID current();
    Mode_ID next();
    void reset();
    virtual QString getMessage();
};

class StateKo1 : public State
{
public:
    explicit StateKo1();
    QString getMessage() override;
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
    QString getMessage() override;
};

class StateAgr2 : public State
{
public:
    explicit StateAgr2();
};

class StateBuilder
{
public:
    static State *getState(Mode_ID mode);
protected:
    static State *getStateAgr1();
    static State *getStateAgr2();
    static State *getStateKo1();
    static State *getStateKo2();
    static State *getStateKo3();
    static State *getStateKo4();
    static State *getStateKo5();
};

#endif // STATE_H
