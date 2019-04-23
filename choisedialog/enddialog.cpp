#include "enddialog.h"
#include "ui_enddialog.h"

using namespace myDialog;

EndDialog::EndDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EndDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowModality(Qt::WindowModal);
    plot1 = qobject_cast<QCustomPlot*>(ui->frame_1);
    plot2 = qobject_cast<QCustomPlot*>(ui->frame_2);
    plot3 = qobject_cast<QCustomPlot*>(ui->frame_3);
    plot4 = qobject_cast<QCustomPlot*>(ui->frame_4);
    ui->frame_1->hide();
    ui->frame_2->hide();
    ui->frame_3->hide();
    ui->frame_4->hide();

    printer = new QPrinter;
    printDialog = new QPrintDialog(printer, this);
}

EndDialog::~EndDialog()
{
    delete ui;
}

void EndDialog::setText(const QString &str)
{
    ui->label->setText(str);
}

void EndDialog::on_pushButton_print_clicked()
{
    if (printDialog->exec() == QDialog::Accepted) {
        // print ...
        QPainter painter;
        painter.begin(printer);
        painter.drawText(100, 100, 500, 500, Qt::AlignLeft|Qt::AlignTop, ui->label->text());
        painter.end();
    }
}

void EndDialog::on_pushButton_next_clicked()
{
    close();
}
