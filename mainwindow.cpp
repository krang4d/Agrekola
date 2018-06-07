#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m = new Measurement;
    st = new StartMeasurment;
    setCentralWidget(m);
    connect(st, SIGNAL(startMeasurment()), m, SLOT(getData()));
}

MainWindow::~MainWindow()
{
    delete m;
    delete st;
    delete ui;
}

void MainWindow::newShow()
{
    int i;
    if (ChoiseDialog *ch = qobject_cast<ChoiseDialog *>(parentWidget()))
        i = ch->getTypeOfWidget();
    else{
        QMessageBox test(QMessageBox::Critical, "qobject_cast", QString("qobject_cast in MainWindow::newShow()"), QMessageBox::Ok); test.exec();
    }
    //else  {QMessageBox test(QMessageBox::Warning, "qobject_cast", QString("qobject_cast"), QMessageBox::Ok); test.exec();}

    if(i == 1){
        setWindowTitle(tr("Определение параметров агрегации, измерение (1)"));
    }
    else if(i == 2){
        setWindowTitle(tr("Определение активности фактора Виллебранда, измерение (2)"));
    }
    else if(i == 3){
        setWindowTitle(tr("Время свертывания, измерение (3)"));
    }
    else if(i == 4){
        setWindowTitle(tr("АЧТВ, измерение (4)"));
    }
    else if(i == 5){
        setWindowTitle(tr("Фибриноген, измерение (5)"));
        m->setUserMessage(tr("Установите в каналы кюветы с пробами и мешалками, укажите используемые каналы, выберите парные или одиночные пробы и введите номера проб. Для парных выберайте каналы 1 и 2, либо 3 и 4, номера проб в них должны быть одинаковыми. Измените, если нужно время инкубации затем нажмите кнопку Старт."));
    }
    else if(i == 6){
        setWindowTitle(tr("Тромбин, измерние (6)"));
    }
    else if(i == 7){
        setWindowTitle(tr("Протромбиновый комплекс, измерение (7)"));
    }
    //ui->label_type->setText(QString(std::to_string(i).c_str()));
    show();
}

void MainWindow::on_action_start_triggered()
{
    //StartMeasurment *st = new StartMeasurment;
    //st->setWindowModality(Qt::ApplicationModal);
    st->show();
}

void MainWindow::on_action_menu_triggered()
{
    hide();
}
