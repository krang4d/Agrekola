#include <QApplication>
#include <QString>
#include <QtConcurrent>
#include <QThread>
#include <QDebug>
#include <QVector>

#include "choisedialog.h"
#include "useE154.h"
/*
void looper(useE154 *a)
{
    a->funThread();
    QThread::currentThread()->msleep(100);
//    QVector<double> vec_data(4);
//    qDebug() << "looper thread ID" <<QThread::currentThreadId();
//    qDebug() << a->GetInformation();
//    for(int i=0; i<10; i++)
//    {
//        vec_data = a->AdcKADR();
//        qDebug() << i << " " << vec_data[0] << " " << vec_data[1] << " " << vec_data[2] << " " << vec_data[3];
//        QThread::currentThread()->msleep(100);
//    }
}

void thread_finish()
{
    qDebug() << "thread_finish()";
}
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "main thread ID: " << QThread::currentThreadId();
    useE154 *agrekola = new useE154;
    ChoiseDialog choiseDlg(agrekola);
    choiseDlg.show();
    //QFutureWatcher<void> futureWatcher;;

//    QWidget::connect(choiseDlg, SIGNAL(onMixCh1(bool)), agrekola, SLOT(onMixCh1(bool)));
//    QWidget::connect(choiseDlg, SIGNAL(onMixCh2(bool)), agrekola, SLOT(onMixCh2(bool)));
//    QWidget::connect(choiseDlg, SIGNAL(onMixCh3(bool)), agrekola, SLOT(onMixCh3(bool)));
//    QWidget::connect(choiseDlg, SIGNAL(onMixCh4(bool)), agrekola, SLOT(onMixCh4(bool)));
//    QWidget::connect(choiseDlg, SIGNAL(onMixPP(bool)), agrekola, SLOT(onMixPP(bool)));
//    QWidget::connect(choiseDlg, SIGNAL(onLaser(bool)), agrekola, SLOT(onLaser(bool)));

//    QWidget::connect(agrekola, SIGNAL(updateTermo(bool)), this, SLOT(updataTermo(bool)));
    //QWidget::connect(agrekola, SIGNAL(ValueCome(QVector<double>)), this, SLOT(getData()));
    //QObject::connect(&choiseDlg, SIGNAL(accepted()), &futureWatcher, SLOT(cancel()));
    //futureWatcher.setFuture(QtConcurrent::run(looper, agrekola));
    //futureWatcher.waitForFinished();
    //delete agrekola;
    //qDebug() << "Canceled?" << futureWatcher.future().isCanceled();
    return a.exec();
}
