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

private slots:
    void on_radioButton_other_toggled(bool checked);
    void on_pushButton_ok_clicked();

signals:
    void inductor_selected();

private:
    Ui::SelectInductor *ui;
};

#endif // SELECTINDUCTOR_H
