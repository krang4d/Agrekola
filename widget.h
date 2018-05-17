#ifndef WIDGET_H
#define WIDGET_H
#include <QString>
#include <QWidget>
#include "useE154.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void setText(QString str);
    void setAgrekila(UseE154 *agr);
    ~Widget();

private slots:
    void on_btnMes_clicked();
    void on_btnTest_clicked();

private:
    Ui::Widget *ui;
    QString text;
    UseE154 *Agrecola;
};

#endif // WIDGET_H
