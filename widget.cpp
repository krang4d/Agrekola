#include "widget.h"
#include "ui_widget.h"
#include <QScrollBar>
#include <QMessageBox>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include "useE154.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    data(false)
{
    ui->setupUi(this);
    setupFiles();
    setWindowTitle("Программы сбора данных с АЦП(E-154) по 4 каналам");
    customPlot1 = ui->frame_1;
    customPlot2 = ui->frame_2;
    customPlot3 = ui->frame_3;
    customPlot4 = ui->frame_4;
    ui->groupBox_Mix->setVisible(false);
    ui->progressBar->hide();

    setupRealtimeData();
    setupTimers();
    setAttribute(Qt::WA_DeleteOnClose);
    installEventFilter(this);
    startWin = new StartMeasurment;
    startWin->setModal(true);
    QWidget::connect(startWin, SIGNAL(startMeasurment()), this, SLOT(getData()));
}

Widget::~Widget()
{
    delete ui;
    delete customPlot1;
    delete customPlot2;
    delete customPlot3;
    delete customPlot4;
    file_data.close();
    file_setting.close();
    file_user.close();
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::Close)
    {
        qDebug() << tr("Close Event is emmited in the Widget!");
        //parentWidget()->show();
        emit stop();
        return true;
    }
    if(event->type() == QEvent::KeyPress)
    {
        qDebug() << "Event kayPress";
        QKeyEvent *kayEvent = static_cast<QKeyEvent *>(event);
        if(kayEvent->key() == Qt::Key_Enter)
        {
            bool b = ui->groupBox_Mix->isVisible();
            if(b)
            {
                ui->groupBox_Mix->setVisible(false);
                qDebug() << "setVisible(false)";
            }
            else
            {
                ui->groupBox_Mix->setVisible(true);
                qDebug() << "setVisible(true)";
            }
        }
        return true;
    }
    return QWidget::eventFilter(watched, event);
}

void Widget::setUserMessage(QString str, bool withtime, bool tofile)
{
    if(withtime)
    {
        QString msg = QString("%1,    Время %2")
                .arg(str)
                .arg(dt.toString("hh:mm:ss"));
        ui->textEdit->append(msg);
        if(tofile) out_user << msg << "\n";
    }
    else
    {
        ui->textEdit->append(str);
        if(tofile) out_user << str << "\n";
    }
    QScrollBar *b = ui->textEdit->verticalScrollBar();
    b->triggerAction(QScrollBar::SliderToMaximum);
}

void Widget::setTestMode(bool b)
{
    //setUserMessage(QString(agrekola->GetInformation()), false);
    emit get_information();
    ui->groupBox_Mix->setVisible(b);
}

void Widget::setupQuadraticPlot(QVector<double> data)
{
    if (data.isEmpty())
    {
        QMessageBox::warning(this, tr("My Application"),
                             tr("Нет данных для вывода графика.\n"));
    }
    customPlot1->addGraph();
    QVector<double> x;
    double average;
    for(int i = 0; i < data.count(); i++)
    {
        x.append(double(i));
        average += data[i];
    }
    average /= data.length();
    //ui->label_average->setText(QString("%1").arg(average));
    customPlot1->graph(0)->setData(x, data);
    // give the axes some labels:
    customPlot1->xAxis->setLabel("x");
    customPlot1->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot1->xAxis->setRange(0, data.length());
    customPlot1->yAxis->setRange(-5, 5);
    customPlot1->replot();
}

void Widget::setupRealtimeData(bool duo)
{
    // include this section to fully disable antialiasing for higher performance:
    /*
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);

    customPlot1->setNotAntialiasedElements(QCP::aeAll);
    customPlot1->xAxis->setTickLabelFont(font);
    customPlot1->yAxis->setTickLabelFont(font);
    customPlot1->legend->setFont(font);

    customPlot2->setNotAntialiasedElements(QCP::aeAll);
    customPlot2->xAxis->setTickLabelFont(font);
    customPlot2->yAxis->setTickLabelFont(font);
    customPlot2->legend->setFont(font);

    customPlot3->setNotAntialiasedElements(QCP::aeAll);
    customPlot3->xAxis->setTickLabelFont(font);
    customPlot3->yAxis->setTickLabelFont(font);
    customPlot3->legend->setFont(font);

    customPlot4->setNotAntialiasedElements(QCP::aeAll);
    customPlot4->xAxis->setTickLabelFont(font);
    customPlot4->yAxis->setTickLabelFont(font);
    customPlot4->legend->setFont(font);
    */
    //customPlot1->setOpenGl(true);
    //customPlot2->setOpenGl(true);
    //customPlot3->setOpenGl(true);
    //customPlot4->setOpenGl(true);
    if(!duo)
    {
        QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
        timeTicker->setTimeFormat("%m:%s");

        customPlot1->addGraph();
        customPlot1->graph(0)->setPen(QPen(QColor(10, 110, 40)));
        customPlot1->xAxis->setTicker(timeTicker);
        customPlot1->axisRect()->setupFullAxesBox();
        customPlot1->xAxis->setLabel("Время, с");
        customPlot1->yAxis->setLabel("Напряжение, В");
        customPlot1->yAxis->setRange(-5.5, 5.5);

        // make left and bottom axes transfer their ranges to right and top axes:
        connect(customPlot1->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot1->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->yAxis2, SLOT(setRange(QCPRange)));

        customPlot2->addGraph();
        customPlot2->graph(0)->setPen(QPen(QColor(255, 110, 40)));
        customPlot2->xAxis->setTicker(timeTicker);
        customPlot2->axisRect()->setupFullAxesBox();
        customPlot2->xAxis->setLabel("Время, с");
        customPlot2->yAxis->setLabel("Напряжение, В");
        customPlot2->yAxis->setRange(-5.5, 5.5);

        connect(customPlot2->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot2->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->yAxis2, SLOT(setRange(QCPRange)));

        customPlot3->addGraph();
        customPlot3->graph(0)->setPen(QPen(QColor(255, 110, 200)));
        customPlot3->xAxis->setTicker(timeTicker);
        customPlot3->axisRect()->setupFullAxesBox();
        customPlot3->xAxis->setLabel("Время, с");
        customPlot3->yAxis->setLabel("Напряжение, В");
        customPlot3->yAxis->setRange(-5.5, 5.5);

        connect(customPlot3->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot3->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot3->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot3->yAxis2, SLOT(setRange(QCPRange)));

        customPlot4->addGraph();
        customPlot4->graph(0)->setPen(QPen(QColor(255, 200, 40)));
        customPlot4->xAxis->setTicker(timeTicker);
        customPlot4->axisRect()->setupFullAxesBox();
        customPlot4->xAxis->setLabel("Время, с");
        customPlot4->yAxis->setLabel("Напряжение, В");
        customPlot4->yAxis->setRange(-5.5, 5.5);

        connect(customPlot4->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot4->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot4->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot4->yAxis2, SLOT(setRange(QCPRange)));

//        // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
//        disconnect(&plotTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlotDuo()));
//        plotTimer.stop();
//        connect(&plotTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlotSingle()));
//        plotTimer.start(0); // Interval 0 means to refresh as fast as possible
    }
    else
    {
        QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
        timeTicker->setTimeFormat("%m:%s");

        customPlot1->addGraph();
        customPlot1->graph(0)->setPen(QPen(QColor(10, 110, 40)));
        customPlot1->graph(1)->setPen(QPen(QColor(255, 110, 40)));
        customPlot1->xAxis->setTicker(timeTicker);
        customPlot1->axisRect()->setupFullAxesBox();
        customPlot1->xAxis->setLabel("Время, с");
        customPlot1->yAxis->setLabel("Напряжение, В");
        customPlot1->yAxis->setRange(-5.5, 5.5);

        // make left and bottom axes transfer their ranges to right and top axes:
        connect(customPlot1->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot1->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot1->yAxis2, SLOT(setRange(QCPRange)));

        customPlot2->addGraph();
        customPlot2->graph(0)->setPen(QPen(QColor(255, 110, 200)));
        customPlot2->graph(1)->setPen(QPen(QColor(255, 200, 40)));
        customPlot2->xAxis->setTicker(timeTicker);
        customPlot2->axisRect()->setupFullAxesBox();
        customPlot2->xAxis->setLabel("Время, с");
        customPlot2->yAxis->setLabel("Напряжение, В");
        customPlot2->yAxis->setRange(-5.5, 5.5);

        connect(customPlot2->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->xAxis2, SLOT(setRange(QCPRange)));
        connect(customPlot2->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot2->yAxis2, SLOT(setRange(QCPRange)));

//        // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
//        disconnect(&plotTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlotSingle()));
//        plotTimer.stop();
//        connect(&plotTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlotDuo()));
//        plotTimer.start(0); // Interval 0 means to refresh as fast as possible
    }
}

void Widget::setupFiles()
{
    QDir dir;
    QString path = QDir::homePath();
    dir.cd(path); //переходим в папку home
    if(!dir.cd("Agrekola4k"))
    {
        if(dir.mkdir("Agrekola4k")) dir.cd("Agrekola4k");
        QDir::setCurrent(dir.path());
        qDebug() << "mkdir(Agrekola4k)";
    }
    else QDir::setCurrent(dir.path());
    //открываем файл сообщений
    file_user.setFileName("user.txt");
    if(!file_user.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) qWarning() << "user file is't opened";
    out_user.setDevice(&file_user);

    if(!dir.cd("settings"))
    {
        if(dir.mkdir("settings")) dir.cd("settings");
        QDir::setCurrent(dir.path());
        qDebug() << "mkdir(settings)";
    }
    else QDir::setCurrent(dir.path());
    //открываем файл настроек
    file_setting.setFileName("setting.txt");
    if(!file_setting.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) qWarning() << "setting file is't opened";
    out_settings.setDevice(&file_setting);

    if(!dir.cd("../data"))
    {
        if(dir.mkdir("../data")) dir.cd("../data");
        QDir::setCurrent(dir.path());
        qDebug() << "mkdir(data)";
    }
    else QDir::setCurrent(dir.path());
}

void Widget::realtimeDataSlotSingle(QVector<double> &a)
{
    qDebug() << "a0 = " << a[0];
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.010) // at most add point every 10 ms
    {
//      add data to lines:
      //QVector<double> a = agrekola->AdcKADR();
      customPlot1->graph(0)->addData(key, a[0]); //qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
      customPlot2->graph(0)->addData(key, a[1]); //qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
      customPlot3->graph(0)->addData(key, a[2]); //qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
      customPlot4->graph(0)->addData(key, a[3]); //qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
      //rescale value (vertical) axis to fit the current data:
      //ui->customPlot->graph(0)->rescaleValueAxis();
      //ui->customPlot->graph(1)->rescaleValueAxis(true);
      if(data)
      {
          y1.push_back(a[0]);
          y2.push_back(a[1]);
          y3.push_back(a[2]);
          y4.push_back(a[3]);
          x.push_back(key);
      }
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    customPlot1->xAxis->setRange(key, 8, Qt::AlignRight);
    customPlot1->replot();

    customPlot2->xAxis->setRange(key, 8, Qt::AlignRight);
    customPlot2->replot();

    customPlot3->xAxis->setRange(key, 8, Qt::AlignRight);
    customPlot3->replot();

    customPlot4->xAxis->setRange(key, 8, Qt::AlignRight);
    customPlot4->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
        ui->label_fps->setText(QString("%1 FPS, Total Data points: %2")
                        .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                        .arg(customPlot1->graph(0)->data()->size()+customPlot2->graph(0)->data()->size() + customPlot3->graph(0)->data()->size() + customPlot4->graph(0)->data()->size()));
        lastFpsKey = key;
        frameCount = 0;
    }
}

void Widget::realtimeDataSlotDuo(QVector<double> &a)
{
    qDebug() << "a0 = " << a[0];
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.010) // at most add point every 10 ms
    {
      // add data to lines:
//      double a1 = agrekola->AdcSample(useE154::CH1);
//      double a2 = agrekola->AdcSample(useE154::CH2);
//      double a3 = agrekola->AdcSample(useE154::CH3);
//      double a4 = agrekola->AdcSample(useE154::CH4);

      customPlot1->graph(0)->addData(key, a[0]); //qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
      customPlot1->graph(1)->addData(key, a[1]); //qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
      customPlot2->graph(0)->addData(key, a[2]); //qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
      customPlot2->graph(1)->addData(key, a[3]); //qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
      //rescale value (vertical) axis to fit the current data:
      //ui->customPlot->graph(0)->rescaleValueAxis();
      //ui->customPlot->graph(1)->rescaleValueAxis(true);
      if(data)
      {
          //(startWin->getTime()/(kay - st));
          //a1 = (a1+a2)/2;
          //a3 = (a3+a4)/2;
          y1.push_back(a[0]);
          y2.push_back(a[1]);
          y3.push_back(a[2]);
          y4.push_back(a[3]);
          x.push_back(key);
      }
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    customPlot1->xAxis->setRange(key, 8, Qt::AlignRight);
    customPlot1->replot();

    customPlot2->xAxis->setRange(key, 8, Qt::AlignRight);
    customPlot2->replot();

    customPlot3->xAxis->setRange(key, 8, Qt::AlignRight);
    customPlot3->replot();

    customPlot4->xAxis->setRange(key, 8, Qt::AlignRight);
    customPlot4->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
        ui->label_fps->setText(QString("%1 FPS, Total Data points: %2")
                        .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                        .arg(customPlot1->graph(0)->data()->size()+customPlot2->graph(0)->data()->size() + customPlot3->graph(0)->data()->size() + customPlot4->graph(0)->data()->size()));
        lastFpsKey = key;
        frameCount = 0;
    }
}

void Widget::on_checkBox_1_stateChanged(int arg1)
{
    if(arg1) setUserMessage("Канал 1: включение перемешивания");
    else setUserMessage("Канала 1: выключение перемешивания");
    emit onMixCh1(arg1);
}

void Widget::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1) setUserMessage("Канал 2: включение перемешивания");
    else setUserMessage("Канала 2: выключение перемешивания");
    emit onMixCh2(arg1);
}

void Widget::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1) setUserMessage("Канал 3: включение перемешивания");
    else setUserMessage("Канала 3: выключение перемешивания");
    emit onMixCh3(arg1);
}

void Widget::on_checkBox_4_stateChanged(int arg1)
{
    if(arg1) setUserMessage("Канал 4: включение перемешивания");
    else setUserMessage("Канала 4: выключение перемешивания");
    emit onMixCh4(arg1);
}

void Widget::on_checkBox_PP_stateChanged(int arg1)
{
    if(arg1) setUserMessage("Канал РР: включение перемешивания");
    else setUserMessage("Канала РР: выключение перемешивания");
    emit onMixPP(arg1);
}

void Widget::on_checkBox_L_stateChanged(int arg1)
{
    if(arg1) setUserMessage("Включение лазеров");
    else setUserMessage("Выключение лазеров");
    emit onLaser(arg1);
}

void Widget::on_pushButton_clicked()
{
    startWin->show();
}

void Widget::updataTermo(bool td)
{

    if(!td)
    {
        ui->label_TD->setText(QString("Температура >37°C"));
        ui->label_TD->setStyleSheet("color: green");
    }
    else
    {
        ui->label_TD->setText(QString("Температура <37°C"));
        ui->label_TD->setStyleSheet("color: red");
    }
}

void Widget::updateTime()
{
    //обновление времени на часах
    dt = QDateTime::currentDateTime();
    ui->label_time->setText("Время: " + dt.toString("hh:mm:ss"));
    ui->label_date->setText("Дата: " + dt.toString("dd.MM.yyyy"));
}

void Widget::progressValueChanged()
{
    ui->progressBar->setMaximum(t-progressTimer.interval());
    ui->progressBar->setValue(ui->progressBar->value()+progressTimer.interval());
}

void Widget::getData()
{
    if(!startWin->isCancel())
    {
        if(startWin->isSingle())
        {
            if(startWin->isChannel_1()) ui->groupBox_f1->show();
            else ui->groupBox_f1->hide();
            if(startWin->isChannel_2()) ui->groupBox_f2->show();
            else ui->groupBox_f2->hide();
            if(startWin->isChannel_3()) ui->groupBox_f3->show();
            else ui->groupBox_f3->hide();
            if(startWin->isChannel_4()) ui->groupBox_f4->show();
            else ui->groupBox_f4->hide();
            setupRealtimeData(false);
        }
        else
        {
            ui->groupBox_f3->hide();
            ui->groupBox_f4->hide();
            ui->groupBox_f1->setTitle("Канал 1, 2");
            ui->groupBox_f2->setTitle("Канал 3, 4");
            setupRealtimeData(true);
        }
        QString ch;

        if (startWin->isChannel_1()) {ch += QString("№1 = %1, ").arg(startWin->getNum_1());}
        else ch += QString("№1 - выкл., ");

        if (startWin->isChannel_2()) {ch += QString("№2 = %1, ").arg(startWin->getNum_2());}
        else ch += QString("№2 - выкл., ");

        if (startWin->isChannel_3()) {ch += QString("№3 = %1, ").arg(startWin->getNum_3());}
        else ch += QString("№3 - выкл., ");

        if (startWin->isChannel_4()) {ch += QString("№4 = %1 ").arg(startWin->getNum_4());}
        else ch += QString("№4 - выкл. ");

        QString stat = QString("Начало измерения (t = %1c, %2)")
                               .arg(startWin->getTime()).arg(ch);

        setUserMessage(stat, true, true);
        t = startWin->getTime() * 1000;
        ui->progressBar->setVisible(true);
        ui->progressBar->setValue(0);
        data = true;
        emit status(QString("Измерение"));
        QTimer::singleShot(t, this, SLOT(writeData()));
        progressTimer.start(300);
    }
}

void Widget::setupTimers()
{
    //настройка таймера для часов
    currenttime = new QTimer(this);
    connect(currenttime, SIGNAL(timeout()), SLOT(updateTime()));
    currenttime->start(1000);
    dt = QDateTime::currentDateTime();
    setUserMessage(QString("Начало работы программы    Дата %1").arg(dt.toString("dd.MM.yyyy")));

    //настройка таймера для обновления датчика температуры
    //TDTimer.start(500);
    //connect(&TDTimer, SIGNAL(timeout()), this, SLOT(updataTermo()));

    //таймер для отображения процесса сбора данных
    connect(&progressTimer, SIGNAL(timeout()), this, SLOT(progressValueChanged()));
}

void Widget::writeData()
{
    progressTimer.stop();
    data = false;
    qDebug() << "call writeData()";
    //создаем файл данных
    //имя файла формируется из текущей даты + число запуска программы в этот день
    QDateTime d = QDateTime::currentDateTime();
    static int i(0);
    for(;;)
    {
        QString name = QString("%1_%2.txt").arg(d.toString("yyyyddMM")).arg(i);
        if(!QFile::exists(name)){
            file_data.setFileName(name);
            if(!file_data.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) qWarning() << "data file is't opened";
            out_data.setDevice(&file_data);
            break;
        }
        i++;
    }
    emit status(QString("Запись данных"));
    qDebug() << "Запись данных";
    out_data << QString("%1\t%2\t\t%3\t\t%4\t\t%5\t\t%6\n")
                .arg("№").arg("V1").arg("V2").arg("V3").arg("V4").arg("t");
    for(int i=0; i<x.length(); i++)
    {
        ui->progressBar->setMaximum(x.length());
        ui->progressBar->setValue(i);//i*100/x.length());
        out_data << QString("%1\t%2\t%3\t%4\t%5\t%6\n")
                       .arg(i).arg(y1[i]).arg(y2[i]).arg(y3[i]).arg(y4[i])
                       .arg(x[i]);
    }
    out_data.flush();
    y1.clear();
    y2.clear();
    y3.clear();
    y4.clear();
    x.clear();
    ui->progressBar->setVisible(false);
    setUserMessage(QString("Данные записаны в файл %1/%2").arg(QDir::currentPath()).arg(file_data.fileName()), true, true);
}
