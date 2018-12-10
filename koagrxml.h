#ifndef KOAGRXML_H
#define KOAGRXML_H

#include <QtXml>
#include <QDebug>
#include <QFile>
#include <QDate>
#include <QObject>

class CreateKoAgr : public QObject
{
    Q_OBJECT
public:
    explicit CreateKoAgr(QObject *parent = 0);
    static QDomDocument createTestKo(QString name);
    static QDomDocument createTestAgr(QString name);
    static int writeFile(QString name, QDomDocument doc);
    static int readFile(QString name, QDomDocument &doc);
};

class KoAgrXML : public CreateKoAgr
{
    Q_OBJECT
public:
    explicit KoAgrXML(QObject *parent = 0);
    static QDomDocument createTestKo1();
    static QDomDocument createTestKo2();
    static QDomDocument createTestKo3();
    static QDomDocument createTestKo4();
    static QDomDocument createTestKo5();
    static QDomDocument createTestAgr1();
    static QDomDocument createTestAgr2();

    static QDomDocument createCalibrationKo1();
    static QDomDocument createCalibrationKo2();
    static QDomDocument createCalibrationKo3();
    static QDomDocument createCalibrationKo4();
    static QDomDocument createCalibrationKo5();
    static QDomDocument createCalibrationAgr1();
    static QDomDocument createCalibrationAgr2();

    static QDomDocument openTestKo1();
    static QDomDocument openTestKo2();
    static QDomDocument openTestKo3();
    static QDomDocument openTestKo4();
    static QDomDocument openTestKo5();
    static QDomDocument openTestAgr1();
    static QDomDocument openTestAgr2();

    static QDomDocument openCalibrationKo1();
    static QDomDocument openCalibrationKo2();
    static QDomDocument openCalibrationKo3();
    static QDomDocument openCalibrationKo4();
    static QDomDocument openCalibrationKo5();
    static QDomDocument openCalibrationAgr1();
    static QDomDocument openCalibrationAgr2();

    static void ListElement(QDomElement root, QString tagname, QString attribute);
    static QString getElement(QDomDocument root, QString tagname, QString attribute = "Value");
    static void setElement(QDomDocument &root, QString tagname, QString value, QString attribute = "Value");
};

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QDomDocument doc, QString n, QObject *parent = 0);
    virtual ~Test();
    virtual void setK1(const int value);
    virtual int getK1() const;
    virtual void setK2(const int value);
    virtual int getK2() const;
    virtual void setK3(const int value);
    virtual int getK3() const;
    virtual void setK4(const int value);
    virtual int getK4() const;
    virtual void setSingle(const int value);
    virtual int getSingle() const ;
    virtual QString getText() const;

    virtual QString getNum1() const;
    virtual void setNum1(const QString &value);

    virtual QString getNum2() const;
    virtual void setNum2(const QString &value);

    virtual QString getNum3() const;
    virtual void setNum3(const QString &value);

    virtual QString getNum4() const;
    virtual void setNum4(const QString &value);

    virtual void save();
    virtual void load();

protected:
    QDomDocument getDoc() const;
    QString getName() const;

private:
    QDomDocument document;
    QString name;

    int k1, k2, k3, k4, single;
    QString num1, num2, num3, num4;
};

class TestKo1 : public Test
{
    Q_OBJECT
public:
    explicit TestKo1(QObject *parent = 0);
    virtual ~TestKo1();
};

class TestKo2 : public Test
{
    Q_OBJECT
public:
    explicit TestKo2(QObject *parent = 0);
    ~TestKo2();
};

class TestKo3 : public Test
{
    Q_OBJECT
public:
    explicit TestKo3(QObject *parent = 0);
    ~TestKo3();
};

class TestKo4 : public Test
{
    Q_OBJECT
public:
    explicit TestKo4(QObject *parent = 0);
    ~TestKo4();
};

class TestKo5 : public Test
{
    Q_OBJECT
public:
    explicit TestKo5(QObject *parent = 0);
    ~TestKo5();
};

class TestAgr1 : public Test
{
    Q_OBJECT
public:
    explicit TestAgr1(QObject *parent = 0);
    ~TestAgr1();
};

class TestAgr2 : public Test
{
    Q_OBJECT
public:
    explicit TestAgr2(QObject *parent = 0);
    ~TestAgr2();
};

class Calibration : public QObject
{
public:
    explicit Calibration(QDomDocument doc, QString n, QObject *parent = 0);
    ~Calibration();

    virtual QDate getDate() const;
    virtual void setDate(const QDate &value);

    int getWrite_time() const;
    void setWrite_time(const int value);

    int getIncube_time() const;
    void setIncube_time(int value);

    virtual void save();
    virtual void load();

protected:
    QDomDocument getDoc() const;
    QString getName() const;

protected:
    QDomDocument document;
    QString name;

private:
    QDate date;
    int write_time, incube_time;
};

class CalibrationKo1 : public Calibration
{
    Q_OBJECT
public:
    explicit CalibrationKo1();
    ~CalibrationKo1();
};

class CalibrationKo2 : public Calibration
{
    Q_OBJECT
public:
    explicit CalibrationKo2();
    ~CalibrationKo2();

    QDate getReagent_date() const;
    void setReagent_date(const QDate &value);

    QDate getK_plazma_date() const;
    void setK_plazma_date(const QDate &value);

    QString getReagent_serial() const;
    void setReagent_serial(const QString &value);

    QString getK_plazma_serial() const;
    void setK_plazma_serial(const QString &value);

    double getA4tv_k_plazma() const;
    void setA4tv_k_plazma(double value);

private:
    //входные
    QDate reagent_date, k_plazma_date;
    QString reagent_serial, k_plazma_serial;
    //выходные
    double a4tv_k_plazma;

    // Calibration interface
public:
    void save() override;
    void load() override;
};

class CalibrationKo3 : public Calibration
{
    Q_OBJECT
public:
    explicit CalibrationKo3();
    ~CalibrationKo3();

    QDate getReagent_date() const;
    void setReagent_date(const QDate &value);

    QString getReagent_serial() const;
    void setReagent_serial(const QString &value);

    double getFibrinogen_k_plazma() const;
    void setFibrinogen_k_plazma(double value);

    double getTime_k_plazma() const;
    void setTime_k_plazma(double value);

    double getFibrinogen_200_plazma() const;
    void setFibrinogen_200_plazma(double value);

    double getTime_200_plazma() const;
    void setTime_200_plazma(double value);

    double getFibrinogen_50_plazma() const;
    void setFibrinogen_50_plazma(double value);

    double getTime_50_plazma() const;
    void setTime_50_plazma(double value);

    double getFibrinogen_25_plazma() const;
    void setFibrinogen_25_plazma(double value);

    double getTime_25_plazma() const;
    void setTime_25_plazma(double value);

private:
    QDate reagent_date;
    QString reagent_serial;

    double fibrinogen_k_plazma, time_k_plazma;
    double fibrinogen_200_plazma, time_200_plazma;
    double fibrinogen_50_plazma, time_50_plazma;
    double fibrinogen_25_plazma, time_25_plazma;

    // Calibration interface
public:
    void save() override;
    void load() override;
};

class CalibrationKo4 : public Calibration
{
    Q_OBJECT
public:
    explicit CalibrationKo4();
    ~CalibrationKo4();

    QDate getReagent_date() const;
    void setReagent_date(const QDate &value);

    QDate getK_plazma_date() const;
    void setK_plazma_date(const QDate &value);

    QString getReagent_serial() const;
    void setReagent_serial(const QString &value);

    QString getK_plazma_serial() const;
    void setK_plazma_serial(const QString &value);

    QString getAction() const;
    void setAction(const QString &value);

    double getTrombine_time() const;
    void setTrombine_time(double value);

private:
    QDate reagent_date, k_plazma_date;

    QString reagent_serial, k_plazma_serial;
    QString action; //стартовый реагент
    double trombine_time;

    // Calibration interface
public:
    void save() override;
    void load() override;
};

class CalibrationKo5 : public Calibration
{
    Q_OBJECT
public:
    explicit CalibrationKo5();
    ~CalibrationKo5();

    QDate getTromboplastin_date() const;
    void setTromboplastin_date(const QDate &value);

    QDate getK_plazma_date() const;
    void setK_plazma_date(const QDate &value);

    QString getTromboplastin_serial() const;
    void setTromboplastin_serial(const QString &value);

    QString getK_plazma_serial() const;
    void setK_plazma_serial(const QString &value);

    double getK_protrombine_index() const;
    void setK_protrombine_index(double value);

    double getK_protrombine_otn() const;
    void setK_protrombine_otn(double value);

    double getProtrombine_k_Kvik() const;
    void setProtrombine_k_Kvik(double value);

    double getTime_k_Kvik() const;
    void setTime_k_Kvik(double value);

    double getProtrombine_50_Kvik() const;
    void setProtrombine_50_Kvik(double value);

    double getTime_50_Kvik() const;
    void setTime_50_Kvik(double value);

    double getProtrombine_25_Kvik() const;
    void setProtrombine_25_Kvik(double value);

    double getTime_25_Kvik() const;
    void setTime_25_Kvik(double value);

    double getProtrombine_12_Kvik() const;
    void setProtrombine_12_Kvik(double value);

    double getTime_12_Kvik() const;
    void setTime_12_Kvik(double value);

    double getProtrombine_index() const;
    void setProtrombine_index(double value);

    double getProtrombine_otn() const;
    void setProtrombine_otn(double value);

private:
    QDate tromboplastin_date, k_plazma_date;
    QString tromboplastin_serial, k_plazma_serial;
    double k_protrombine_index, k_protrombine_otn;
    double protrombine_k_Kvik, time_k_Kvik;
    double protrombine_50_Kvik, time_50_Kvik;
    double protrombine_25_Kvik, time_25_Kvik;
    double protrombine_12_Kvik, time_12_Kvik;
    double protrombine_index, protrombine_otn;

    // Calibration interface
public:
    void save() override;
    void load() override;
};

class CalibrationAgr1 : public Calibration
{
    Q_OBJECT
public:
    explicit CalibrationAgr1();
    ~CalibrationAgr1();

    QDate getReagent_date() const;
    void setReagent_date(const QDate &value);

    QString getReagent_serial() const;
    void setReagent_serial(const QString &value);

    double getK_concentration() const;
    void setK_concentration(double value);

    double getLevel_0() const;
    void setLevel_0(double value);

    double getLevel_100() const;
    void setLevel_100(double value);

private:
    QDate reagent_date;
    QString reagent_serial;
    double k_concentration, level_0, level_100;

    // Calibration interface
public:
    void save() override;
    void load() override;
};

class CalibrationAgr2 : public Calibration
{
    Q_OBJECT
public:
    explicit CalibrationAgr2();
    ~CalibrationAgr2();

    QDate getReagent_date() const;
    void setReagent_date(const QDate &value);

    QDate getK_plazma_date() const;
    void setK_plazma_date(const QDate &value);

    int getIncube_time_1() const;
    void setIncube_time_1(int value);

    int getIncube_time_2() const;
    void setIncube_time_2(int value);

    QString getReagent_serial() const;
    void setReagent_serial(const QString &value);

    QString getK_plazma_serial() const;
    void setK_plazma_serial(const QString &value);

    double getK_plazma() const;
    void setK_plazma(double value);

    double getLevel_0() const;
    void setLevel_0(double value);

    double getLevel_100() const;
    void setLevel_100(double value);

    double getC1() const;
    void setC1(double value);

    double getCk1() const;
    void setCk1(double value);

    double getC2() const;
    void setC2(double value);

    double getCk2() const;
    void setCk2(double value);

    double getC3() const;
    void setC3(double value);

    double getCk3() const;
    void setCk3(double value);

    double getC4() const;
    void setC4(double value);

    double getCk4() const;
    void setCk4(double value);

private:
    QDate reagent_date, k_plazma_date;
    QString reagent_serial, k_plazma_serial;

    int incube_time_1, incube_time_2;
    double k_plazma, level_0, level_100;
    double c1, ck1, c2, ck2, c3, ck3, c4, ck4;

    // Calibration interface
public:
    void save() override;
    void load() override;
};
#endif // KOAGRXML_H
