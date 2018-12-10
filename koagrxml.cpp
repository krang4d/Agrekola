#include "koagrxml.h"

CreateKoAgr::CreateKoAgr(QObject *parent) : QObject(parent)
{

}

QDomDocument CreateKoAgr::createTestKo(QString name) {

    QDomDocument document;
    QDomElement test = document.createElement(name);
    document.appendChild(test);

    QDomElement k1 = document.createElement("k1");
    k1.setAttribute("Value", "1");
    k1.setAttribute("Num", "num1");
    test.appendChild(k1);

    QDomElement k2 = document.createElement("k2");
    k2.setAttribute("Value", "1");
    k2.setAttribute("Num", "num2");
    test.appendChild(k2);

    QDomElement k3 = document.createElement("k3");
    k3.setAttribute("Value", "1");
    k3.setAttribute("Num", "num3");
    test.appendChild(k3);

    QDomElement k4 = document.createElement("k4");
    k4.setAttribute("Value", "1");
    k4.setAttribute("Num", "num4");
    test.appendChild(k4);

    QDomElement single = document.createElement("single");
    single.setAttribute("Value", "1");
    test.appendChild(single);

    return document;
}

QDomDocument CreateKoAgr::createTestAgr(QString name) {
    QDomDocument document = createTestKo(name);
    QDomElement test = document.firstChildElement(name);
    return document;
}

int CreateKoAgr::writeFile(QString name, QDomDocument doc)
{
    QFile file(name + QString(".xml"));
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Faild to open file for writting";
        return -1;
    } else {
        QTextStream stream(&file);
        stream << doc.toString();
        file.close();
    }
    file.close();
    return 0;
}

int CreateKoAgr::readFile(QString name, QDomDocument &doc)
{
    QFile file(name + QString(".xml"));
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Faild to open file for writting";
        return -1;
    } else {
        if(!doc.setContent(&file)) {
            qDebug() << "Failed to load document";
            return -2;
        }
        file.close();
    }
    return 0;
}

KoAgrXML::KoAgrXML(QObject *parent) : CreateKoAgr(parent)
{

}

QDomDocument KoAgrXML::createTestKo1()
{
    QString name("testKo1");
    QDomDocument document = createTestKo(name);
    writeFile(name, document);
    return document;
}

QDomDocument KoAgrXML::createTestKo2()
{
    QString name("testKo2");
    QDomDocument document = createTestKo(name);
    writeFile(name, document);
    return document;
}

QDomDocument KoAgrXML::createTestKo3()
{
    QString name("testKo3");
    QDomDocument document = createTestKo(name);
    writeFile(name, document);
    return document;
}

QDomDocument KoAgrXML::createTestKo4()
{
    QString name("testKo4");
    QDomDocument document = createTestKo(name);
    writeFile(name, document);
    return document;
}

QDomDocument KoAgrXML::createTestKo5()
{
    QString name("testKo5");
    QDomDocument document = createTestKo(name);
    writeFile(name, document);
    return document;
}

QDomDocument KoAgrXML::createTestAgr1()
{
    QString name("testAgr1");
    QDomDocument document = createTestAgr(name);
    writeFile(name, document);
    return document;
}

QDomDocument KoAgrXML::createTestAgr2()
{
    QString name("testAgr2");
    QDomDocument document = createTestAgr(name);
    writeFile(name, document);
    return document;
}

QDomDocument KoAgrXML::createCalibrationKo1()
{
    QString name("calibrationKo1");
    QDomDocument document;
    QDomElement calibration = document.createElement(name);
    document.appendChild(calibration);
    calibration.appendChild(document.createElement("date"));
    calibration.appendChild(document.createElement("reagent_serial"));
    calibration.appendChild(document.createElement("reagent_date"));

    calibration.appendChild(document.createElement("write_time"));
    calibration.appendChild(document.createElement("incube_time"));

    writeFile(name, document);
    return document;
}

QDomDocument KoAgrXML::createCalibrationKo2()
{
    QString name("calibrationKo2");
    QDomDocument document;
    QDomElement calibration = document.createElement(name);
    document.appendChild(calibration);
    calibration.appendChild(document.createElement("date"));
    calibration.appendChild(document.createElement("reagent_serial"));
    calibration.appendChild(document.createElement("reagent_date"));
    calibration.appendChild(document.createElement("k_plazma_serial"));
    calibration.appendChild(document.createElement("k_plazma_date"));
    calibration.appendChild(document.createElement("a4tv_k_plazma"));

    calibration.appendChild(document.createElement("write_time"));
    calibration.appendChild(document.createElement("incube_time"));

    writeFile(name, document);
    return document;
}

QDomDocument KoAgrXML::createCalibrationKo3()
{
    QString name("calibrationKo3");
    QDomDocument document;
    QDomElement calibration = document.createElement(name);
    document.appendChild(calibration);
    calibration.appendChild(document.createElement("date"));
    calibration.appendChild(document.createElement("reagent_serial"));
    calibration.appendChild(document.createElement("reagent_date"));
    calibration.appendChild(document.createElement("fibrinogen_k_plazma"));
    calibration.appendChild(document.createElement("time_k_plazma"));
    calibration.appendChild(document.createElement("fibrinogen_200_plazma"));
    calibration.appendChild(document.createElement("time_200_plazma"));
    calibration.appendChild(document.createElement("fibrinogen_50_plazma"));
    calibration.appendChild(document.createElement("time_50_plazma"));
    calibration.appendChild(document.createElement("fibrinogen_25_plazma"));
    calibration.appendChild(document.createElement("time_25_plazma"));

    calibration.appendChild(document.createElement("write_time"));
    calibration.appendChild(document.createElement("incube_time"));

    writeFile(name, document);
    return document;
}

QDomDocument KoAgrXML::createCalibrationKo4()
{
    QString name("calibrationKo4");
    QDomDocument document;
    QDomElement calibration = document.createElement(name);
    document.appendChild(calibration);
    calibration.appendChild(document.createElement("date"));
    calibration.appendChild(document.createElement("reagent_serial"));
    calibration.appendChild(document.createElement("reagent_date"));
    calibration.appendChild(document.createElement("k_plazma_serial"));
    calibration.appendChild(document.createElement("k_plazma_date"));
    calibration.appendChild(document.createElement("action"));
    calibration.appendChild(document.createElement("trombine_time"));
    calibration.appendChild(document.createElement("write_time"));
    calibration.appendChild(document.createElement("incube_time"));

    writeFile(name, document);
    return document;
}

QDomDocument KoAgrXML::createCalibrationKo5()
{
    QString name("calibrationKo5");
    QDomDocument document;
    QDomElement calibration = document.createElement(name);
    document.appendChild(calibration);
    calibration.appendChild(document.createElement("date"));
    calibration.appendChild(document.createElement("tromboplastin_serial"));
    calibration.appendChild(document.createElement("tromboplastin_date"));
    calibration.appendChild(document.createElement("k_plazma_serial"));
    calibration.appendChild(document.createElement("k_plazma_date"));
    calibration.appendChild(document.createElement("k_protrombine_index"));
    calibration.appendChild(document.createElement("k_protrombine_otn"));
    calibration.appendChild(document.createElement("protrombine_k_Kvik"));
    calibration.appendChild(document.createElement("time_k_Kvik"));

    calibration.appendChild(document.createElement("protrombine_50_Kvik"));
    calibration.appendChild(document.createElement("time_50_Kvik"));

    calibration.appendChild(document.createElement("protrombine_25_Kvik"));
    calibration.appendChild(document.createElement("time_25_Kvik"));

    calibration.appendChild(document.createElement("protrombine_12_Kvik"));
    calibration.appendChild(document.createElement("time_12_Kvik"));

    calibration.appendChild(document.createElement("protrombine_index"));
    calibration.appendChild(document.createElement("protrombine_otn"));

    calibration.appendChild(document.createElement("write_time"));
    calibration.appendChild(document.createElement("incube_time"));

    writeFile(name, document);
    return document;
}

QDomDocument KoAgrXML::createCalibrationAgr1()
{
    QString name("calibrationAgr1");
    QDomDocument document;
    QDomElement calibration = document.createElement(name);
    document.appendChild(calibration);
    //входные данные
    calibration.appendChild(document.createElement("date"));
    calibration.appendChild(document.createElement("reagent_serial"));
    calibration.appendChild(document.createElement("reagent_date"));
    calibration.appendChild(document.createElement("k_concentration"));
    //выходные данные
    calibration.appendChild(document.createElement("level_0"));
    calibration.appendChild(document.createElement("level_100"));

    calibration.appendChild(document.createElement("write_time"));
    calibration.appendChild(document.createElement("incube_time"));
    calibration.appendChild(document.createElement("incube_time_2"));

    writeFile(name, document);
    return document;
}

QDomDocument KoAgrXML::createCalibrationAgr2()
{
    QString name("calibrationAgr2");
    QDomDocument document;
    QDomElement calibration = document.createElement(name);
    document.appendChild(calibration);
    //входные данные
    calibration.appendChild(document.createElement("date"));

    calibration.appendChild(document.createElement("write_time"));
    calibration.appendChild(document.createElement("incube_time"));
    calibration.appendChild(document.createElement("incube_time_2"));

    calibration.appendChild(document.createElement("reagent_serial"));
    calibration.appendChild(document.createElement("reagent_date"));
    calibration.appendChild(document.createElement("k_plazma_serial"));
    calibration.appendChild(document.createElement("k_plazma_date"));
    calibration.appendChild(document.createElement("k_plazma"));
    //выходные данные
    calibration.appendChild(document.createElement("level_0"));
    calibration.appendChild(document.createElement("level_100"));

    calibration.appendChild(document.createElement("c1"));
    calibration.appendChild(document.createElement("ck1"));

    calibration.appendChild(document.createElement("c2"));
    calibration.appendChild(document.createElement("ck2"));

    calibration.appendChild(document.createElement("c3"));
    calibration.appendChild(document.createElement("ck3"));

    calibration.appendChild(document.createElement("c4"));
    calibration.appendChild(document.createElement("ck4"));

    writeFile(name, document);
    return document;
}

QDomDocument KoAgrXML::openTestKo1()
{
    QDomDocument doc;
    QString name("testKo1");
    if( QFile::exists(name + QString(".xml")) ) {
        readFile(name, doc);
    }
    else doc = createTestKo1();
    return doc;
}

QDomDocument KoAgrXML::openTestKo2()
{
    QDomDocument doc;
    QString name("testKo2");
    if( QFile::exists(name + QString(".xml")) ) {
        readFile(name, doc);
    }
    else doc = createTestKo2();
    return doc;
}

QDomDocument KoAgrXML::openTestKo3()
{
    QDomDocument doc;
    QString name("testKo3");
    if( QFile::exists(name + QString(".xml")) ) {
        readFile(name, doc);
    }
    else doc = createTestKo3();
    return doc;
}

QDomDocument KoAgrXML::openTestKo4()
{
    QDomDocument doc;
    QString name("testKo3");
    if( QFile::exists(name + QString(".xml")) ) {
        readFile(name, doc);
    }
    else doc = createTestKo4();
    return doc;
}

QDomDocument KoAgrXML::openTestKo5()
{
    QDomDocument doc;
    QString name("testKo5");
    if( QFile::exists(name + QString(".xml")) ) {
        readFile(name, doc);
    }
    else doc = createTestKo5();
    return doc;
}

QDomDocument KoAgrXML::openTestAgr1()
{
    QDomDocument doc;
    QString name("testAgr1");
    if( QFile::exists(name + QString(".xml")) ) {
        readFile(name, doc);
    }
    else doc = createTestAgr1();
    return doc;
}

QDomDocument KoAgrXML::openTestAgr2()
{
    QDomDocument doc;
    QString name("testAgr2");
    if( QFile::exists(name + QString(".xml")) ) {
        readFile(name, doc);
    }
    else doc = createTestAgr2();
    return doc;
}

QDomDocument KoAgrXML::openCalibrationKo1()
{
    QDomDocument doc;
    QString name("calibrationKo1");
    if( QFile::exists(name + QString(".xml")) ) {
        readFile(name, doc);
    }
    else doc = createCalibrationKo1();
    return doc;
}

QDomDocument KoAgrXML::openCalibrationKo2()
{
    QDomDocument doc;
    QString name("calibrationKo2");
    if( QFile::exists(name + QString(".xml")) ) {
        readFile(name, doc);
    }
    else doc = createCalibrationKo2();
    return doc;
}

QDomDocument KoAgrXML::openCalibrationKo3()
{
    QDomDocument doc;
    QString name("calibrationKo3");
    if( QFile::exists(name + QString(".xml")) ) {
        readFile(name, doc);
    }
    else doc = createCalibrationKo3();
    return doc;
}

QDomDocument KoAgrXML::openCalibrationKo4()
{
    QDomDocument doc;
    QString name("calibrationKo4");
    if( QFile::exists(name + QString(".xml")) ) {
        readFile(name, doc);
    }
    else doc = createCalibrationKo4();
    return doc;
}

QDomDocument KoAgrXML::openCalibrationKo5()
{
    QDomDocument doc;
    QString name("calibrationKo5");
    if( QFile::exists(name + QString(".xml")) ) {
        readFile(name, doc);
    }
    else doc = createCalibrationKo5();
    return doc;
}

QDomDocument KoAgrXML::openCalibrationAgr1()
{
    QDomDocument doc;
    QString name("calibrationAgr1");
    if( QFile::exists(name + QString(".xml")) ) {
        readFile(name, doc);
    }
    else doc = createCalibrationAgr1();
    return doc;
}

QDomDocument KoAgrXML::openCalibrationAgr2()
{
    QDomDocument doc;
    QString name("calibrationAgr2");
    if( QFile::exists(name + QString(".xml")) ) {
        readFile(name, doc);
    }
    else doc = createCalibrationAgr2();
    return doc;
}

void KoAgrXML::ListElement(QDomElement root, QString tagname, QString attribute)
{
    QDomNodeList items = root.elementsByTagName(tagname);
    qDebug() << "Total items = " << items.count();
    for(int i =0; i < items.count(); i++) {
        QDomNode itemnode = items.at(i);
        //convert to element
        if(itemnode.isElement()) {
            QDomElement itemele = itemnode.toElement();
            qDebug() << itemele.attribute(attribute);
        }
    }
}

QString KoAgrXML::getElement(QDomDocument root, QString tagname, QString attribute)
{
    QDomNodeList items = root.elementsByTagName(tagname);
    QDomNode itemnode = items.at(0);
    if( itemnode.isElement()) {
        QDomElement itemelement = itemnode.toElement();
        return itemelement.attribute(attribute);
    } else return QString("");
}

void KoAgrXML::setElement(QDomDocument &root, QString tagname, QString value, QString attribute)
{
    QDomNodeList items = root.elementsByTagName(tagname);
    QDomNode itemnode = items.at(0);
    if( itemnode.isElement()) {
        QDomElement itemelement = itemnode.toElement();
        itemelement.setAttribute(attribute, value);
    }
}

Test::Test(QDomDocument dom, QString n, QObject *parent)
    : QObject(parent), document(dom), name(n)
{
    load();
    //document = KoAgrXML::openTest();
}

Test::~Test()
{
    save();
    qDebug() << "TestKo1::~TestKo1()";
}

void Test::setK1(const int value)
{
    k1 = value;
}

int Test::getK1() const
{
    return k1;
}

void Test::setK2(const int value)
{
    k2 = value;
}

int Test::getK2() const
{
    return k2;
}

void Test::setK3(const int value)
{
    k3 = value;
}

int Test::getK3() const
{
    return k3;
}

void Test::setK4(const int value)
{
    k4 = value;
}

int Test::getK4() const
{
    return k4;
}

void Test::setSingle(const int value)
{
    single = value;
}

int Test::getSingle() const
{
    return single;
}

QString Test::getText() const
{
    return document.toString();
}

QDomDocument Test::getDoc() const
{
    return document;
}

QString Test::getName() const
{
    return name;
}

QString Test::getNum4() const
{
    return num4;
}

void Test::setNum4(const QString &value)
{
    num4 = value;
}

void Test::save()
{
    KoAgrXML::setElement(document, QString("k1"), QString("%1").arg(k1));
    KoAgrXML::setElement(document, QString("k2"), QString("%1").arg(k2));
    KoAgrXML::setElement(document, QString("k3"), QString("%1").arg(k3));
    KoAgrXML::setElement(document, QString("k4"), QString("%1").arg(k4));
    KoAgrXML::setElement(document, QString("single"), QString("%1").arg(single));

    KoAgrXML::setElement(document, QString("k1"), QString("%1").arg(k1), "Num");
    KoAgrXML::setElement(document, QString("k2"), QString("%1").arg(k2), "Num");
    KoAgrXML::setElement(document, QString("k3"), QString("%1").arg(k3), "Num");
    KoAgrXML::setElement(document, QString("k4"), QString("%1").arg(k4), "Num");

    CreateKoAgr::writeFile(name, document);
    qDebug() << "Test::save()";
}

void Test::load()
{
    QString value;
    value = KoAgrXML::getElement(document, QString("k1"));
    k1 = value.toInt();

    value = KoAgrXML::getElement(document, QString("k2"));
    k2 = value.toInt();

    value = KoAgrXML::getElement(document, QString("k3"));
    k3 = value.toInt();

    value = KoAgrXML::getElement(document, QString("k4"));
    k4 = value.toInt();

    value = KoAgrXML::getElement(document, QString("single"));
    single = value.toInt();

    num1 = KoAgrXML::getElement(document, QString("k1"), "Num");
    num2 = KoAgrXML::getElement(document, QString("k2"), "Num");
    num3 = KoAgrXML::getElement(document, QString("k3"), "Num");
    num4 = KoAgrXML::getElement(document, QString("k4"), "Num");
}

QString Test::getNum3() const
{
    return num3;
}

void Test::setNum3(const QString &value)
{
    num3 = value;
}

QString Test::getNum2() const
{
    return num2;
}

void Test::setNum2(const QString &value)
{
    num2 = value;
}

QString Test::getNum1() const
{
    return num1;
}

void Test::setNum1(const QString &value)
{
    num1 = value;
}

TestKo1::TestKo1(QObject *parent)
    : Test(KoAgrXML::createTestKo1(), "testKo1", parent)
{}

TestKo1::~TestKo1()
{
    qDebug() << "~TestKo1()";
}

TestKo2::TestKo2(QObject *parent)
    : Test(KoAgrXML::createTestKo2(), "testKo2", parent)
{}

TestKo2::~TestKo2()
{}

TestKo3::TestKo3(QObject *parent)
    : Test(KoAgrXML::createTestKo3(), "testKo3", parent)
{}

TestKo3::~TestKo3()
{}

TestKo4::TestKo4(QObject *parent)
    : Test(KoAgrXML::createTestKo4(), "testKo4", parent)
{}

TestKo4::~TestKo4()
{}

TestKo5::TestKo5(QObject *parent)
    : Test(KoAgrXML::createTestKo5(), "testKo5", parent)
{}

TestKo5::~TestKo5()
{}

TestAgr1::TestAgr1(QObject *parent)
    : Test(KoAgrXML::createTestAgr1(), "testAgr1", parent)
{}

TestAgr1::~TestAgr1()
{}

TestAgr2::TestAgr2(QObject *parent)
    : Test(KoAgrXML::createTestAgr2(), "testAgr2", parent)
{}

TestAgr2::~TestAgr2()
{}

Calibration::Calibration(QDomDocument doc, QString n, QObject *parent)
    : QObject(parent), document(doc), name(n)
{
    load();
//    QString value;
//    value = KoAgrXML::getElement(document, QString("date"));
//    date = QDate::fromString(value, "yyyyMMdd");

//    value = KoAgrXML::getElement(document, QString("write_time"));
//    write_time = value.toInt();

//    value = KoAgrXML::getElement(document, QString("incube_time"));
//    incube_time = value.toInt();
}

Calibration::~Calibration()
{
//    KoAgrXML::setElement(document, QString("date"), QString("%1").arg(date.toString(QString("yyyyMMdd"))));
//    KoAgrXML::setElement(document, QString("write_time"), QString("%1").arg(write_time));
//    KoAgrXML::setElement(document, QString("incube_time"), QString("%1").arg(incube_time));
//    CreateKoAgr::writeFile(name, document);
    save();
}

QDate Calibration::getDate() const
{
    return date;
}

void Calibration::setDate(const QDate &value)
{
    date = value;
}

int Calibration::getWrite_time() const
{
    return write_time;
}

void Calibration::setWrite_time(const int value)
{
    write_time = value;
}

int Calibration::getIncube_time() const
{

    return incube_time;
}

void Calibration::setIncube_time(int value)
{
    incube_time = value;
}

void Calibration::save()
{
    KoAgrXML::setElement(document, QString("date"), QString("%1").arg(date.toString("yyyyMMdd")));
    KoAgrXML::setElement(document, QString("write_time"), QString("%1").arg(write_time));
    KoAgrXML::setElement(document, QString("incube_time"), QString("%1").arg(incube_time));
    CreateKoAgr::writeFile(name, document);
    qDebug() << "Calibration::save()";
}

void Calibration::load()
{
    QString value;
    value = KoAgrXML::getElement(document, QString("date"));
    date = QDate::fromString(value, QString("yyyyMMdd"));

    value = KoAgrXML::getElement(document, QString("write_time"));
    write_time = value.toInt();

    value = KoAgrXML::getElement(document, QString("incube_time"));
    incube_time = value.toInt();
}

QDomDocument Calibration::getDoc() const
{
    return document;
}

QString Calibration::getName() const
{
    return name;
}

CalibrationKo1::CalibrationKo1()
    : Calibration(KoAgrXML::createCalibrationKo1(), "calibrationKo1")
{
    //Calibration::setDoc(KoAgrXML::createCalibrationKo1());
    //Calibration::setName("calibrationKo1");
}

CalibrationKo1::~CalibrationKo1()
{}

CalibrationKo2::CalibrationKo2()
    : Calibration(KoAgrXML::createCalibrationKo2(), "calibrationKo2")
{
    load();
    //Calibration::setDoc(KoAgrXML::createCalibrationKo2());
    //Calibration::setName("calibrationKo2");
}

CalibrationKo2::~CalibrationKo2()
{
    save();
}

QDate CalibrationKo2::getReagent_date() const
{
    //QString value = KoAgrXML::getElement(Calibration::getDoc(), QString("reagent_date"));
    return reagent_date;
}

void CalibrationKo2::setReagent_date(const QDate &value)
{
    reagent_date = value;
}

QDate CalibrationKo2::getK_plazma_date() const
{
    return k_plazma_date;
}

void CalibrationKo2::setK_plazma_date(const QDate &value)
{
    k_plazma_date = value;
}

QString CalibrationKo2::getReagent_serial() const
{
    return reagent_serial;
}

void CalibrationKo2::setReagent_serial(const QString &value)
{
    reagent_serial = value;
}

QString CalibrationKo2::getK_plazma_serial() const
{
    return k_plazma_serial;
}

void CalibrationKo2::setK_plazma_serial(const QString &value)
{
    k_plazma_serial = value;
}

double CalibrationKo2::getA4tv_k_plazma() const
{
    return a4tv_k_plazma;
}

void CalibrationKo2::setA4tv_k_plazma(double value)
{
    a4tv_k_plazma = value;
}

void CalibrationKo2::save()
{
    KoAgrXML::setElement(document, QString("reaget_date"), reagent_date.toString("yyyyMMdd"));
    KoAgrXML::setElement(document, QString("k_plazma_date"), k_plazma_date.toString("yyyyMMdd"));
    KoAgrXML::setElement(document, QString("reagent_serial"), reagent_serial);
    KoAgrXML::setElement(document, QString("k_plazma_serial"), k_plazma_serial);
    KoAgrXML::setElement(document, QString("a4tv_k_plazma"), QString("%1").arg(a4tv_k_plazma));
    CreateKoAgr::writeFile(name, document);
    qDebug() << "CalibrationKo2::save()";
}

void CalibrationKo2::load()
{
    QString value;
    value = KoAgrXML::getElement(document, QString("reagent_date"));
    reagent_date = QDate::fromString(value, QString("yyyyMMdd"));

    value = KoAgrXML::getElement(document, QString("k_plazma_date"));
    k_plazma_date = QDate::fromString(value, QString("yyyyMMdd"));

    value = KoAgrXML::getElement(document, QString("reagent_serial"));
    reagent_serial = value.toInt();

    value = KoAgrXML::getElement(document, QString("k_plazma_serial"));
    k_plazma_serial = value.toInt();

    value = KoAgrXML::getElement(document, QString("a4tv_k_plazma"));
    a4tv_k_plazma = value.toInt();
}

CalibrationKo3::CalibrationKo3()
    : Calibration(KoAgrXML::createCalibrationKo3(), "calibrationKo3")
{
    load();
}

CalibrationKo3::~CalibrationKo3()
{
    save();
}

QDate CalibrationKo3::getReagent_date() const
{
    return reagent_date;
}

void CalibrationKo3::setReagent_date(const QDate &value)
{
    reagent_date = value;
}

QString CalibrationKo3::getReagent_serial() const
{
    return reagent_serial;
}

void CalibrationKo3::setReagent_serial(const QString &value)
{
    reagent_serial = value;
}

double CalibrationKo3::getFibrinogen_k_plazma() const
{
    return fibrinogen_k_plazma;
}

void CalibrationKo3::setFibrinogen_k_plazma(double value)
{
    fibrinogen_k_plazma = value;
}

double CalibrationKo3::getTime_k_plazma() const
{
    return time_k_plazma;
}

void CalibrationKo3::setTime_k_plazma(double value)
{
    time_k_plazma = value;
}

double CalibrationKo3::getFibrinogen_200_plazma() const
{
    return fibrinogen_200_plazma;
}

void CalibrationKo3::setFibrinogen_200_plazma(double value)
{
    fibrinogen_200_plazma = value;
}

double CalibrationKo3::getTime_200_plazma() const
{
    return time_200_plazma;
}

void CalibrationKo3::setTime_200_plazma(double value)
{
    time_200_plazma = value;
}

double CalibrationKo3::getFibrinogen_50_plazma() const
{
    return fibrinogen_50_plazma;
}

void CalibrationKo3::setFibrinogen_50_plazma(double value)
{
    fibrinogen_50_plazma = value;
}

double CalibrationKo3::getTime_50_plazma() const
{
    return time_50_plazma;
}

void CalibrationKo3::setTime_50_plazma(double value)
{
    time_50_plazma = value;
}

double CalibrationKo3::getFibrinogen_25_plazma() const
{
    return fibrinogen_25_plazma;
}

void CalibrationKo3::setFibrinogen_25_plazma(double value)
{
    fibrinogen_25_plazma = value;
}

double CalibrationKo3::getTime_25_plazma() const
{
    return time_25_plazma;
}

void CalibrationKo3::setTime_25_plazma(double value)
{
    time_25_plazma = value;
}

void CalibrationKo3::save()
{
    KoAgrXML::setElement(document, QString("reagent_date"), reagent_date.toString("yyyyMMdd"));
    KoAgrXML::setElement(document, QString("reagent_serial"), reagent_serial);

    KoAgrXML::setElement(document, QString("fibrinogen_k_plazma"), QString("%1").arg(fibrinogen_k_plazma));
    KoAgrXML::setElement(document, QString("time_k_plazma"), QString("%1").arg(time_k_plazma));

    KoAgrXML::setElement(document, QString("fibrinogen_200_plazma"), QString("%1").arg(fibrinogen_200_plazma));
    KoAgrXML::setElement(document, QString("time_200_plazma"), QString("%1").arg(time_200_plazma));

    KoAgrXML::setElement(document, QString("fibrinogen_50_plazma"), QString("%1").arg(fibrinogen_50_plazma));
    KoAgrXML::setElement(document, QString("time_50_plazma"), QString("%1").arg(time_50_plazma));

    KoAgrXML::setElement(document, QString("fibrinogen_25_plazma"), QString("%1").arg(fibrinogen_25_plazma));
    KoAgrXML::setElement(document, QString("time_25_plazma"), QString("%1").arg(time_25_plazma));

    CreateKoAgr::writeFile(name, document);
    qDebug() << "CalibrationKo3::save()";
}

void CalibrationKo3::load()
{
    QString value;
    value = KoAgrXML::getElement(document, QString("reagent_date"));
    reagent_date = QDate::fromString(value, QString("yyyyMMdd"));

    value = KoAgrXML::getElement(document, QString("reagent_serial"));
    reagent_serial = value;

    value = KoAgrXML::getElement(document, QString("fibrinogen_k_plazma"));
    fibrinogen_k_plazma = value.toDouble();

    value = KoAgrXML::getElement(document, QString("time_k_plazma"));
    time_k_plazma = value.toDouble();

    value = KoAgrXML::getElement(document, QString("fibrinogen_200_plazma"));
    fibrinogen_200_plazma = value.toDouble();

    value = KoAgrXML::getElement(document, QString("time_200_plazma"));
    time_200_plazma = value.toDouble();

    value = KoAgrXML::getElement(document, QString("fibrinogen_50_plazma"));
    fibrinogen_50_plazma = value.toDouble();

    value = KoAgrXML::getElement(document, QString("time_50_plazma"));
    time_50_plazma = value.toDouble();

    value = KoAgrXML::getElement(document, QString("fibrinogen_25_plazma"));
    fibrinogen_25_plazma = value.toDouble();

    value = KoAgrXML::getElement(document, QString("time_25_plazma"));
    time_25_plazma = value.toDouble();
}

CalibrationKo4::CalibrationKo4()
    : Calibration(KoAgrXML::createCalibrationKo4(), "calibrationKo4")
{
    load();
}

CalibrationKo4::~CalibrationKo4()
{
    save();
}

QDate CalibrationKo4::getReagent_date() const
{
    return reagent_date;
}

void CalibrationKo4::setReagent_date(const QDate &value)
{
    reagent_date = value;
}

QDate CalibrationKo4::getK_plazma_date() const
{
    return k_plazma_date;
}

void CalibrationKo4::setK_plazma_date(const QDate &value)
{
    k_plazma_date = value;
}

QString CalibrationKo4::getReagent_serial() const
{
    return reagent_serial;
}

void CalibrationKo4::setReagent_serial(const QString &value)
{
    reagent_serial = value;
}

QString CalibrationKo4::getK_plazma_serial() const
{
    return k_plazma_serial;
}

void CalibrationKo4::setK_plazma_serial(const QString &value)
{
    k_plazma_serial = value;
}

QString CalibrationKo4::getAction() const
{
    return action;
}

void CalibrationKo4::setAction(const QString &value)
{
    action = value;
}

double CalibrationKo4::getTrombine_time() const
{
    return trombine_time;
}

void CalibrationKo4::setTrombine_time(double value)
{
    trombine_time = value;
}

void CalibrationKo4::save()
{
    KoAgrXML::setElement(document, QString("reagent_date"), reagent_date.toString("yyyyMMdd"));
    KoAgrXML::setElement(document, QString("k_plazma_date"), k_plazma_date.toString("yyyyMMdd"));

    KoAgrXML::setElement(document, QString("reagent_serial"), reagent_serial);
    KoAgrXML::setElement(document, QString("k_plazma_serial"), k_plazma_serial);

    KoAgrXML::setElement(document, QString("action"), action);


    KoAgrXML::setElement(document, QString("trombine_time"), QString("%1").arg(trombine_time));

    CreateKoAgr::writeFile(name, document);
    qDebug() << "CalibrationKo4::save()";
}

void CalibrationKo4::load()
{
    QString value;
    value = KoAgrXML::getElement(document, QString("reagent_date"));
    reagent_date = QDate::fromString(value, QString("yyyyMMdd"));

    value = KoAgrXML::getElement(document, QString("k_plazma_date"));
    k_plazma_date = QDate::fromString(value, QString("yyyyMMdd"));

    value = KoAgrXML::getElement(document, QString("reagent_serial"));
    reagent_serial = value;

    value = KoAgrXML::getElement(document, QString("k_plazma_serial"));
    k_plazma_serial = value;

    value = KoAgrXML::getElement(document, QString("action"));
    action = value;

    value = KoAgrXML::getElement(document, QString("trombine_time"));
    trombine_time = value.toDouble();
}

CalibrationKo5::CalibrationKo5()
    : Calibration(KoAgrXML::createCalibrationKo5(), "calibrationKo5")
{
    load();
}

CalibrationKo5::~CalibrationKo5()
{
    save();
}

QDate CalibrationKo5::getTromboplastin_date() const
{
    return tromboplastin_date;
}

void CalibrationKo5::setTromboplastin_date(const QDate &value)
{
    tromboplastin_date = value;
}

QDate CalibrationKo5::getK_plazma_date() const
{
    return k_plazma_date;
}

void CalibrationKo5::setK_plazma_date(const QDate &value)
{
    k_plazma_date = value;
}

QString CalibrationKo5::getTromboplastin_serial() const
{
    return tromboplastin_serial;
}

void CalibrationKo5::setTromboplastin_serial(const QString &value)
{
    tromboplastin_serial = value;
}

QString CalibrationKo5::getK_plazma_serial() const
{
    return k_plazma_serial;
}

void CalibrationKo5::setK_plazma_serial(const QString &value)
{
    k_plazma_serial = value;
}

double CalibrationKo5::getK_protrombine_index() const
{
    return k_protrombine_index;
}

void CalibrationKo5::setK_protrombine_index(double value)
{
    k_protrombine_index = value;
}

double CalibrationKo5::getK_protrombine_otn() const
{
    return k_protrombine_otn;
}

void CalibrationKo5::setK_protrombine_otn(double value)
{
    k_protrombine_otn = value;
}

double CalibrationKo5::getProtrombine_k_Kvik() const
{
    return protrombine_k_Kvik;
}

void CalibrationKo5::setProtrombine_k_Kvik(double value)
{
    protrombine_k_Kvik = value;
}

double CalibrationKo5::getTime_k_Kvik() const
{
    return time_k_Kvik;
}

void CalibrationKo5::setTime_k_Kvik(double value)
{
    time_k_Kvik = value;
}

double CalibrationKo5::getProtrombine_50_Kvik() const
{
    return protrombine_50_Kvik;
}

void CalibrationKo5::setProtrombine_50_Kvik(double value)
{
    protrombine_50_Kvik = value;
}

double CalibrationKo5::getTime_50_Kvik() const
{
    return time_50_Kvik;
}

void CalibrationKo5::setTime_50_Kvik(double value)
{
    time_50_Kvik = value;
}

double CalibrationKo5::getProtrombine_25_Kvik() const
{
    return protrombine_25_Kvik;
}

void CalibrationKo5::setProtrombine_25_Kvik(double value)
{
    protrombine_25_Kvik = value;
}

double CalibrationKo5::getTime_25_Kvik() const
{
    return time_25_Kvik;
}

void CalibrationKo5::setTime_25_Kvik(double value)
{
    time_25_Kvik = value;
}

double CalibrationKo5::getProtrombine_12_Kvik() const
{
    return protrombine_12_Kvik;
}

void CalibrationKo5::setProtrombine_12_Kvik(double value)
{
    protrombine_12_Kvik = value;
}

double CalibrationKo5::getTime_12_Kvik() const
{
    return time_12_Kvik;
}

void CalibrationKo5::setTime_12_Kvik(double value)
{
    time_12_Kvik = value;
}

double CalibrationKo5::getProtrombine_index() const
{
    return protrombine_index;
}

void CalibrationKo5::setProtrombine_index(double value)
{
    protrombine_index = value;
}

double CalibrationKo5::getProtrombine_otn() const
{
    return protrombine_otn;
}

void CalibrationKo5::setProtrombine_otn(double value)
{
    protrombine_otn = value;
}

void CalibrationKo5::save()
{
    KoAgrXML::setElement(document, QString("tromboplastin_date"), tromboplastin_date.toString("yyyyMMdd"));
    KoAgrXML::setElement(document, QString("k_plazma_date"), k_plazma_date.toString("yyyyMMdd"));

    KoAgrXML::setElement(document, QString("tromboplastin_serial"), tromboplastin_serial);
    KoAgrXML::setElement(document, QString("k_plazma_serial"), k_plazma_serial);

    KoAgrXML::setElement(document, QString("k_protrombine_index"), QString("%1").arg(k_protrombine_index));
    KoAgrXML::setElement(document, QString("k_protrombine_otn"), QString("%1").arg(k_protrombine_otn));
    KoAgrXML::setElement(document, QString("protrombine_k_Kvik"), QString("%1").arg(protrombine_k_Kvik));
    KoAgrXML::setElement(document, QString("time_k_Kvik"), QString("%1").arg(time_k_Kvik));
    KoAgrXML::setElement(document, QString("protrombine_50_Kvik"), QString("%1").arg(protrombine_50_Kvik));
    KoAgrXML::setElement(document, QString("time_50_Kvik"), QString("%1").arg(time_50_Kvik));
    KoAgrXML::setElement(document, QString("protrombine_25_Kvik"), QString("%1").arg(protrombine_25_Kvik));
    KoAgrXML::setElement(document, QString("time_25_Kvik"), QString("%1").arg(time_25_Kvik));
    KoAgrXML::setElement(document, QString("protrombine_12_Kvik"), QString("%1").arg(protrombine_12_Kvik));
    KoAgrXML::setElement(document, QString("time_12_Kvik"), QString("%1").arg(time_12_Kvik));
    KoAgrXML::setElement(document, QString("protrombine_index"), QString("%1").arg(protrombine_index));
    KoAgrXML::setElement(document, QString("protrombine_otn"), QString("%1").arg(protrombine_otn));

    CreateKoAgr::writeFile(name, document);
    qDebug() << "CalibrationKo5::save()";
}

void CalibrationKo5::load()
{
    QString value;
    value = KoAgrXML::getElement(document, QString("tromboplastin_date"));
    tromboplastin_date = QDate::fromString(value, QString("yyyyMMdd"));

    value = KoAgrXML::getElement(document, QString("k_plazma_date"));
    k_plazma_date = QDate::fromString(value, QString("yyyyMMdd"));

    value = KoAgrXML::getElement(document, QString("tromboplastin_serial"));
    tromboplastin_serial = value;

    value = KoAgrXML::getElement(document, QString("k_plazma_serial"));
    k_plazma_serial = value;

    value = KoAgrXML::getElement(document, QString("k_protrombine_index"));
    k_protrombine_index = value.toDouble();
    value = KoAgrXML::getElement(document, QString("k_protrombine_otn"));
    k_protrombine_otn = value.toDouble();

    value = KoAgrXML::getElement(document, QString("protrombine_k_Kvik"));
    protrombine_k_Kvik = value.toDouble();
    value = KoAgrXML::getElement(document, QString("time_k_Kvik"));
    time_k_Kvik = value.toDouble();

    value = KoAgrXML::getElement(document, QString("protrombine_50_Kvik"));
    protrombine_50_Kvik = value.toDouble();
    value = KoAgrXML::getElement(document, QString("time_50_Kvik"));
    time_50_Kvik = value.toDouble();
    value = KoAgrXML::getElement(document, QString("protrombine_25_Kvik"));
    protrombine_25_Kvik = value.toDouble();
    value = KoAgrXML::getElement(document, QString("time_25_Kvik"));
    time_25_Kvik = value.toDouble();
    value = KoAgrXML::getElement(document, QString("protrombine_12_Kvik"));
    protrombine_12_Kvik = value.toDouble();
    value = KoAgrXML::getElement(document, QString("time_12_Kvik"));
    time_12_Kvik = value.toDouble();
    value = KoAgrXML::getElement(document, QString("protrombine_index"));
    protrombine_index = value.toDouble();
    value = KoAgrXML::getElement(document, QString("protrombine_otn"));
    protrombine_otn = value.toDouble();
}

CalibrationAgr1::CalibrationAgr1()
    : Calibration(KoAgrXML::createCalibrationAgr1(), "calibrationAgr1")
{
    load();
}

CalibrationAgr1::~CalibrationAgr1()
{
    save();
}

QDate CalibrationAgr1::getReagent_date() const
{
    return reagent_date;
}

void CalibrationAgr1::setReagent_date(const QDate &value)
{
    reagent_date = value;
}

QString CalibrationAgr1::getReagent_serial() const
{
    return reagent_serial;
}

void CalibrationAgr1::setReagent_serial(const QString &value)
{
    reagent_serial = value;
}

double CalibrationAgr1::getK_concentration() const
{
    return k_concentration;
}

void CalibrationAgr1::setK_concentration(double value)
{
    k_concentration = value;
}

double CalibrationAgr1::getLevel_0() const
{
    return level_0;
}

void CalibrationAgr1::setLevel_0(double value)
{
    level_0 = value;
}

double CalibrationAgr1::getLevel_100() const
{
    return level_100;
}

void CalibrationAgr1::setLevel_100(double value)
{
    level_100 = value;
}

void CalibrationAgr1::save()
{
    KoAgrXML::setElement(document, QString("reagent_date"), reagent_date.toString("yyyyMMdd"));

    KoAgrXML::setElement(document, QString("reagent_serial"), reagent_serial);
    KoAgrXML::setElement(document, QString("k_concentration"), QString("%1").arg(k_concentration));
    KoAgrXML::setElement(document, QString("level_0"), QString("%1").arg(level_0));
    KoAgrXML::setElement(document, QString("level_100"), QString("%1").arg(level_100));

    CreateKoAgr::writeFile(name, document);
    qDebug() << "CalibrationKo4::save()";
}

void CalibrationAgr1::load()
{
    QString value;
    value = KoAgrXML::getElement(document, QString("reagent_date"));
    reagent_date = QDate::fromString(value, QString("yyyyMMdd"));

    value = KoAgrXML::getElement(document, QString("reagent_serial"));
    reagent_serial = value;

    value = KoAgrXML::getElement(document, QString("k_concentration"));
    k_concentration = value.toDouble();

    value = KoAgrXML::getElement(document, QString("level_0"));
    level_0 = value.toDouble();

    value = KoAgrXML::getElement(document, QString("level_100"));
    level_100 = value.toDouble();
}

CalibrationAgr2::CalibrationAgr2()
    : Calibration(KoAgrXML::createCalibrationAgr2(), "calibrationAgr2")
{
    load();
}

CalibrationAgr2::~CalibrationAgr2()
{
    save();
}

QDate CalibrationAgr2::getReagent_date() const
{
    return reagent_date;
}

void CalibrationAgr2::setReagent_date(const QDate &value)
{
    reagent_date = value;
}

QDate CalibrationAgr2::getK_plazma_date() const
{
    return k_plazma_date;
}

void CalibrationAgr2::setK_plazma_date(const QDate &value)
{
    k_plazma_date = value;
}

int CalibrationAgr2::getIncube_time_1() const
{
    return incube_time_1;
}

void CalibrationAgr2::setIncube_time_1(int value)
{
    incube_time_1 = value;
}

int CalibrationAgr2::getIncube_time_2() const
{
    return incube_time_2;
}

void CalibrationAgr2::setIncube_time_2(int value)
{
    incube_time_2 = value;
}

QString CalibrationAgr2::getReagent_serial() const
{
    return reagent_serial;
}

void CalibrationAgr2::setReagent_serial(const QString &value)
{
    reagent_serial = value;
}

QString CalibrationAgr2::getK_plazma_serial() const
{
    return k_plazma_serial;
}

void CalibrationAgr2::setK_plazma_serial(const QString &value)
{
    k_plazma_serial = value;
}

double CalibrationAgr2::getK_plazma() const
{
    return k_plazma;
}

void CalibrationAgr2::setK_plazma(double value)
{
    k_plazma = value;
}

double CalibrationAgr2::getLevel_0() const
{
    return level_0;
}

void CalibrationAgr2::setLevel_0(double value)
{
    level_0 = value;
}

double CalibrationAgr2::getLevel_100() const
{
    return level_100;
}

void CalibrationAgr2::setLevel_100(double value)
{
    level_100 = value;
}

double CalibrationAgr2::getC1() const
{
    return c1;
}

void CalibrationAgr2::setC1(double value)
{
    c1 = value;
}

double CalibrationAgr2::getCk1() const
{
    return ck1;
}

void CalibrationAgr2::setCk1(double value)
{
    ck1 = value;
}

double CalibrationAgr2::getC2() const
{
    return c2;
}

void CalibrationAgr2::setC2(double value)
{
    c2 = value;
}

double CalibrationAgr2::getCk2() const
{
    return ck2;
}

void CalibrationAgr2::setCk2(double value)
{
    ck2 = value;
}

double CalibrationAgr2::getC3() const
{
    return c3;
}

void CalibrationAgr2::setC3(double value)
{
    c3 = value;
}

double CalibrationAgr2::getCk3() const
{
    return ck3;
}

void CalibrationAgr2::setCk3(double value)
{
    ck3 = value;
}

double CalibrationAgr2::getC4() const
{
    return c4;
}

void CalibrationAgr2::setC4(double value)
{
    c4 = value;
}

double CalibrationAgr2::getCk4() const
{
    return ck4;
}

void CalibrationAgr2::setCk4(double value)
{
    ck4 = value;
}

void CalibrationAgr2::save()
{
    KoAgrXML::setElement(document, QString("reagent_date"), reagent_date.toString("yyyyMMdd"));
    KoAgrXML::setElement(document, QString("k_plazma_date"), k_plazma_date.toString("yyyyMMdd"));

    KoAgrXML::setElement(document, QString("reagent_serial"), reagent_serial);
    KoAgrXML::setElement(document, QString("k_plazma_serial"), k_plazma_serial);

    KoAgrXML::setElement(document, QString("incube_time_1"), QString("%1").arg(incube_time_1));
    KoAgrXML::setElement(document, QString("incube_time_2"), QString("%1").arg(incube_time_2));

    KoAgrXML::setElement(document, QString("k_plazma"), QString("%1").arg(k_plazma));
    KoAgrXML::setElement(document, QString("level_0"), QString("%1").arg(level_0));
    KoAgrXML::setElement(document, QString("level_100"), QString("%1").arg(level_100));


    KoAgrXML::setElement(document, QString("c1"), QString("%1").arg(c1));
    KoAgrXML::setElement(document, QString("ck1"), QString("%1").arg(ck1));
    KoAgrXML::setElement(document, QString("c2"), QString("%1").arg(c2));
    KoAgrXML::setElement(document, QString("ck2"), QString("%1").arg(ck2));
    KoAgrXML::setElement(document, QString("c3"), QString("%1").arg(c3));
    KoAgrXML::setElement(document, QString("ck3"), QString("%1").arg(ck3));
    KoAgrXML::setElement(document, QString("c4"), QString("%1").arg(c4));
    KoAgrXML::setElement(document, QString("ck4"), QString("%1").arg(ck4));

    CreateKoAgr::writeFile(name, document);
    qDebug() << "CalibrationKo5::save()";
}

void CalibrationAgr2::load()
{
    QString value;
    value = KoAgrXML::getElement(document, QString("reagent_date"));
    reagent_date = QDate::fromString(value, QString("yyyyMMdd"));

    value = KoAgrXML::getElement(document, QString("k_plazma_date"));
    k_plazma_date = QDate::fromString(value, QString("yyyyMMdd"));

    value = KoAgrXML::getElement(document, QString("reagent_serial"));
    reagent_serial = value;

    value = KoAgrXML::getElement(document, QString("k_plazma_serial"));
    k_plazma_serial = value;

    value = KoAgrXML::getElement(document, QString("incube_time_1"));
    incube_time_1 = value.toDouble();

    value = KoAgrXML::getElement(document, QString("incube_time_2"));
    incube_time_2 = value.toDouble();

    value = KoAgrXML::getElement(document, QString("k_plazma"));
    k_plazma = value.toDouble();
    value = KoAgrXML::getElement(document, QString("level_0"));
    level_0 = value.toDouble();
    value = KoAgrXML::getElement(document, QString("level_100"));
    level_100 = value.toDouble();

    value = KoAgrXML::getElement(document, QString("c1"));
    c1 = value.toDouble();
    value = KoAgrXML::getElement(document, QString("ck1"));
    ck1 = value.toDouble();
    value = KoAgrXML::getElement(document, QString("c2"));
    c2 = value.toDouble();
    value = KoAgrXML::getElement(document, QString("ck2"));
    ck2 = value.toDouble();
    value = KoAgrXML::getElement(document, QString("c3"));
    c3 = value.toDouble();
    value = KoAgrXML::getElement(document, QString("ck3"));
    ck3 = value.toDouble();
    value = KoAgrXML::getElement(document, QString("c4"));
    c4 = value.toDouble();
    value = KoAgrXML::getElement(document, QString("ck4"));
    ck4 = value.toDouble();
}
