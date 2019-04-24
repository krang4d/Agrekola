#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include "itools.h"

namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(ITools *, QDialog *parent = 0);
    ~Options();

private slots:
    void on_pushButton_Next_clicked();

private:
    Ui::Options *ui;
    ITools *widget;
};

#endif // OPTIONS_H
