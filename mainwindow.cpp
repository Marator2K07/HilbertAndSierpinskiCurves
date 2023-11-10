#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    drawingField = ui->graphicsView; // сделаем ссылку на поле отображения без посредников
    hilbertCurve = new HilbertCurve;
    // при каждом новом элементе кривой он будет появляться на представлении
    connect(hilbertCurve, SIGNAL(newLineReady(QLine)),
            drawingField, SLOT(drawLine(QLine)));
    // сразу пытаемся задать порядок кривой, длину ее звена
    // и собственно вычислить ее
    hilbertCurve->setN(2);
    hilbertCurve->makeCalculation();
}

MainWindow::~MainWindow()
{
    delete ui;
}

