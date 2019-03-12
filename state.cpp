#include "state.h"
#include "QmessageBox"

State::State(QObject *parent) : QObject(parent)
{
    index = 0;
    state_map = {
        { 0, QString("Base class state") }
    };
}

State::~State()
{

}

State_ID State::current()
{
    return state.at(index);
}

State_ID State::next()
{
    if( hasNext() ) {
        index++;
        emit stateChanged();
        return state.at(index);
    }
    else {
        QMessageBox::warning(0, "Errore", "State::Index is out of date!");
        return current();
    }
}

bool State::hasNext()
{
    if( 0 <= index && index + 1  < state.size() )
        return true;
    else return false;
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
    State::state = { Incubation1_ID, Ko_ID, Calc_ID, Incubation1_ID,  Ko_ID, Calc_ID };
//    State::state = { Incubation1_ID, Ko_ID, Incubation1_ID,  Ko_ID, Calc_ID };
    State::state_map = {
        { 0,  QString("Инкубация 1") },
        { 1,  QString("Измерение 1") },
        { 2,  QString("Расчет") },
        { 3,  QString("Инкубация 2") },
        { 4,  QString("Измерение 2") },
        { 5,  QString("Расчет") }
    };
}

StateKo2::StateKo2()
{
    State::state = { LaserON_ID, MotorON_ID, Incubation1_ID, Ko_ID, LaserOFF_ID, MotorOFF_ID, Calc_ID, Write_ID };
    State::state_map = {
        { 0,  QString("Включение лазеров") },
        { 1,  QString("Включение двигателей") },
        { 2,  QString("Инкубация") },
        { 3,  QString("Сбор данных") },
        { 4,  QString("Выключение лазеров") },
        { 5,  QString("Выключение двигателей") },
        { 6,  QString("Расчет") },
        { 7,  QString("Запись") }
    };
}

StateKo3::StateKo3()
{
    State::state = { LaserON_ID, MotorON_ID, Incubation1_ID, Ko_ID, LaserOFF_ID, MotorOFF_ID, Calc_ID, Write_ID };
    State::state_map = {
        { 0,  QString("Включение лазеров") },
        { 1,  QString("Включение двигателей") },
        { 2,  QString("Инкубация") },
        { 3,  QString("Сбор данных") },
        { 4,  QString("Выключение лазеров") },
        { 5,  QString("Выключение двигателей") },
        { 6,  QString("Расчет") },
        { 7,  QString("Запись") }
    };
}

StateKo4::StateKo4()
{
    State::state = { LaserON_ID, MotorON_ID, Incubation1_ID, Ko_ID, LaserOFF_ID, MotorOFF_ID, Calc_ID, Write_ID };
    State::state_map = {
        { 0,  QString("Включение лазеров") },
        { 1,  QString("Включение двигателей") },
        { 2,  QString("Инкубация") },
        { 3,  QString("Сбор данных") },
        { 4,  QString("Выключение лазеров") },
        { 5,  QString("Выключение двигателей") },
        { 6,  QString("Расчет") },
        { 7,  QString("Запись") }
    };
}

StateKo5::StateKo5()
{
    State::state = { LaserON_ID, MotorON_ID, Incubation1_ID, Ko_ID, LaserOFF_ID, MotorOFF_ID, Calc_ID, Write_ID };
    State::state_map = {
        { 0,  QString("Включение лазеров") },
        { 1,  QString("Включение двигателей") },
        { 2,  QString("Инкубация") },
        { 3,  QString("Сбор данных") },
        { 4,  QString("Выключение лазеров") },
        { 5,  QString("Выключение двигателей") },
        { 6,  QString("Расчет") },
        { 7,  QString("Запись") }
    };
}

StateAgr1::StateAgr1()
{
    State::state = { Incubation1_ID , Avg_ID ,Incubation1_ID, Avg_ID, Agr_ID };
    State::state_map = {
        { 0,  QString("Установите пробы с БТП в рабочие  каналы") },
        { 1,  QString("Фиксация «100%» уровней") },
        { 2,  QString("Установите пробы с ОТП в рабочие  каналы") },
        { 3,  QString("Фиксация «0%» уровней") }
    };
}

StateCalAgr2::StateCalAgr2()
{

}

StateCalKo1::StateCalKo1()
{

}

StateCalKo2::StateCalKo2()
{
    State::state = { LaserON_ID, MotorON_ID, Incubation1_ID, Ko_ID, MotorOFF_ID, LaserOFF_ID, Calc_ID };
    State::state_map = {
        { 0,  QString("Включение лазеров") },
        { 1,  QString("Включение двигателей") },
        { 2,  QString("Инкубация") },
        { 3,  QString("Сбор данных") },
        { 4,  QString("Выключение лазеров") },
        { 5,  QString("Выключение двигателей") },
        { 6,  QString("Расчет") }
    };
}

StateCalKo3::StateCalKo3()
{
    State::state = { LaserON_ID, MotorON_ID, Incubation1_ID, Ko_ID, Incubation1_ID, Ko_ID, MotorOFF_ID, LaserOFF_ID, Calc_ID };
    State::state_map = {
        { 0,  QString("Включение лазеров") },
        { 1,  QString("Включение двигателей") },
        { 2,  QString("Инкубация") },
        { 3,  QString("Сбор данных Канал 1,2 - 200%, Канал 3,4 - 100%") },
        { 4,  QString("Инкубация") },
        { 5,  QString("Сбор данных Канал 1,2 - 50%, Канал 3,4 - 25%") },
        { 6,  QString("Выключение лазеров") },
        { 7,  QString("Выключение двигателей") },
        { 8,  QString("Расчет") }
    };
}

StateCalKo4::StateCalKo4()
{
    State::state = { LaserON_ID, MotorON_ID, Incubation1_ID, Ko_ID, MotorOFF_ID, LaserOFF_ID, Calc_ID };
    State::state_map = {
        { 0,  QString("Включение лазеров") },
        { 1,  QString("Включение двигателей") },
        { 2,  QString("Инкубация") },
        { 3,  QString("Сбор данных") },
        { 4,  QString("Выключение лазеров") },
        { 5,  QString("Выключение двигателей") },
        { 6,  QString("Расчет") }
    };
}

StateCalKo5::StateCalKo5()
{
    State::state = { LaserON_ID, MotorON_ID, Incubation1_ID, Ko_ID, MotorOFF_ID, LaserOFF_ID, Calc_ID };
    State::state_map = {
        { 0,  QString("Включение лазеров") },
        { 1,  QString("Включение двигателей") },
        { 2,  QString("Инкубация") },
        { 3,  QString("Сбор данных") },
        { 4,  QString("Выключение лазеров") },
        { 5,  QString("Выключение двигателей") },
        { 6,  QString("Расчет") }
    };
}

StateCalAgr1::StateCalAgr1()
{
    State::state = { Incubation1_ID , Avg_ID ,Incubation1_ID, Avg_ID, Agr_ID };
    State::state_map = {
        { 0,  QString("Установите пробы с БТП в рабочие  каналы и нажмите СТАРТ") },
        { 1,  QString("Фиксация «100%» уровней") },
        { 2,  QString("Установите пробы с ОТП в рабочие  каналым и нажмите СТАРТ") },
        { 3,  QString("Фиксация «0%» уровней") }
    };
}

QString StateAgr1::getMessage()
{
    return state_map.take(index);
}

StateAgr2::StateAgr2()
{
    State::state = { Incubation2_ID };
}

State *StateBuilder::getStateTestKo1()
{
    return new StateKo1;
}

State *StateBuilder::getStateTestKo2()
{
    return new StateKo2;
}

State *StateBuilder::getStateTestKo3()
{
    return new StateKo3;
}

State *StateBuilder::getStateTestKo4()
{
    return new StateKo4;
}

State *StateBuilder::getStateTestKo5()
{
    return new StateKo5;
}

State *StateBuilder::getStateTestAgr1()
{
    return new StateAgr1;
}

State *StateBuilder::getStateTestAgr2()
{
    return new StateAgr2;
}

State *StateBuilder::getStateCalAgr1()
{
    return new StateCalAgr1;
}

State *StateBuilder::getStateCalAgr2()
{
    return new StateCalAgr2;
}

State *StateBuilder::getStateCalKo1()
{
    return new StateCalKo1;
}

State *StateBuilder::getStateCalKo2()
{
    return new StateCalKo2;
}

State *StateBuilder::getStateCalKo3()
{
    return new StateCalKo3;
}

State *StateBuilder::getStateCalKo4()
{
    return new StateCalKo4;
}

State *StateBuilder::getStateCalKo5()
{
    return new StateCalKo5;
}

State* StateBuilder::getState(Mode_ID mode)
{
    State* state;
    switch (mode) {
    case CalibAgr1_ID:
        state = getStateCalAgr1();
        break;
    case CalibAgr2_ID:
        state = getStateCalAgr2();
        break;
    case CalibKo1_ID:
        state = getStateCalKo1();
        break;
    case CalibKo2_ID:
        state = getStateCalKo2();
        break;
    case CalibKo3_ID:
        state = getStateCalKo3();
        break;
    case CalibKo4_ID:
        state = getStateCalKo4();
        break;
    case CalibKo5_ID:
        state = getStateCalKo5();
        break;
    case TestAgr1_ID:
        state = getStateTestAgr1();
        break;
    case TestAgr2_ID:
        state = getStateTestAgr2();
        break;
    case TestKo1_ID:
        state = getStateTestKo1();
        break;
    case TestKo2_ID:
        state = getStateTestKo2();
        break;
    case TestKo3_ID:
        state = getStateTestKo3();
        break;
    case TestKo4_ID:
        state = getStateTestKo4();
        break;
    case TestKo5_ID:
        state = getStateTestKo5();
        break;
    default:
        state = new State();
        break;
    }
    return state;
}
