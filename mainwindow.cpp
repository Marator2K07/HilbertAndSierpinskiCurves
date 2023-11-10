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
    // сразу пытаемся задать порядок кривой и, собственно,
    // вычислить ее; причем кривая будет работать в отдельном потоке!
    QThread *threadAnother = new QThread(this);
    hilbertCurve->moveToThread(threadAnother);
    connect(threadAnother, SIGNAL(started()),
            hilbertCurve, SLOT(makeCalculation()));
    connect(hilbertCurve, SIGNAL(endBuildCurve()),
            threadAnother, SLOT(quit()));
    hilbertCurve->setN(5);
    threadAnother->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

