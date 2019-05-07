#include "enddialog.h"
//#include "ui_enddialog.h"

using namespace myDialog;

EndDialog::EndDialog(const QString &str, QMap<double, double> y1, QMap<double, double> y2, QMap<double, double> y3, QMap<double, double> y4, QWidget *parent) :
    QDialog(parent)
    //ui(new Ui::EndDialog)
{
    //ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowModality(Qt::WindowModal);
    setWindowTitle("Результаты");
    QGridLayout *gridLayout = new QGridLayout(this);
    QLabel *label = new QLabel(this);
    pushButton_print = new QPushButton(this);
    pushButton_print->setText("Распечатать");
    connect(pushButton_print, &QPushButton::clicked, this, &EndDialog::on_pushButton_print_clicked);

    pushButton_next = new QPushButton(this);
    pushButton_next->setText("Продолжить");
    connect(pushButton_next, &QPushButton::clicked, this, &EndDialog::on_pushButton_next_clicked);

    plot1 = new QCustomPlot(this);
    plot2 = new QCustomPlot(this);
    plot3 = new QCustomPlot(this);
    plot4 = new QCustomPlot(this);

    gridLayout->addWidget(label, 0, 0, 1, 2, Qt::AlignCenter);
    gridLayout->addWidget(plot1, 1, 0, 1, 2);
    gridLayout->addWidget(plot2, 2, 0, 1, 2);
    gridLayout->addWidget(plot3, 3, 0, 1, 2);
    gridLayout->addWidget(plot4, 4, 0, 1, 2);

    gridLayout->addWidget(pushButton_print, 5, 0);
    gridLayout->addWidget(pushButton_next, 5, 1);


    this->setLayout(gridLayout);
    //plot1 = ui->frame_1;
    // set title of plot:
    plot1->plotLayout()->insertRow(0);
    plot1->plotLayout()->addElement(0, 0, new QCPTextElement(plot1, "Канал 1", QFont("sans", 10, QFont::Bold)));
    plot1->hide();
    //plot2 = ui->frame_2;
    plot2->plotLayout()->insertRow(0);
    plot2->plotLayout()->addElement(0, 0, new QCPTextElement(plot2, "Канал 2", QFont("sans", 10, QFont::Bold)));
    plot2->hide();
    //plot3 = ui->frame_3;
    plot3->plotLayout()->insertRow(0);
    plot3->plotLayout()->addElement(0, 0, new QCPTextElement(plot3, "Канал 3", QFont("sans", 10, QFont::Bold)));
    plot3->hide();
    //plot4 = ui->frame_4;
    plot4->plotLayout()->insertRow(0);
    plot4->plotLayout()->addElement(0, 0, new QCPTextElement(plot4, "Канал 4", QFont("sans", 10, QFont::Bold)));
    plot4->hide();
//    ui->frame_1->hide();
//    ui->frame_2->hide();
//    ui->frame_3->hide();
//    ui->frame_4->hide();

    printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printDialog = new QPrintDialog(printer, this);

    label->setText(str);

    graph(y1, plot1);
    graph(y2, plot2);
    graph(y3, plot3);
    graph(y4, plot4);
}

//EndDialog::EndDialog(const QString &str, QMap<double, double> y1, QMap<double, double> y2, QMap<double, double> y3, QMap<double, double> y4, QWidget *parent)
//{
//    EndDialog(str, parent);
//    graph(y1, plot1);
//    graph(y2, plot2);
//    graph(y3, plot3);
//    graph(y4, plot4);
//}

EndDialog::~EndDialog()
{
    //delete ui;
}

void EndDialog::graph(QMap<double, double> map, QCustomPlot *plot)
{
    //demoName = "Quadratic Demo";
    if(map.isEmpty()) {
        qDebug() << "Map is empty in EndDialog::graph()";
        return;
    }
    QVector<double> y = map.values().toVector();
    QVector<double> x = map.keys().toVector();
    double max_x = *std::max_element(x.begin(), x.end()); qDebug() << "max_x :" << max_x;
    double min_x = *std::min_element(x.begin(), x.end()); qDebug() << "min_x :" << min_x;
    double max_y = *std::max_element(y.begin(), y.end()); qDebug() << "max_y :" << max_y;
    double min_y = *std::min_element(y.begin(), y.end()); qDebug() << "min_y :" << min_y;
//    // generate some data:
//    QVector<double> x(101), y(101); // initialize with entries 0..100
//    for (int i=0; i<101; ++i)
//    {
//      x[i] = i/50.0 - 1; // x goes from -1 to 1
//      y[i] = x[i]*x[i];  // let's plot a quadratic function
//    }
    // create graph and assign data to it:
    plot->addGraph();
    plot->graph(0)->setData(x, y);
    // give the axes some labels:
    plot->xAxis->setLabel("x");
    plot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    plot->xAxis->setRange(min_x, max_x);
    if(max_y > 0)
        plot->yAxis->setRange(0, max_y + 0.2);
    else plot->yAxis->setRange(0, max_y - 0.2);
    plot->show();
}

void EndDialog::on_pushButton_print_clicked()
{
    if (printDialog->exec() == QDialog::Accepted) {
        // print ...
        QPainter painter;

        painter.begin(printer);
        double xscale = printer->pageRect().width()/double(width());
        double yscale = printer->pageRect().height()/double(height());
        double scale = qMin(xscale, yscale);
        painter.translate(printer->paperRect().x() + printer->pageRect().width()/2,
                     printer->paperRect().y() + printer->pageRect().height()/2);
        painter.scale(scale, scale);
        painter.translate(-width()/2, -height()/2);

//        painter.drawText(50, 50, 500, 1000, Qt::AlignLeft|Qt::AlignTop, ui->label->text());
//        painter.drawPixmap(50, 1000, 100, 100, plot1->toPixmap());
        pushButton_next->hide();
        pushButton_print->hide();
        this->render(&painter);
        pushButton_next->show();
        pushButton_print->show();
        //painter.end();
    }
}

void EndDialog::on_pushButton_next_clicked()
{
    close();
}
