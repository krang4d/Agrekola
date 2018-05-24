#ifndef CHOISEDIALOG_H
#define CHOISEDIALOG_H

#include <QDialog>
//#include "agr1.h"
//#include "agr2.h"
//#include "ko1.h"
//#include "ko2.h"
//#include "ko3.h"
//#include "ko4.h"

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

    virtual void accept() override;

    void on_agr1Button_clicked();

    void on_agr2Button_clicked();

    void on_ko1Button_clicked();

    void on_ko2Button_clicked();

    void on_ko3Button_clicked();

    void on_ko4Button_clicked();

    void on_ko5Button_clicked();

    void on_testButton_clicked();

private:
    Ui::ChoiseDialog *ui;
};

#endif // CHOISEDIALOG_H
