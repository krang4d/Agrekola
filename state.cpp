#include "state.h"

State::State(QObject *parent) : QObject(parent)
{}

State::~State()
{}

void State::insertState(State_ID id, QString msg, int level)
{
    //state.push_back(id);
    state_map.append(QPair<State_ID, QString>(id, msg));
    it = state_map.begin();
    this->level = level;
}

State_ID State::current()
{
    return (*it).first;
}

int State::next()
{
    if( hasNext() ) {
        ++it;
        emit stateChanged();
        return (*it).first;
    }
    else {
       qDebug() << "Errore", "State::Index is out of date!";
       //emit stateChanged();
       return -1;
    }
}

bool State::hasNext()
{
    return it != state_map.end();
}

void State::reset()
{
    it = state_map.begin();
}

QString State::getMessage()
{
    auto str = *it;
    return str.second;
}

int State::getLevel()
{
    return level;
}

void State::doState(State_ID st)
{
    switch (st) {
    case MotorON_ID:
        break;
    case MotorOFF_ID:
        break;
    case LaserON_ID:
        break;
    case LaserOFF_ID:
        break;
    case Ko_ID:
        break;
    case Agr_ID:
        break;
    case Avg_ID:
        break;
    case Btp_ID:
        break;
    case Otp_ID:
        break;
    case Calc_ID:
        break;
    case Write_ID:
        break;
    case Incubation1_ID:
        break;
    case Incubation2_ID:
        break;
    case SelectInductor_ID:
        break;
    case End_ID:
        break;
    default:
        break;
    next();
    }
}

StateKo1::StateKo1()
{
    insertState(Incubation1_ID, "Инкубация 1");
    insertState(Ko_ID,          "Измерение 1");
    insertState(Calc_ID,        "Расчет");
    insertState(Write_ID,       "Запись");
    insertState(End_ID,         "Конец");
}

void StateKo1::doScenario()
{

}

StateKo2::StateKo2()
{
    insertState(LaserON_ID,     "Включение лазеров");
    insertState(MotorON_ID,     "Включение двигателей");
    insertState(Incubation1_ID, "Инкубация");
    insertState(Ko_ID,          "Сбор данных");
    insertState(LaserOFF_ID,    "Выключение лазеров");
    insertState(MotorOFF_ID,    "Выключение двигателей");
    insertState(Calc_ID,        "Расчет");
    insertState(Write_ID,       "Запись");
    insertState(End_ID,         "Конец");
}

StateKo3::StateKo3()
{
    insertState(LaserON_ID,     "Включение лазеров");
    insertState(MotorON_ID,     "Включение двигателей");
    insertState(Incubation1_ID, "Инкубация");
    insertState(Ko_ID,          "Сбор данных");
    insertState(LaserOFF_ID,    "Выключение лазеров");
    insertState(MotorOFF_ID,    "Выключение двигателей");
    insertState(Calc_ID,        "Расчет");
    insertState(Write_ID,       "Запись");
    insertState(End_ID,         "Конец");
}

StateKo4::StateKo4()
{
    insertState(LaserON_ID,     "Включение лазеров");
    insertState(MotorON_ID,     "Включение двигателей");
    insertState(Incubation1_ID, "Инкубация");
    insertState(Ko_ID,          "Сбор данных");
    insertState(LaserOFF_ID,    "Выключение лазеров");
    insertState(MotorOFF_ID,    "Выключение двигателей");
    insertState(Calc_ID,        "Расчет");
    insertState(Write_ID,       "Запись");
    insertState(End_ID,         "Конец");
}

StateKo5::StateKo5()
{
    insertState(LaserON_ID,     "Включение лазеров");
    insertState(MotorON_ID,     "Включение двигателей");
    insertState(Incubation1_ID, "Инкубация");
    insertState(Ko_ID,          "Сбор данных");
    insertState(LaserOFF_ID,    "Выключение лазеров");
    insertState(MotorOFF_ID,    "Выключение двигателей");
    insertState(Calc_ID,        "Расчет");
    insertState(Write_ID,       "Запись");
    insertState(End_ID,         "Конец");
}

StateAgr1::StateAgr1()
{
    insertState(Incubation1_ID, "Инкубация");
    insertState(SelectInductor_ID, "Выбор индуктора");
}

StateAgr2::StateAgr2()
{
    insertState(LaserON_ID,     "Включение лазеров");
    insertState(MotorON_ID,     "Включение двигателей");
    insertState(Incubation1_ID, "Инкубация");
    insertState(Btp_ID,         "Фиксация «100%» уровня");    //"Установите пробы с БТП в рабочие  каналы"
    insertState(Incubation1_ID, "Инкубация");
    insertState(Otp_ID,         "Фиксация «0%» уровня");      //"Установите пробы с ОТП в рабочие  каналы"
    insertState(SelectInductor_ID, "Выбор индуктора");
    insertState(Agr_ID, "Сбор данных");
    insertState(LaserOFF_ID,    "Выключение лазеров");
    insertState(MotorOFF_ID,    "Выключение двигателей");
    insertState(Calc_ID, "Расчет");
    insertState(End_ID,  "Конец");
}

StateCalKo1::StateCalKo1()
{
    insertState(LaserON_ID,     "Включение лазеров");
    insertState(MotorON_ID,     "Включение двигателей");
    insertState(Incubation1_ID, "Инкубация");
    insertState(Ko_ID,          "Сбор данных");
    insertState(LaserOFF_ID,    "Выключение лазеров");
    insertState(MotorOFF_ID,    "Выключение двигателей");
    insertState(Calc_ID,        "Расчет");
    insertState(Write_ID,       "Запись");
    insertState(End_ID,         "Конец");
}

StateCalKo2::StateCalKo2()
{
    insertState(LaserON_ID,     "Включение лазеров");
    insertState(MotorON_ID,     "Включение двигателей");
    insertState(Incubation1_ID, "Инкубация");
    insertState(Ko_ID,          "Сбор данных");
    insertState(LaserOFF_ID,    "Выключение лазеров");
    insertState(MotorOFF_ID,    "Выключение двигателей");
    insertState(Calc_ID,        "Расчет");
    insertState(Write_ID,       "Запись");
    insertState(End_ID,         "Конец");
}

StateCalKo3::StateCalKo3()      //Фибриноген калибровка
{
    insertState(LaserON_ID,     "Включение лазеров");
    insertState(MotorON_ID,     "Включение двигателей");

    insertState(Ko_ID,          "Установите разведения 200% в каналы 1,2, 100% в каналыы 3,4");
    insertState(Calc_ID,        "Расчет", 1);
    insertState(Write_ID,       "Запись");

    insertState(Ko_ID,          "Установите разведения 50% в каналы 1,2, 25% в каналыы 3,4");
    insertState(Calc_ID,        "Расчет", 2);
    insertState(Write_ID,       "Запись");

    insertState(LaserOFF_ID,    "Выключение лазеров");
    insertState(MotorOFF_ID,    "Выключение двигателей");
    insertState(End_ID,         "Конец");
}

StateCalKo4::StateCalKo4()      //Тромбин калибровка
{
    insertState(LaserON_ID,     "Включение лазеров");
    insertState(MotorON_ID,     "Включение двигателей");
    insertState(Incubation1_ID, "Инкубация");
    insertState(Ko_ID,          "Сбор данных");
    insertState(LaserOFF_ID,    "Выключение лазеров");
    insertState(MotorOFF_ID,    "Выключение двигателей");
    insertState(Calc_ID,        "Расчет");
    insertState(Write_ID,       "Запись");
    insertState(End_ID,         "Конец");
}

StateCalKo5::StateCalKo5()
{
    insertState(LaserON_ID,     "Включение лазеров");
    insertState(MotorON_ID,     "Включение двигателей");
    insertState(Incubation1_ID, "Инкубация");
    insertState(Ko_ID,          "Сбор данных");
    insertState(LaserOFF_ID,    "Выключение лазеров");
    insertState(MotorOFF_ID,    "Выключение двигателей");
    insertState(Calc_ID,        "Расчет");
    insertState(Write_ID,       "Запись");
    insertState(End_ID,         "Конец");
}

StateCalAgr1::StateCalAgr1()
{
    insertState(Incubation1_ID, "Инкубация");
    insertState(Btp_ID,         "Фиксация «100%» уровня");    //"Установите пробы с БТП в рабочие  каналы"
    insertState(Incubation1_ID, "Инкубация");
    insertState(Otp_ID,         "Фиксация «0%» уровня");      //"Установите пробы с ОТП в рабочие  каналы"
    insertState(Agr_ID,         "Определение параметров агрегации");      //"Установите пробы с ОТП в рабочие  каналы"
    insertState(Calc_ID,        "Расчет");
    insertState(Write_ID,       "Запись");
    insertState(End_ID,         "Конец");
}

StateCalAgr2::StateCalAgr2()
{
    insertState(LaserON_ID,     "Включение лазеров");
    insertState(MotorON_ID,     "Включение двигателей");
    insertState(Incubation1_ID, "Инкубация");
    insertState(Agr_ID,          "Сбор данных");
    insertState(LaserOFF_ID,    "Выключение лазеров");
    insertState(MotorOFF_ID,    "Выключение двигателей");
    insertState(Calc_ID,        "Расчет");
    insertState(Write_ID,       "Запись");
    insertState(End_ID,         "Конец");
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
