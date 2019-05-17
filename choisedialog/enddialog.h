#ifndef ENDDIALOG_H
#define ENDDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QPrintDialog>
#include <QPainter>
#include <QMap>
#include <qcustomplot.h>

//namespace Ui {
//class EndDialog;
//}
namespace myDialog {
class EndDialog : public QDialog
{
    Q_OBJECT
    void graph(QMap<double, double>, QCustomPlot*);

public:
    explicit EndDialog(const QString&, QMap<double, double>,QMap<double, double>,QMap<double, double>,QMap<double, double>, QWidget *parent = 0);
    //EndDialog(const QString&, QMap<double, double>,QMap<double, double>,QMap<double, double>,QMap<double, double>, QWidget *parent = 0);
    ~EndDialog();

private slots:
    void on_pushButton_print_clicked();
    void on_pushButton_next_clicked();

private:
    //Ui::EndDialog   *ui;
    QPushButton *pushButton_print, *pushButton_next;
    //QCustomPlot     *plot1, *plot2, *plot3, *plot4;
    QPrintDialog    *printDialog;
    QPrinter        *printer;
    QVector<QCustomPlot*> plots;
};
}
#endif // ENDDIALOG_H
