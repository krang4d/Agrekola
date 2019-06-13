#pragma once

#include <QWidget>
#include <QDebug>
#include <QVector>
#include <QString>
#include <QThread>

#include "LoadDll.h"
#include "Lusbapi.h"

#define MaxVirtualSoltsQuantity 127

struct Error_E154
{
    QString err_msg;
    Error_E154(const QString &m) : err_msg(m) {}
};

struct DoubleData
{
    DoubleData(double *d, int i) : data(d), size(i) {}
    double *data;
    int size;
};

class IuseE154
{
public:
    virtual QVariantList AdcKADR() = 0; //покадровое измерение
    virtual QString GetInformation() = 0;
    /*Методы управления портами*/
    virtual void onMixCh1(bool) = 0;
    virtual void onMixCh2(bool) = 0;
    virtual void onMixCh3(bool) = 0;
    virtual void onMixCh4(bool) = 0;
    virtual void onMixPP(bool) = 0;
    virtual void onLaser(bool) = 0;
};

class useE154 : public QThread, public IuseE154
{
     Q_OBJECT
     void run() Q_DECL_OVERRIDE {
         thread_stop = false;
         funThread();
         qDebug() << "Thread useE154 is stoped, id: " << QThread::currentThreadId();
     }
public:
    enum {
        OFF, ON
    };

    enum Channel{
        CH1 = 0x00, CH2 = 0x01 , CH3 = 0x02, CH4 = 0x03, PP = 0x04, L = 0x05
    };

    useE154(QWidget *parent = 0);
	~useE154(void);

    int OpenDevice();
    void CloseDevice();

    QString GetUserMessages() const;
    QString GetUsbSpeed();
    void SetChannel(Channel ch, int pos);
    bool GetStatusTD();  //термостатирование

protected:
    void initPorts();                           //инициализация всех выводов TTL
    void funThread();
    void initADC();
    DoubleData AdcSynchroDouble();

signals:
    void value_come(QVariantList);
    void update_termo(bool);

public slots:
    /*Методы по сбору данных */
    double AdcSample(Channel ch);   //простое одноканальное измерение АЦП канала ch, n раз

    QString AdcSynchro();       //измерение в синхронном режиме возвращает строку данных

    /*Метод остановки потока*/
    void stopThread();

    // IuseE154 iterface
    QVariantList AdcKADR() override;                 //покадровое измерение
    QString GetInformation();
    /*Методы управления портами*/
    void onMixCh1(bool) override;
    void onMixCh2(bool) override;
    void onMixCh3(bool) override;
    void onMixCh4(bool) override;
    void onMixPP(bool) override;
    void onLaser(bool) override;

private:

	ILE154 *pModule;							// указатель на интерфейс модуля
	MODULE_DESCRIPTION_E154 ModuleDescription;	// структура с полной информацией о модуле
    IO_REQUEST_LUSBAPI IoReq;                   // структура с параметрами запроса на ввод/вывод данных
    ADC_PARS_E154 ap;							// структура параметров работы АЦП модуля
    double *pDestination;

    QVector<double> vec_data;

	WORD TtlOut;	//Состояние выходных портов 
	WORD TtlIN;		//Состояние входных портов
    volatile bool thread_stop;
};

class OnlyOneE154
{
    TLoadDll *pLoadDll;							// указатель на класс динамической загрузки DLL
    ILE154 *pModule;							// указатель на интерфейс модуля
    HANDLE ModuleHandle;						// дескриптор устройства

public:
    static OnlyOneE154& Instance()
    {
        static OnlyOneE154 theSingleInstance;
        return theSingleInstance;
    }

    ILE154* getModule() { return pModule; }

    //typedef DWORD (WINAPI *pGetDllVersion)(void);
    inline QString GetVersion()
    {
        pGetDllVersion GetDllVersion = (pGetDllVersion)pLoadDll->CallGetDllVersion();
        if(!GetDllVersion) qDebug().noquote() << QString("Ошибка выделения памяти в функции Get_Version()!");
        //sprintf(str, " Lusbapi.dll Version Error!!!\n   Current: %1u.%1u. Required: %1u.%1u",
        //						DllVersion >> 0x10, DllVersion & 0xFFFF,
        //						CURRENT_VERSION_LUSBAPI >> 0x10, CURRENT_VERSION_LUSBAPI & 0xFFFF);
        DWORD DllVersion = GetDllVersion();
        return QString("Версия dll библиотеки - v%1.%2").arg(DllVersion >> 0x10).arg(DllVersion & 0xFFFF);
    }

private:
    OnlyOneE154() {
        pLoadDll = new TLoadDll();
        if(!pLoadDll) qDebug().noquote() << QString("Ошибка загрузи библиотеки Dll Load_Dll()!");

        initAPIInstance();
        //initModuleHandler();
    }

    ~OnlyOneE154() {
        ReleaseAPIInstance();
    }

    OnlyOneE154(const OnlyOneE154& root) = delete;
    OnlyOneE154& operator=(const OnlyOneE154&) = delete;

    //typedef LPVOID (WINAPI *pCreateInstance)(char *);
    inline void initAPIInstance()
    {
        char name[] = "e154";
        pCreateInstance CreateInstance = (pCreateInstance)pLoadDll->CallCreateLInstance();
        if(!CreateInstance) qDebug().noquote() << QString("Ошибка выделения памяти в функции SetAPIInstance()!");
        pModule = static_cast<ILE154 *>(CreateInstance(name));
        //pModule = static_cast<ILE154 *>(CreateInstance(const_cast<char*>("e154")));
        if(!pModule) qDebug().noquote() << QString("Ошибка выделения памяти для интерфейса CreateInstance(\"e154\")!");
    }

    inline void ReleaseAPIInstance() //(char *ErrorString, bool AbortionFlag)
    {	// подчищаем интерфейс модуля
        if(pModule)
        {
            // освободим интерфейс модуля
            if(!pModule->ReleaseLInstance()) qDebug().noquote() << QString("Ошибка при освобождении интерфейса ReleaseLInstance()!");
            //else printf(" ReleaseLInstance() --> OK\n");
            // обнулим указатель на интерфейс модуля
            pModule = NULL;

            if(!pLoadDll) {
                delete pLoadDll;
            }
        }
    }
    void initModuleHandler()
    {
        ModuleHandle = pModule->GetModuleHandleW();
        if(ModuleHandle == INVALID_HANDLE_VALUE) qDebug().noquote() << QString("GetModuleHandle() --> Bad\n");
    }
};

