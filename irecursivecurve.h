#ifndef IRECURSIVECURVE_H
#define IRECURSIVECURVE_H

#include <QObject>
#include <QLine>
#include <QLineF>
#include <QQueue>
#include <QThread>

class IRecursiveCurve
{
private:
    ///
    /// \brief moveLine
    /// сместить составную часть кривой (прямую) на значения сдвига
    virtual void moveLine(double xOffset, double yOffset) = 0;
    ///
    /// \brief typeA
    /// создает рекурсивную кривую типа А
    /// определенного порядка
    virtual void typeA(short n) = 0;
    ///
    /// \brief typeB
    /// создает рекурсивную кривую типа B
    /// определенного порядка
    virtual void typeB(short n) = 0;
    ///
    /// \brief typeC
    /// создает рекурсивную кривую типа C
    /// определенного порядка
    virtual void typeC(short n) = 0;
    ///
    /// \brief typeD
    /// создает рекурсивную кривую типа D
    /// определенного порядка
    virtual void typeD(short n) = 0;

public:
    ///
    /// \brief makeCalculation
    /// исходя из порядка кривой высчитывает
    /// общий рисунок, записывая полученные
    /// линии в соотвествующее поле
    virtual void makeCalculation() = 0;
    ///
    /// \brief changeN
    /// слот изменения порядка кривой для связки
    /// с графическим интерфейсом приложения
    virtual void changeN(int value) = 0;
    ///
    /// \brief changeInitialLenght
    /// слот изменения инициализационной главной длины кривой
    /// для связки с графическим интерфейсом приложения
    virtual void changeInitialLenght(int value) = 0;

signals:
    ///
    /// \brief endBuildCurve
    /// вычисление кривой закончилось
    virtual void endBuildCurve() = 0;
    ///
    /// \brief newLineReady
    /// оповещает о том, что очередная прямая кривой
    /// готова для использования.
    virtual void newLineReady(QLine line) = 0;
    ///
    /// \brief newLineFReady
    /// оповещает о том, что прямая с повышенной
    /// точностью координат готова
    virtual void newLineFReady(QLineF line) = 0;

};

#endif // IRECURSIVECURVE_H
