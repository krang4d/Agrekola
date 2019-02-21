#include "state.h"

State::State(QObject *parent) : QObject(parent)
{
    index = 0;
    state = { Test_ID };
    state_map = {
        { 0, QString("Test_ID") }
    };
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

QString State::getMessage()
{
    return state_map.take(index);
}

StateKo1::StateKo1()
{
    State::state = { TestKo1_ID };
    State::state_map = {
        { 0,  QString("«Установите в каналы кюветы с пробами»") }
    };
}

StateKo2::StateKo2()
{
    State::state = { Incubation1_ID, TestKo2_ID };
}

StateKo3::StateKo3()
{
    State::state = { Incubation1_ID, TestKo3_ID };
}

StateKo4::StateKo4()
{
    State::state = { Incubation1_ID, TestKo4_ID };
}

StateKo5::StateKo5()
{
    State::state = { Incubation1_ID, TestKo5_ID };
}

StateAgr1::StateAgr1()
{
    State::state = { Incubation1_ID, BTPTestAgr1_ID ,Incubation1_ID, OTPTestAgr1_ID, TestAgr1_ID };
    State::state_map = {
        { 0,  QString("Установите пробы с БТП в рабочие  каналы") },
        { 1,  QString("Фиксация «100%» уровней") },
        { 2,  QString("Установите пробы с ОТП в рабочие  каналы") },
        { 3,  QString("Фиксация «0%» уровней") }
    };
}

QString StateAgr1::getMessage()
{

    return state_map.take(index);
//    const Mode_ID localAt = state.at(index);
//    switch ( index  ) {
//    case BTPTestAgr1_ID:
//        return QString("Фиксация «100%» уровней");
//    case OTPTestAgr1_ID:
//        return QString("Фиксация «0%» уровней");
//    case Incubation1_ID:
//        return QString("Установите пробы с БТП в рабочие  каналы");
//    case Incubation2_ID:
//        return QString("Установите пробы с ОТП в рабочие  каналы");
//    default:
//        return "default message";
//    }
}

StateAgr2::StateAgr2()
{
    State::state = { TestAgr2_ID };
}

State *StateBuilder::getStateKo1()
{
    return new StateKo1;
}

State *StateBuilder::getStateKo2()
{
    return new StateKo2;
}

State *StateBuilder::getStateKo3()
{
    return new StateKo3;
}

State *StateBuilder::getStateKo4()
{
    return new StateKo4;
}

State *StateBuilder::getStateKo5()
{
    return new StateKo5;
}

State *StateBuilder::getStateAgr1()
{
    return new StateAgr1;
}

State *StateBuilder::getStateAgr2()
{
    return new StateAgr2;
}

State* StateBuilder::getState(Mode_ID mode)
{
    State* state;
    switch (mode) {
    case TestAgr1_ID:
        state = getStateAgr1();
        break;
    case TestAgr2_ID:
        state = getStateAgr2();
        break;
    case TestKo1_ID:
        state = getStateKo1();
        break;
    case TestKo2_ID:
        state = getStateKo2();
        break;
    case TestKo3_ID:
        state = getStateKo3();
        break;
    case TestKo4_ID:
        state = getStateKo4();
        break;
    case TestKo5_ID:
        state = getStateKo5();
        break;
    default:
        state = new State();
        break;
    }
    return state;
}
