#include "state.h"

State::State(IScenario *o, QObject *parent) : QObject(parent), scena(o)
{}

State::~State()
{}

void State::insertState(State_ID id, QString msg, int level)
{
    //state.push_back(id);
    state_list.append(QPair<State_ID, QString>(id, msg));
    it = state_list.begin();
    this->level = level;
}

State_ID State::current()
{
    return it->first;
}

void State::next()
{
    if( it != state_list.end() ) {
        ++it;
        emit stateChanged();
    }
    else {
       qDebug() << "Errore: State::Index is out of date!";
       //emit stateChanged();
    }
}

bool State::hasNext()
{
    return it != state_list.end();
}

void State::reset()
{
    it = state_list.begin();
}

QString State::getMessage()
{
    return it->second;
}

int State::getLevel()
{
    return level;
}

void State::doState()
{
    qDebug() << QString("State IS: %1" ).arg(it->first);
    switch(it->first) {
        case Btp_ID:
            scena->getBTP();
            break;
        case Otp_ID:
            scena->getOTP();
            break;
        case MotorON_ID:
            scena->onMixChls(true);
            scena->onMixPP(true);
            next();
            break;
        case MotorOFF_ID:
            scena->onMixChls(false);
            scena->onMixPP(false);
            next();
            break;
        case LaserON_ID:
            scena->onLazer(true);
            next();
            break;
        case LaserOFF_ID:
            scena->onLazer(false);
            next();
            break;
        case Ko_ID:
            scena->ko(this);
            break;
        case Calc_ID:
            scena->calc();
            next();
            break;
        case Write_ID:
            scena->write();
            next();
            break;
//        case Avg_ID:
//            if (startWin->isChannel(Channel1_ID)) {
//                i++;
//                getData(Channel1_ID, startWin->getTimeWrite());
//                connect(this, &Widget::done1, [this]() {
//                    i--;
//                    disconnect(this, &Widget::done1, 0, 0);
//                    if (!i) { state->next(); qDebug() << "done1"; }
//                });

//            }
//            if (startWin->isChannel(Channel2_ID)) {
//                i++;
//                getData(Channel2_ID, startWin->getTimeWrite());
//                connect(this, &Widget::done2, [this]() {
//                    i--;
//                    disconnect(this, &Widget::done2, 0, 0);
//                    if (!i) { state->next(); qDebug() << "done2"; }
//                });
//            }
//            if (startWin->isChannel(Channel3_ID)) {
//                i++;
//                getData(Channel3_ID, startWin->getTimeWrite());
//                connect(this, &Widget::done3, [this]() {
//                    i--;
//                    disconnect(this, &Widget::done3, 0, 0);
//                    if (!i) { state->next(); qDebug() << "done3"; }
//                });
//            }
//            if (startWin->isChannel(Channel4_ID)) {
//                i++;
//                getData(Channel4_ID, startWin->getTimeWrite());
//                connect(this, &Widget::done4, [this]() {
//                    i--;
//                    disconnect(this, &Widget::done4, 0, 0);
//                    if (!i) { state->next(); qDebug() << "done4"; }
//                });
//            }
//            break;
        case Agr_ID:
            ///scena->waitImpulse(new ImpuleWaiter);
            next();
            break;
        case Incubation1_ID:
            scena->incubation1(this);
            break;
        case Incubation2_ID:
            scena->incubation2(this);
            break;
        case SelectInductor_ID:
            scena->selectInductor(this);
            break;
        case End_ID:
            scena->finish();
            break;
        default:
            qDebug() << QString("called default startMeasurment()");
            ///QMessageBox::information(this, "Alert", "called default startMeasurment()");
            break;
    } //end switch
}

void State::doScenario()
{
    while(hasNext()){
        doState();
    }
}

StateKo1::StateKo1(IScenario *o) : State(o)
{
    insertState(LaserON_ID,     "Включение лазеров");
    insertState(MotorON_ID,     "Включение двигателей");
    insertState(Incubation1_ID, "Инкубация");
    insertState(Ko_ID,          "Измерение");
    insertState(Calc_ID,        "Расчет");
    insertState(Write_ID,       "Запись");
    insertState(LaserOFF_ID,     "Включение лазеров");
    insertState(MotorOFF_ID,     "Включение двигателей");
    insertState(End_ID,         "Конец");
}

void StateKo1::doScenario()
{

}

StateKo2::StateKo2(IScenario *o) : State(o)
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

StateKo3::StateKo3(IScenario *o) : State(o)
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

StateKo4::StateKo4(IScenario *o) : State(o)
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

StateKo5::StateKo5(IScenario *o) : State(o)
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

StateAgr1::StateAgr1(IScenario *o ) : State(o)
{
    insertState(LaserON_ID,     "Включение лазеров");
    insertState(MotorON_ID,     "Включение двигателей");
    insertState(Incubation1_ID, "Инкубация");
    insertState(SelectInductor_ID, "Выбор индуктора");
    insertState(LaserOFF_ID,    "Выключение лазеров");
    insertState(MotorOFF_ID,    "Выключение двигателей");
    insertState(End_ID,         "Конец");
}

StateAgr2::StateAgr2(IScenario *o) : State(o)
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

StateCalKo1::StateCalKo1(IScenario *o) : State(o)
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

StateCalKo2::StateCalKo2(IScenario *o) : State(o)
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

StateCalKo3::StateCalKo3(IScenario *o) : State(o)      //Фибриноген калибровка
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

StateCalKo4::StateCalKo4(IScenario *o) : State(o)      //Тромбин калибровка
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

StateCalKo5::StateCalKo5(IScenario *o) : State(o)
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

StateCalAgr1::StateCalAgr1(IScenario *o) : State(o)
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

StateCalAgr2::StateCalAgr2(IScenario *o) : State(o)
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

State *StateBuilder::getStateTestKo1(IScenario *o)
{
    return new StateKo1(o);
}

State *StateBuilder::getStateTestKo2(IScenario *o)
{
    return new StateKo2(o);
}

State *StateBuilder::getStateTestKo3(IScenario *o)
{
    return new StateKo3(o);
}

State *StateBuilder::getStateTestKo4(IScenario *o)
{
    return new StateKo4(o);
}

State *StateBuilder::getStateTestKo5(IScenario *o)
{
    return new StateKo5(o);
}

State *StateBuilder::getStateTestAgr1(IScenario *o)
{
    return new StateAgr1(o);
}

State *StateBuilder::getStateTestAgr2(IScenario *o)
{
    return new StateAgr2(o);
}

State *StateBuilder::getStateCalAgr1(IScenario *o)
{
    return new StateCalAgr1(o);
}

State *StateBuilder::getStateCalAgr2(IScenario *o)
{
    return new StateCalAgr2(o);
}

State *StateBuilder::getStateCalKo1(IScenario *o)
{
    return new StateCalKo1(o);
}

State *StateBuilder::getStateCalKo2(IScenario *o)
{
    return new StateCalKo2(o);
}

State *StateBuilder::getStateCalKo3(IScenario *o)
{
    return new StateCalKo3(o);
}

State *StateBuilder::getStateCalKo4(IScenario *o)
{
    return new StateCalKo4(o);
}

State *StateBuilder::getStateCalKo5(IScenario *o)
{
    return new StateCalKo5(o);
}

State* StateBuilder::getState(Mode_ID mode, IScenario *o)
{
    State* state;
    switch (mode) {
    case CalibAgr1_ID:
        state = getStateCalAgr1(o);
        break;
    case CalibAgr2_ID:
        state = getStateCalAgr2(o);
        break;
    case CalibKo1_ID:
        state = getStateCalKo1(o);
        break;
    case CalibKo2_ID:
        state = getStateCalKo2(o);
        break;
    case CalibKo3_ID:
        state = getStateCalKo3(o);
        break;
    case CalibKo4_ID:
        state = getStateCalKo4(o);
        break;
    case CalibKo5_ID:
        state = getStateCalKo5(o);
        break;
    case TestAgr1_ID:
        state = getStateTestAgr1(o);
        break;
    case TestAgr2_ID:
        state = getStateTestAgr2(o);
        break;
    case TestKo1_ID:
        state = getStateTestKo1(o);
        break;
    case TestKo2_ID:
        state = getStateTestKo2(o);
        break;
    case TestKo3_ID:
        state = getStateTestKo3(o);
        break;
    case TestKo4_ID:
        state = getStateTestKo4(o);
        break;
    case TestKo5_ID:
        state = getStateTestKo5(o);
        break;
    default:
        state = new State(o);
        break;
    }
    return state;
}
