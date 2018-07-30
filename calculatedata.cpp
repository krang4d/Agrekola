#include "calculatedata.h"

CalculateData::CalculateData(QObject *parent) : QObject(parent)
{

}

CalculateData::CalculateData(QMap<double, double> map, QObject *parent) : CalculateData(parent)
{
    mdata = map;
}

void CalculateArg1::calc()
{
    QMapIterator<double, double> it(mdata);
    double sum = std::accumulate(mdata.begin(), mdata.end() , 0);
    double avg = sum/mdata.size();
    while(it.hasNext()) {
        ;
    }
    qDebug().noquote() << "sum = " << QString("%1").arg(sum) << "avg = " << QString("%1").arg(avg);
}
