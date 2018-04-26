﻿#pragma once

#include <QWidget>
#include "LoadDll.h"
#include "Lusbapi.h"
#include <string>
#include <list>
#include <QList>

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

class useE154 : public QWidget
{
     Q_OBJECT

signals:
    void ValueCome(std::list<double>*);

public:
    useE154(QWidget *parent = 0);
	~useE154(void);
    string OpenDevice();
    string GetVersion(void);
    string GetUserMessages() const;
    string GetUsbSpeed();
    string GetInformation();
    void SetChannel(channel ch, int pos);
    bool GetStatusTD();
    double AdcSample(channel ch);               //простое одноканальное измерение АЦП
    void AdcKADR();
    void AdcSynchro();                          //измерение в синхронном режиме

    double volts_array[16];
    std::list<double> AdcSampleList;

protected:
	void initAPIInstance();
	void initModuleHandler();
    void initPorts();                           //инициализация всех выводов TTL
    string initADC();
	void ReleaseAPIInstance();					//(char *ErrorString, bool AbortionFlag);

private:
    TLoadDll *pLoadDll;							// указатель на класс динамической загрузки DLL
	ILE154 *pModule;							// указатель на интерфейс модуля
	HANDLE ModuleHandle;						// дескриптор устройства
	char ModuleName[7];							// название модуля
	BYTE UsbSpeed;								// скорость работы шины USB
	MODULE_DESCRIPTION_E154 ModuleDescription;	// структура с полной информацией о модуле
    IO_REQUEST_LUSBAPI IoReq;                   // структура с параметрами запроса на ввод/вывод данных
    ADC_PARS_E154 ap;							// структура параметров работы АЦП модуля

	// отсчёты АЦП
	SHORT AdcSample1, AdcSample2;

    std::list<SHORT> Adc1BufferList;
    std::list<SHORT> Adc2BufferList;
    std::list<SHORT> Adc3BufferList;
    std::list<SHORT> Adc4BufferList;

	WORD TtlOut;	//Состояние выходных портов 
	WORD TtlIN;		//Состояние входных портов
    std::list<string> user_msg;
    //std::list<AdcBuffer> VoltList;
    //string user_msg;                      // последнее выведенное сообщение
    string log_msg;							// служебная информация
};
