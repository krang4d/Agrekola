#ifndef STATE_H
#define STATE_H

#include <QObject>
#include <globalvalue.h>

class State : public QObject
{
    Q_OBJECT

protected:
    QVector<Mode_ID> state;
    int index;

public:
    explicit State(QObject *parent = 0);
    virtual ~State();
    Mode_ID current();
    Mode_ID next();
    void reset();

signals:

public slots:
};

class StateAgr1 : public State
{
    Q_OBJECT

public:
    explicit StateAgr1();
    ~StateAgr1();
};

class StateBuilder
{
public:
    static State *getStateAgr1();
};

#endif // STATE_H
