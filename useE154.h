﻿#pragma once

//#include "LoadDll.h"
#include "LoadDll.h"
#include "lib\Lusbapi.h"
#include <string>
#include <list>

#define MaxVirtualSoltsQuantity 127

using std::string;

enum position {
	ON, OFF
}

enum channel {
	CH1, CH2 , CH3, Ch4, PP, L
}

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
    string GetInformation() const;
    void SetChannel(channel ch, position pos) {
    	swith(ch){
    		if(pos == chennel::ON){
	    		case CH1: { TtlOut |= (1<<0); pModule->TTL_OUT(TtlOut); break; }
	    		case CH2: { TtlOut |= (1<<1); pModule->TTL_OUT(TtlOut); break; }
	    		case CH3: { TtlOut |= (1<<2); pModule->TTL_OUT(TtlOut); break; }
	    		case CH4: { TtlOut |= (1<<3); pModule->TTL_OUT(TtlOut); break; }
	    		case  PP: { TtlOut |= (1<<4); pModule->TTL_OUT(TtlOut); break; }
	    		case   L: { TtlOut |= (1<<5); pModule->TTL_OUT(TtlOut); break; }
	    			default throw Errore_E154("Неправильно выбран TTL канал");
	    	}else{
				case CH1: { TtlOut &= ~(1<<0); pModule->TTL_OUT(TtlOut); break; }
	    		case CH2: { TtlOut &= ~(1<<1); pModule->TTL_OUT(TtlOut); break; }
	    		case CH3: { TtlOut &= ~(1<<2); pModule->TTL_OUT(TtlOut); break; }
	    		case CH4: { TtlOut &= ~(1<<3); pModule->TTL_OUT(TtlOut); break; }
	    		case  PP: { TtlOut &= ~(1<<4); pModule->TTL_OUT(TtlOut); break; }
	    		case   L: { TtlOut &= ~(1<<5); pModule->TTL_OUT(TtlOut); break; }
	    			default throw Errore_E154("Неправильно выбран TTL канал");
	    	}
    	}

    }
    bool GetTDStatus() { pModule->TTL_IN(&TtlIN); if(TtlIN & (1<<0)) return TRUE else return FALSE }  

protected:
	void initAPIInstance();
	void initModuleHandler();
	void initPorts() {
		if(pModule->ENABLE_TTL_OUT(1)) pModule->TTL_OUT(0); else throw Errore_E154("Ошибка включения линий TTL");
		//if(pModule->ENABLE_TTL_IN(1)) pModule->TTL_IN(0); else throw Errore_E154("Ошибка включения TTL_IN");
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
	const double AdcRate;						// частота работы АЦП в кГц
	const WORD InputRangeIndex;					// индекс входного диапазона напряжения

	WORD TtlOut;	//Состояние выходных портов 
	WORD TtlIN;		//Состояние входных портов
    std::list<string> user_msg;
    //string user_msg;							// последнее выведенное сообщение
    string log_msg;							// служебная информация
};

