#include <QApplication>
#include <QString>
#include <QtConcurrent>
#include <QThread>
#include <QDebug>
#include <QVector>

#include "choisedialog.h"
#include "useE154.h"
#include "widget.h"

void looper(useE154 *a)
{
    a->funThread();
//    QThread::currentThread()->msleep(100);
//    QVariantList vec_data;
//    qDebug() << "looper thread ID" <<QThread::currentThreadId();
//    qDebug() << a->GetInformation();
//    for(int i=0; i<10; i++)
//    {
//        vec_data = a->AdcKADR();
//        qDebug() << i << " " << vec_data[0] << " " << vec_data[1] << " " << vec_data[2] << " " << vec_data[3];
//        QThread::currentThread()->msleep(100);
//    }
}

void show(Widget *w)
{
    w->show();
}

void thread_finish()
{
    qDebug() << "thread_finish()";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "main thread ID: " << QThread::currentThreadId();
    useE154 *agrekola = new useE154;
    Widget *widget =new Widget;
    //ChoiseDialog choiseDlg;

    QFutureWatcher<void> futureWatcher1;

    QWidget::connect(widget, SIGNAL(onMixCh1(bool)), agrekola, SLOT(onMixCh1(bool)));
    QWidget::connect(widget, SIGNAL(onMixCh2(bool)), agrekola, SLOT(onMixCh2(bool)));
    QWidget::connect(widget, SIGNAL(onMixCh3(bool)), agrekola, SLOT(onMixCh3(bool)));
    QWidget::connect(widget, SIGNAL(onMixCh4(bool)), agrekola, SLOT(onMixCh4(bool)));
    QWidget::connect(widget, SIGNAL(onMixPP(bool)), agrekola, SLOT(onMixPP(bool)));
    QWidget::connect(widget, SIGNAL(onLaser(bool)), agrekola, SLOT(onLaser(bool)));
    QObject::connect(widget, SIGNAL(stop()), agrekola, SLOT( stopThread()));

    QWidget::connect(agrekola, SIGNAL(update_termo(bool)), widget, SLOT(updataTermo(bool)));
    //QWidget::connect(agrekola, SIGNAL(value_come(QVector<double>&)), widget, SLOT());
    QWidget::connect(agrekola, SIGNAL(value_come(QVariantList)), widget, SLOT(realtimeDataSlotSingle(QVariantList)));

    futureWatcher1.setFuture(QtConcurrent::run(looper, agrekola));
    widget->show();
    a.exec();
    futureWatcher1.waitForFinished();

    //delete agrekola;
    //qDebug() << "Canceled?" << futureWatcher.future().isCanceled();
}
