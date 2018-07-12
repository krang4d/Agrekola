#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QKeyEvent>
#include "useE154.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    centerWidget = new Widget;
    setCentralWidget(centerWidget);
    ch = qobject_cast<ChoiseDialog *>(parentWidget());
    if (!ch){
        QMessageBox test(QMessageBox::Critical, "qobject_cast", QString("qobject_cast in MainWindow::newShow()"), QMessageBox::Ok); test.exec();
    }
    installEventFilter(this);
    connect(centerWidget, SIGNAL(status(QString)), this->statusBar(), SLOT(showMessage(QString)));
    setupThread();
}

MainWindow::~MainWindow()
{
    delete ui;
    centerWidget->stop();
    //delete centerWidget;
}

void MainWindow::newShow()
{
    show();
    int i = ch->getTypeOfWidget();
    //else  {QMessageBox test(QMessageBox::Warning, "qobject_cast", QString("qobject_cast"), QMessageBox::Ok); test.exec();}
    QString str;
    switch (i){
    case 1:{
        str = tr("Определение параметров агрегации, измерение (1)");
        setWindowTitle(str);
        centerWidget->setUserMessage(str);

    }break;
    case 2:{
        str = tr("Определение активности фактора Виллебранда, измерение (2)");
        setWindowTitle(str);
        centerWidget->setUserMessage(str);
    }break;
    case 3:{
        str = tr("Время свертывания, измерение (3)");
        setWindowTitle(str);
        centerWidget->setUserMessage(str);
    }break;
    case 4:{
        str = tr("АЧТВ, измерение (4)");
        setWindowTitle(str);
        centerWidget->setUserMessage(str);
    }break;
    case 5:{
        str = tr("Фибриноген, измерение (5)");
        setWindowTitle(str);
        centerWidget->setUserMessage(tr("Установите в каналы кюветы с пробами и мешалками, укажите используемые каналы, выберите парные или одиночные пробы и введите номера проб. Для парных выберайте каналы 1 и 2, либо 3 и 4, номера проб в них должны быть одинаковыми. Измените, если нужно время инкубации затем нажмите кнопку Старт."));
    }
    case 6:{
        str = tr("Тромбин, измерние (6)");
        setWindowTitle(str);
        centerWidget->setUserMessage(str);
    }break;
    case 7:{
        str = tr("Протромбиновый комплекс, измерение (7)");
        setWindowTitle(str);
        centerWidget->setUserMessage(str);
    }break;
    default:
        break;
    }
}

void MainWindow::setupThread()
{
    qDebug() << "main thread ID: " << QThread::currentThreadId();
    useE154 *agrekola = new useE154;
    //ChoiseDialog choiseDlg;
    QWidget::connect(centerWidget, SIGNAL(onmixch1(bool)), agrekola, SLOT(onMixCh1(bool)));
    QWidget::connect(centerWidget, SIGNAL(onmixch2(bool)), agrekola, SLOT(onMixCh2(bool)));
    QWidget::connect(centerWidget, SIGNAL(onmixch3(bool)), agrekola, SLOT(onMixCh3(bool)));
    QWidget::connect(centerWidget, SIGNAL(onmixch4(bool)), agrekola, SLOT(onMixCh4(bool)));
    QWidget::connect(centerWidget, SIGNAL(onmixpp(bool)), agrekola, SLOT(onMixPP(bool)));
    QWidget::connect(centerWidget, SIGNAL(onlaser(bool)), agrekola, SLOT(onLaser(bool)));
    QObject::connect(centerWidget, SIGNAL(stop()), agrekola, SLOT(stopThread()));
    QObject::connect(centerWidget, SIGNAL(stop()), centerWidget, SLOT(deleteLater()));

    QWidget::connect(agrekola, SIGNAL(update_termo(bool)), centerWidget, SLOT(updataTermo(bool)));
    QWidget::connect(agrekola, SIGNAL(value_come(QVariantList)), centerWidget, SLOT(realtimeDataSlot(QVariantList)));
    QWidget::connect(agrekola, SIGNAL(finished()), agrekola, SLOT(deleteLater()));
    agrekola->start();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *kayEvent = static_cast<QKeyEvent *>(event);
        if(kayEvent->key() == Qt::Key_Space)
        {
            QMessageBox::about(this, "Event is emmited", "Key_Space is pressed!");
            return true;
        }
    }
    if(event->type() == QEvent::Close)
    {
        centerWidget->stop();
        ch->show();
        return QMainWindow::eventFilter(watched, event);
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::on_action_start_triggered()
{
    centerWidget->getData();
}

void MainWindow::on_menu_triggered()
{
    ch->show();
    close();
}
