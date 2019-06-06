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
    setGeometry(parent->geometry());
    QGridLayout *gridLayout = new QGridLayout(this);
    QLabel *label = new QLabel(this);
    pushButton_print = new QPushButton(this);
    pushButton_print->setText("Распечатать");
    connect(pushButton_print, &QPushButton::clicked, this, &EndDialog::on_pushButton_print_clicked);

    pushButton_next = new QPushButton(this);
    pushButton_next->setText("Продолжить");
    connect(pushButton_next, &QPushButton::clicked, this, &EndDialog::on_pushButton_next_clicked);

    gridLayout->addWidget(label, 0, 0, 1, 2, Qt::AlignCenter);

    if(!y1.isEmpty()) {
        QCustomPlot *plot = new QCustomPlot(this);
        plot->plotLayout()->insertRow(0);
        plot->plotLayout()->addElement(0, 0, new QCPTextElement(plot, "Канал 1", QFont("sans", 10, QFont::Bold)));
        graph(y1, plot);
        plots.append(plot);
    }

    if(!y2.isEmpty()) {
        QCustomPlot *plot = new QCustomPlot(this);
        plot->plotLayout()->insertRow(0);
        plot->plotLayout()->addElement(0, 0, new QCPTextElement(plot, "Канал 2", QFont("sans", 10, QFont::Bold)));
        graph(y2, plot);
        plots.append(plot);
    }

    if(!y3.isEmpty()) {
        QCustomPlot *plot = new QCustomPlot(this);
        plot->plotLayout()->insertRow(0);
        plot->plotLayout()->addElement(0, 0, new QCPTextElement(plot, "Канал 3", QFont("sans", 10, QFont::Bold)));
        graph(y3, plot);
        plots.append(plot);
    }

    if(!y4.isEmpty()) {
        QCustomPlot *plot = new QCustomPlot(this);
        plot->plotLayout()->insertRow(0);
        plot->plotLayout()->addElement(0, 0, new QCPTextElement(plot, "Канал 4", QFont("sans", 10, QFont::Bold)));
        graph(y4, plot);
        plots.append(plot);
    }

    printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printDialog = new QPrintDialog(printer, this);

    label->setText(str);

    int i = 0;
    if(plots.length() > 1) {
        for(auto it = plots.begin(); it!= plots.end(); it++ ) {
            if(i == 0) gridLayout->addWidget(plots.at(i), 1, 0);
            if(i == 1) gridLayout->addWidget(plots.at(i), 1, 1);
            if(i == 2) gridLayout->addWidget(plots.at(i), 2, 0);
            if(i == 3) gridLayout->addWidget(plots.at(i), 2, 1);
            i++;
        }
    } else gridLayout->addWidget(plots.at(i), 1, 0, 1, 2);
    gridLayout->addWidget(pushButton_print, 3, 0);
    gridLayout->addWidget(pushButton_next, 3, 1);
    this->setLayout(gridLayout);
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
    double delta = x.first();
    for( auto &it : x ) {
        it -= delta;
    }

    double max_x = *std::max_element(x.begin(), x.end()); qDebug() << "max_x :" << max_x;
    double min_x = *std::min_element(x.begin(), x.end()); qDebug() << "min_x :" << min_x;
    double max_y = *std::max_element(y.begin(), y.end()); qDebug() << "max_y :" << max_y;
    double min_y = *std::min_element(y.begin(), y.end()); qDebug() << "min_y :" << min_y;
    // create graph and assign data to it:
    plot->addGraph();
    plot->graph(0)->setData(x, y);
    // give the axes some labels:
    plot->xAxis->setLabel("Время, с");
    plot->yAxis->setLabel("Вольт");
    // set axes ranges, so we see all data:
    plot->xAxis->setRange(min_x, max_x+0.1);
    plot->yAxis->setRange(min_y - 0.1, max_y + 0.1);
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
