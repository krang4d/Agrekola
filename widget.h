﻿#ifndef WIDGET_H
#define WIDGET_H
#include <QString>
#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void setText(QString str);
    ~Widget();

private:
    Ui::Widget *ui;
    QString text;
};

#endif // WIDGET_H
