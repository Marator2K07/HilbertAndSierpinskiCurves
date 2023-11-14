#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawingfield.h"
#include "hilbertcurve.h"
#include "sierpinskicurve.h"

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

    IRecursiveCurve *currentCurve;
    HilbertCurve *hilbertCurve;
    SierpinskiCurve *sierpinskiCurve;
};
#endif // MAINWINDOW_H
