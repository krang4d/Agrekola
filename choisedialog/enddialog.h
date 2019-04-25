#ifndef ENDDIALOG_H
#define ENDDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QPrintDialog>
#include <QPainter>
#include <qcustomplot.h>

namespace Ui {
class EndDialog;
}
namespace myDialog {
class EndDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EndDialog(const QString&, QWidget *parent = 0);
    ~EndDialog();

private slots:
    void on_pushButton_print_clicked();
    void on_pushButton_next_clicked();

private:
    Ui::EndDialog   *ui;
    QCustomPlot     *plot1, *plot2, *plot3, *plot4;
    QPrintDialog    *printDialog;
    QPrinter        *printer;
};
}
#endif // ENDDIALOG_H
