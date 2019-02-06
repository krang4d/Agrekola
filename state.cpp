#include "state.h"

State::State(QObject *parent) : QObject(parent)
{
    index = 0;
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
    const Mode_ID localAt = state.at(index);
    switch ( localAt  ) {
    case Test_ID:
        return QString("Test_ID");
    case TestAgr1_ID:
        return QString("TestAgr1_ID");
    case TestAgr2_ID:
        return QString("TestAgr2_ID");
    case TestKo1_ID:
        return QString("TestKo1_ID");
    case TestKo2_ID:
        return QString("TestKo2_ID");
    case TestKo3_ID:
        return QString("TestKo3_ID");
    case TestKo4_ID:
        return QString("TestKo4_ID");
    case TestKo5_ID:
        return QString("TestKo5_ID");
    case Level_ID:
        return QString("Level_ID");
    case CalibAgr1_ID:
        return QString("CalibAgr1_ID");
    case CalibAgr2_ID:
        return QString("CalibAgr2_ID");
    case CalibKo1_ID:
        return QString("CalibKo1_ID");
    case CalibKo2_ID:
        return QString("CalibKo2_ID");
    case CalibKo3_ID:
        return QString("CalibKo3_ID");
    case CalibKo4_ID:
        return QString("CalibKo4_ID");
    case CalibKo5_ID:
        return QString("CalibKo5_ID");;
    case BTPTestAgr1_ID:
        return QString("BTPTestAgr1_ID");
    case BTPCalibAgr1_ID:
        return QString("BTPCalibAgr1_ID");
    case OTPTestAgr1_ID:
        return QString("OTPTestAgr1_ID");
    case OTPCalibAgr1_ID:
        return QString("OTPCalibAgr1_ID");
    case BTPTestAgr2_ID:
        return QString("BTPTestAgr2_ID");
    case BTPCalibAgr2_ID:
        return QString("BTPCalibAgr2_ID");
    case OTPCalibAgr2_ID:
        return QString("OTPCalibAgr2_ID");
    case Incubation1_ID:
        return QString("Incubation1_ID");
    case Incubation2_ID:
        return QString("Incubation2_ID");
    default:
        return "default message";
        break;
    }
    return "base class default message";
}

StateKo1::StateKo1()
{
    State::state = { TestKo1_ID };
}

QString StateKo1::getMessage()
{
    const Mode_ID localAt = state.at(index);
    switch ( localAt  ) {
    case TestKo1_ID:
        return QString("");
    default:
        return "default message";
        break;
    }
}

StateKo2::StateKo2()
{
    State::state = { TestKo2_ID };
}

StateKo3::StateKo3()
{
    State::state = { TestKo3_ID };
}

StateKo4::StateKo4()
{
    State::state = { TestKo4_ID };
}

StateKo5::StateKo5()
{
    State::state = { TestKo5_ID };
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
        break;
    }
    return state;
}
