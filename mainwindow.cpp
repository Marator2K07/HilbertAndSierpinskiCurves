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
    // заносим данные о кривых в комбоБокс через класс нашей модели!
    ComboBoxModel *model = new ComboBoxModel();
    ui->currentCurve->setModel(model);
    model->append("Гильбертова кривая", hilbertCurve);
    model->append("кривая Серпинского", sierpinskiCurve);
    // о умолчанию выбрана Гильбертова кривая
    ui->currentCurve->setCurrentIndex(0);
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
    threadWithCurve = new QThread(this);
    hilbertCurve->moveToThread(threadWithCurve);
    sierpinskiCurve->moveToThread(threadWithCurve);
    turnOnHilbertCurve(); // теперь подключаем слоты через отдельный метод
    connect(ui->calcCurve, SIGNAL(clicked()),
            threadWithCurve, SLOT(start()));
    connect(ui->calcCurve, SIGNAL(clicked()),
            drawingField, SLOT(clean()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::turnOnHilbertCurve()
{
    // включаем Гильбертову кривую в вычисления
    connect(threadWithCurve, SIGNAL(started()),
            hilbertCurve, SLOT(makeCalculation()));
    connect(hilbertCurve, SIGNAL(endBuildCurve()),
            threadWithCurve, SLOT(quit()));
    // выключаем кривую Серпинского из вычислений
    disconnect(threadWithCurve, SIGNAL(started()),
               sierpinskiCurve, SLOT(makeCalculation()));
    disconnect(sierpinskiCurve, SIGNAL(endBuildCurve()),
               threadWithCurve, SLOT(quit()));
}

void MainWindow::turnOnSierpinskiCurve()
{
    // включаем кривую Серпинского в вычисления
    connect(threadWithCurve, SIGNAL(started()),
            sierpinskiCurve, SLOT(makeCalculation()));
    connect(sierpinskiCurve, SIGNAL(endBuildCurve()),
            threadWithCurve, SLOT(quit()));
    // выключаем Гильбертову кривую из вычислений
    disconnect(threadWithCurve, SIGNAL(started()),
               hilbertCurve, SLOT(makeCalculation()));
    disconnect(hilbertCurve, SIGNAL(endBuildCurve()),
               threadWithCurve, SLOT(quit()));
}
