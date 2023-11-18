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
    RecursiveCurvesModel *model = new RecursiveCurvesModel();
    ui->currentCurveComboBox->setModel(model);
    model->append("Гильбертова кривая", hilbertCurve);
    model->append("кривая Серпинского", sierpinskiCurve);
    // по умолчанию выбрана Гильбертова кривая
    ui->currentCurveComboBox->setCurrentIndex(0);
    currentCurve = hilbertCurve;
    currentCurve->changeN(ui->curveOrderValue->value());
    currentCurve->changeInitialLenght(ui->initialCurveLenghtValue->value());
    // при взаимодействии с комбоБоксом меняется текущая кривая
    connect(ui->currentCurveComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeCurrentCurve(int)));
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
    // не забываем
    threadWithCurve = new QThread;
}

MainWindow::~MainWindow()
{
    // чтобы приложение закрывалось без исключений,
    // надо поток плавно остановить
    if (threadWithCurve != nullptr) {
        threadWithCurve->quit();
        threadWithCurve->wait();
    }
    delete ui;
}

void MainWindow::newCalculationCurrentCurve()
{
    // перед вычислениями записываем важные данные кривой и отправляем в поток
    currentCurve->changeN(ui->curveOrderValue->value());
    currentCurve->changeInitialLenght(ui->initialCurveLenghtValue->value());
    dynamic_cast<QObject*>(currentCurve)->moveToThread(threadWithCurve);
    // также соединяем связи
    connect(threadWithCurve, SIGNAL(started()),
            dynamic_cast<QObject*>(currentCurve),
            SLOT(makeCalculation()));
    connect(dynamic_cast<QObject*>(currentCurve),
            SIGNAL(endBuildCurve()),
            threadWithCurve, SLOT(quit()));
    connect(threadWithCurve, SIGNAL(finished()),
            this, SLOT(finishCalculationCurrentCurve()));
}

void MainWindow::finishCalculationCurrentCurve()
{
    // после вычислений, можно освободить связи
    disconnect(threadWithCurve, SIGNAL(started()),
               dynamic_cast<QObject*>(currentCurve),
               SLOT(makeCalculation()));
    disconnect(dynamic_cast<QObject*>(currentCurve),
               SIGNAL(endBuildCurve()),
               threadWithCurve, SLOT(quit()));
    disconnect(threadWithCurve, SIGNAL(finished()),
               this, SLOT(finishCalculationCurrentCurve()));
}

void MainWindow::changeCurrentCurve(int)
{
    // если сменили вид кривой, во время расчета другой
    if (threadWithCurve != nullptr) {
        threadWithCurve->quit();
        threadWithCurve->wait();
    }
    // меняем текущую кривую
    currentCurve = qvariant_cast<IRecursiveCurve*>(ui->currentCurveComboBox->currentData());
}

void MainWindow::onCalcCurveClicked()
{
    newCalculationCurrentCurve();
    drawingField->clean();
    threadWithCurve->start();
}

