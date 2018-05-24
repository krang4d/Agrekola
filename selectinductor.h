#ifndef SELECTINDUCTOR_H
#define SELECTINDUCTOR_H

#include <QDialog>

namespace Ui {
class SelectInductor;
}

class SelectInductor : public QDialog
{
    Q_OBJECT

public:
    explicit SelectInductor(QWidget *parent = 0);
    ~SelectInductor();

private:
    Ui::SelectInductor *ui;
};

#endif // SELECTINDUCTOR_H
