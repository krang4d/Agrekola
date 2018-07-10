#pragma once

#include <QWidget>
#include <QDebug>
#include <QVector>
#include <QString>
#include <QThread>

#include "LoadDll.h"
#include "Lusbapi.h"


#define MaxVirtualSoltsQuantity 127

struct Errore_E154
{
    QString err_msg;
    Errore_E154(const QString &m) : err_msg(m) {}
};

struct DoubleData
{
    DoubleData(double *d, int i) : data(d), size(i) {}
    double *data;
    int size;
};

class useE154 : public QThread
{
     Q_OBJECT
     void run() Q_DECL_OVERRIDE {
         funThread();
     }
public:
    enum {
        OFF, ON
    };

    enum channel{
        CH1 = 0x00, CH2 = 0x01 , CH3 = 0x02, CH4 = 0x03, PP = 0x04, L = 0x05
    };

signals:
    void value_come(QVector<double>&);
    void update_termo(bool);

public:
    useE154(QThread *parent = 0);
	~useE154(void);
    QString GetVersion(void);
    QString GetUserMessages() const;
    QString GetUsbSpeed();
    QString GetInformation();
    void SetChannel(channel ch, int pos);
    bool GetStatusTD();

public slots:
    /*Функции по сбору данных */
    double AdcSample(channel ch);   //простое одноканальное измерение АЦП канала ch, n раз
    QVector<double> AdcKADR();                 //покадровое измерение
    QString AdcSynchro();       //измерение в синхронном режиме возвращает строку данных
    DoubleData AdcSynchroDouble();


protected:
	void initAPIInstance();
	void initModuleHandler();
    void initPorts();                           //инициализация всех выводов TTL
    QString initADC();

public:
    void funThread();
    int OpenDevice();
    void CloseDevice();
    void ReleaseAPIInstance();					//(char *ErrorString, bool AbortionFlag);

public slots:
    void onMixCh1(bool);
    void onMixCh2(bool);
    void onMixCh3(bool);
    void onMixCh4(bool);
    void onMixPP(bool);
    void onLaser(bool);
    void stopThread();

private:
    TLoadDll *pLoadDll;							// указатель на класс динамической загрузки DLL
	ILE154 *pModule;							// указатель на интерфейс модуля
	HANDLE ModuleHandle;						// дескриптор устройства
	char ModuleName[7];							// название модуля
	BYTE UsbSpeed;								// скорость работы шины USB
	MODULE_DESCRIPTION_E154 ModuleDescription;	// структура с полной информацией о модуле
    IO_REQUEST_LUSBAPI IoReq;                   // структура с параметрами запроса на ввод/вывод данных
    ADC_PARS_E154 ap;							// структура параметров работы АЦП модуля
    double *pDestination;

    double volts_array[16];
    QVector<double> vec_data;

	WORD TtlOut;	//Состояние выходных портов 
	WORD TtlIN;		//Состояние входных портов
    volatile bool thread_stop;
};
