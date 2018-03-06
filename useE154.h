#pragma once

//#include "LoadDll.h"
#include "LoadDll.h"
#include "lib\Lusbapi.h"
#include <string>
#include <list>

#define MaxVirtualSoltsQuantity 127

using std::string;

enum {
	OFF, ON 
};

enum channel{
    CH1, CH2 , CH3, CH4, PP, L
};

struct Errore_E154
{
    string err_msg;
    Errore_E154(const string &m) : err_msg(m) {}
};

class useE154
{
public:
	useE154(void);
	~useE154(void);
    string GetVertion(void);
    string OpenDevice();
    string GetUserMessages() const;
    string GetUsbSpeed();
    string GetInformation();
    void SetChannel(channel ch, int pos) {
         if(pos == ON){
            switch(ch){
                    case CH1: { TtlOut |= (1<<0); pModule->TTL_OUT(TtlOut); break; }
                    case CH2: { TtlOut |= (1<<1); pModule->TTL_OUT(TtlOut); break; }
                    case CH3: { TtlOut |= (1<<2); pModule->TTL_OUT(TtlOut); break; }
                    case CH4: { TtlOut |= (1<<3); pModule->TTL_OUT(TtlOut); break; }
                    case  PP: { TtlOut |= (1<<4); pModule->TTL_OUT(TtlOut); break; }
                    case   L: { TtlOut |= (1<<5); pModule->TTL_OUT(TtlOut); break; }
                        default: throw Errore_E154("Неправильно выбран TTL канал");
             }
         }
         else{
             switch(ch){
                    case CH1: { TtlOut &= ~(1<<0); pModule->TTL_OUT(TtlOut); break; }
                    case CH2: { TtlOut &= ~(1<<1); pModule->TTL_OUT(TtlOut); break; }
                    case CH3: { TtlOut &= ~(1<<2); pModule->TTL_OUT(TtlOut); break; }
                    case CH4: { TtlOut &= ~(1<<3); pModule->TTL_OUT(TtlOut); break; }
                    case  PP: { TtlOut &= ~(1<<4); pModule->TTL_OUT(TtlOut); break; }
                    case   L: { TtlOut &= ~(1<<5); pModule->TTL_OUT(TtlOut); break; }
                        default: throw Errore_E154("Неправильно выбран TTL канал");
                }
            }
    }
    bool GetTDStatus() { pModule->TTL_IN(&TtlIN); if(TtlIN & (1<<0)) return TRUE; else return FALSE; }
    double AdcSample();			 				//простое измерение АЦП
protected:
	void initAPIInstance();
	void initModuleHandler();
	void initPorts() {
		if(pModule->ENABLE_TTL_OUT(1)) pModule->TTL_OUT(0); else throw Errore_E154("Ошибка включения линий TTL"); //инициализация всех выводов TTL
	}
	void ReleaseAPIInstance();					//(char *ErrorString, bool AbortionFlag);
    TLoadDll *pLoadDll;							// указатель на класс динамической загрузки DLL
	DWORD DllVersion;							// версия библиотеки
	ILE154 *pModule;							// указатель на интерфейс модуля
	HANDLE ModuleHandle;						// дескриптор устройства
	char ModuleName[7];							// название модуля
	BYTE UsbSpeed;								// скорость работы шины USB
	MODULE_DESCRIPTION_E154 ModuleDescription;	// структура с полной информацией о модуле

	ADC_PARS_E154 ap;							// структура параметров работы АЦП модуля

	// отсчёты АЦП
	SHORT AdcSample1, AdcSample2;

	// индекс входного диапазона напряжения
	const WORD InputRangeIndex = ADC_INPUT_RANGE_5000mV_E154;
	const double AdcRate;						// частота работы АЦП в кГц

	WORD TtlOut;	//Состояние выходных портов 
	WORD TtlIN;		//Состояние входных портов
    std::list<string> user_msg;
    //string user_msg;							// последнее выведенное сообщение
    string log_msg;							// служебная информация
};
