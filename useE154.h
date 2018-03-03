#pragma once

//#include "LoadDll.h"
#include "LoadDll.h"
#include "lib\Lusbapi.h"
#include <string>

#define MaxVirtualSoltsQuantity 127

using std::string;

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

protected:
	void initAPIInstance();
	void initModuleHandler();
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

    string user_msg;							// последнее выведенное сообщение
    string log_msg;							// служебная информация
};

