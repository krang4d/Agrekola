#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m = new Measurement;
    setCentralWidget(m);
}

MainWindow::~MainWindow()
{
    delete m;
    delete ui;
}
