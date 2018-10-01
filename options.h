#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>
#include <widget.h>

namespace Ui {
class Options;
}

class Widget;

class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = 0);
    void setWidget(Widget *);
    ~Options();

private slots:
    void on_pushButton_Next_clicked();

private:
    Ui::Options *ui;
    Widget *widget;

};

#endif // OPTIONS_H
