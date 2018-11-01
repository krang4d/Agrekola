#ifndef CALIBPARAM_H
#define CALIBPARAM_H

#include <QDialog>
#include <QString>

namespace Ui {
class CalibParam;
}

class CalibParam : public QDialog
{
    Q_OBJECT

public:
    explicit CalibParam(QWidget *parent = 0);
    ~CalibParam();

    void setText(QString);

private:
    Ui::CalibParam *ui;
};

#endif // CALIBPARAM_H
