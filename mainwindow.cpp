#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    drawingField = ui->drawingField; // сделаем ссылку на поле рисования без посредников
    hilbertCurve = new HilbertCurve();
}

MainWindow::~MainWindow()
{
    delete ui;
}

