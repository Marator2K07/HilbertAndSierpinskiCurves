#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // инициализируем надписи с быстрым выбором и ставим им "приятелей"
    ui->curveOrderLabel->setText("&Порядок кривой:");
    ui->curveOrderLabel->setBuddy(ui->curveOrderValue);
    ui->initialCurveLenghtLabel->setText("Изначальный &размер кривой:");
    ui->initialCurveLenghtLabel->setBuddy(ui->initialCurveLenghtValue);
    // инициализируем поля
    drawingField = ui->graphicsView; // сделаем ссылку на поле отображения без посредников
    hilbertCurve = new HilbertCurve;
    sierpinskiCurve = new SierpinskiCurve;
     // о умолчанию выбрана Гильбертова кривая
    currentCurve = hilbertCurve;
    currentCurve->changeN(ui->curveOrderValue->value());
    currentCurve->changeInitialLenght(ui->initialCurveLenghtValue->value());
    // при каждом новом элементе кривой он будет появляться на представлении
    connect(hilbertCurve, SIGNAL(newLineReady(QLine)),
            drawingField, SLOT(drawLine(QLine)));
    connect(sierpinskiCurve, SIGNAL(newLineFReady(QLineF)),
            drawingField, SLOT(drawFLine(QLineF)));
    // связываем спинБоксы со слотами кривых
    connect(ui->curveOrderValue, SIGNAL(valueChanged(int)),
            hilbertCurve, SLOT(changeN(int)));
    connect(ui->curveOrderValue, SIGNAL(valueChanged(int)),
            sierpinskiCurve, SLOT(changeN(int)));
    connect(ui->initialCurveLenghtValue, SIGNAL(valueChanged(int)),
            hilbertCurve, SLOT(changeInitialLenght(int)));
    connect(ui->initialCurveLenghtValue, SIGNAL(valueChanged(int)),
            sierpinskiCurve, SLOT(changeInitialLenght(int)));
    // вычисление кривой происходит в отдельном потоке, причем
    // прорисовка идет постепенно, а не сразу, по нажатию кнопки
    QThread *threadAnother = new QThread(this);
    hilbertCurve->moveToThread(threadAnother);
    sierpinskiCurve->moveToThread(threadAnother);
    connect(threadAnother, SIGNAL(started()),
            hilbertCurve, SLOT(makeCalculation()));
    connect(hilbertCurve, SIGNAL(endBuildCurve()),
            threadAnother, SLOT(quit()));
    connect(ui->calcCurve, SIGNAL(clicked()),
            threadAnother, SLOT(start()));
    connect(ui->calcCurve, SIGNAL(clicked()),
            drawingField, SLOT(clean()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
