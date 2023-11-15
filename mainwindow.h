#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawingfield.h"
#include "hilbertcurve.h"
#include "sierpinskicurve.h"
#include "comboboxmodel.h"

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
    /// \brief turnOnHilbertCurve
    /// включение кривой в расчет представления,
    /// то есть коннектим Гильбертову кривую и дисконнектим
    /// остальные (кривую Серпинского)
    void turnOnHilbertCurve();
    ///
    /// \brief turnOnSierpinskiCurve
    /// включение кривой Серпинского в расчет представления,
    /// то есть коннектим эту кривую и дисконнектим
    /// остальные (Гильбертову кривую)
    void turnOnSierpinskiCurve();
};
#endif // MAINWINDOW_H
