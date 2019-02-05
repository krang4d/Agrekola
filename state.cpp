#include "state.h"

State::State(QObject *parent) : QObject(parent)
{
    index = 0;
}

State::~State()
{

}

Mode_ID State::current()
{
    return state.at(index);
}

Mode_ID State::next()
{
    index++;
    return state.at(index);
}

void State::reset()
{
    index = 0;
}

StateAgr1::StateAgr1()
{
    State::state = { BTPTestAgr1_ID , TestAgr1_ID };
}

StateAgr1::~StateAgr1()
{

}

State *StateBuilder::getStateAgr1()
{
    return new StateAgr1;
}
