#ifndef STATE_H
#define STATE_H

#include <QObject>
#include <globalvalue.h>

class State : public QObject
{
    Q_OBJECT
protected:
    QVector<State_ID> state;
    QMap<int, QString> state_map;
    int index;

public:
    explicit State(QObject *parent = 0);
    virtual ~State();
    State_ID current();
    State_ID next();
    bool hasNext();
    void reset();
    virtual QString getMessage();
signals:
    void stateChanged();
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
    QString getMessage() override;
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
