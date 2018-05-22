#ifndef CHOISEDIALOG_H
#define CHOISEDIALOG_H

#include <QDialog>
#include "agr1.h"

namespace Ui {
class ChoiseDialog;
}

class ChoiseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChoiseDialog(QWidget *parent = 0);
    ~ChoiseDialog();

private slots:
    void on_agr1Button_clicked();

private:
    Ui::ChoiseDialog *ui;
    Agr1 *agr1;
};

#endif // CHOISEDIALOG_H
