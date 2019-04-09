#ifndef PRINTER_H
#define PRINTER_H

#include <QWidget>
#include <QPrintDialog>
#include <QPrinter>
#include <QPainter>

class Printer : public QPrintDialog
{
    Q_OBJECT
public:
    explicit Printer(QWidget *parent = 0);
    ~Printer();
    void print(QString);

private:
    QPrinter *printer;
    QPainter *painter;

    // QDialog interface
public slots:
    int exec() override;
};

#endif // PRINTER_H
