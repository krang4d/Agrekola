#include "printer.h"

Printer::Printer(QWidget *parent) : QPrintDialog(parent)
{
    painter =  new QPainter;
    printer = new QPrinter;
    painter->begin(printer);
}

Printer::~Printer()
{

}

void Printer::print(QString text)
{
    painter->drawText(100, 100, 500, 500, Qt::AlignLeft|Qt::AlignTop, text);

}

int Printer::exec()
{

}
