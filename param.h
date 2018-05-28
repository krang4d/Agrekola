#ifndef PARAM_H
#define PARAM_H

#include <QWidget>

namespace Ui {
class Param;
}

class Param : public QWidget
{
    Q_OBJECT

public:
    explicit Param(QWidget *parent = 0);
    ~Param();

private:
    Ui::Param *ui;
};

#endif // PARAM_H
