#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawingfield.h"
#include "hilbertcurve.h"
#include "sierpinskicurve.h"
#include "recursivecurvesmodel.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DrawingField *drawingField;

    QThread *threadWithCurve;
    IRecursiveCurve *currentCurve;
    HilbertCurve *hilbertCurve;
    SierpinskiCurve *sierpinskiCurve;

private:
    ///
    /// \brief newCalculationCurrentCurve
    /// создается новый поток, в который идет текущая кривая
    /// с инициализацией сигнально-слотовых соединений для расчетов
    void newCalculationCurrentCurve();
    ///
    /// \brief finishCalculationCurrentCurve
    /// после использования потока, рвем его связи и
    /// освобождаем занятую им память
    void finishCalculationCurrentCurve();

private slots:
    void changeCurrentCurve(int newIndex);

    void on_calcCurve_clicked();
};
#endif // MAINWINDOW_H
