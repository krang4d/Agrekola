#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QKeyEvent>

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
}

MainWindow::~MainWindow()
{
    delete ui;
    delete centerWidget;
}

void MainWindow::newShow()
{
    int i = ch->getTypeOfWidget();
    //else  {QMessageBox test(QMessageBox::Warning, "qobject_cast", QString("qobject_cast"), QMessageBox::Ok); test.exec();}
    QString str;
    if(i == 1){
        str = tr("Определение параметров агрегации, измерение (1)");
        setWindowTitle(str);
        centerWidget->setUserMessage(str);
    }
    else if(i == 2){
        str = tr("Определение активности фактора Виллебранда, измерение (2)");
        setWindowTitle(str);
        centerWidget->setUserMessage(str);
    }
    else if(i == 3){
        str = tr("Время свертывания, измерение (3)");
        setWindowTitle(str);
        centerWidget->setUserMessage(str);
    }
    else if(i == 4){
        str = tr("АЧТВ, измерение (4)");
        setWindowTitle(str);
        centerWidget->setUserMessage(str);
    }
    else if(i == 5){
        str = tr("Фибриноген, измерение (5)");
        setWindowTitle(str);
        centerWidget->setUserMessage(tr("Установите в каналы кюветы с пробами и мешалками, укажите используемые каналы, выберите парные или одиночные пробы и введите номера проб. Для парных выберайте каналы 1 и 2, либо 3 и 4, номера проб в них должны быть одинаковыми. Измените, если нужно время инкубации затем нажмите кнопку Старт."));
    }
    else if(i == 6){
        str = tr("Тромбин, измерние (6)");
        setWindowTitle(str);
        centerWidget->setUserMessage(str);
    }
    else if(i == 7){
        str = tr("Протромбиновый комплекс, измерение (7)");
        setWindowTitle(str);
        centerWidget->setUserMessage(str);
    }
    //ui->label_type->setText(QString(std::to_string(i).c_str()));
    show();
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
        ch->show();
        return true;
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::on_action_start_triggered()
{
    centerWidget->getData();
}

void MainWindow::on_action_menu_triggered()
{
    ch->show();
    close();
    //this->~MainWindow();
}
