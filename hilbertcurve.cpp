#include "hilbertcurve.h"

short HilbertCurve::getN() const
{
    return n;
}

int HilbertCurve::getInitialLenght() const
{
    return initialLenght;
}

void HilbertCurve::moveAndSaveLine(double xOffset, double yOffset)
{
    // сдвигаем
    currentPos = nextPos;
    nextPos.setX(nextPos.x() + xOffset);
    nextPos.setY(nextPos.y() + yOffset);
    // сохраняем
    lines.append(QLine(currentPos, nextPos));
    // сигналим
    emit newLineReady(lines.dequeue());
    // задержка
    thread()->msleep(pause);
}

void HilbertCurve::typeA(short n)
{
    if (n > 0) {
        typeD(n-1); // возможен переход в скобу типа D        
        moveAndSaveLine(-lineLenght, 0); // линия влево по горизонтали
        typeA(n-1); // возможен переход в скобу типа A
        moveAndSaveLine(0, lineLenght); // линия вниз по вертикали
        typeA(n-1); // возможен переход в скобу типа A
        moveAndSaveLine(lineLenght, 0); // линия вправо по горизонтали
        typeB(n-1); // возможен переход в скобу типа B
    }
}

void HilbertCurve::typeB(short n)
{
    if (n > 0) {
        typeC(n-1); // возможен переход в скобу типа C
        moveAndSaveLine(0, -lineLenght); // линия вверх по вертикали
        typeB(n-1); // возможен переход в скобу типа B        
        moveAndSaveLine(lineLenght, 0); // линия вправо по горизонтали
        typeB(n-1); // возможен переход в скобу типа B        
        moveAndSaveLine(0, lineLenght); // линия вниз по вертикали
        typeA(n-1); // возможен переход в скобу типа A
    }
}

void HilbertCurve::typeC(short n)
{
    if (n > 0) {
        typeB(n-1); // возможен переход в скобу типа B        
        moveAndSaveLine(lineLenght, 0); // линия вправо по горизонтали
        typeC(n-1); // возможен переход в скобу типа C        
        moveAndSaveLine(0, -lineLenght); // линия вверх по вертикали
        typeC(n-1); // возможен переход в скобу типа C        
        moveAndSaveLine(-lineLenght, 0); // линия влево по горизонтали
        typeD(n-1); // возможен переход в скобу типа D
    }
}

void HilbertCurve::typeD(short n)
{
    if (n > 0) {
        typeA(n-1); // возможен переход в скобу типа A        
        moveAndSaveLine(0, lineLenght); // линия вниз по вертикали
        typeD(n-1); // возможен переход в скобу типа D        
        moveAndSaveLine(-lineLenght, 0); // линия влево по горизонтали
        typeD(n-1); // возможен переход в скобу типа D        
        moveAndSaveLine(0, -lineLenght); // линия вверх по вертикали
        typeC(n-1); // возможен переход в скобу типа C
    }
}

HilbertCurve::HilbertCurve(QObject *parent) :
    QObject{parent} {
    n = 0;
    pause = 32;
    initialLenght = 128;
    currentPos.setX(0);
    currentPos.setY(0);
    nextPos.setX(0);
    nextPos.setY(0);
}

void HilbertCurve::makeCalculation()
{
    // подготовка
    lineLenght = initialLenght / n; // чем больше порядок кривой - тем меньше узор
    currentPos.setX(0);
    currentPos.setY(0);
    nextPos.setX(0);
    nextPos.setY(0);
    lines.clear();    
    typeA(n); // сам алгоритм
    // даем сигнал потоку, что можно заканчивать
    emit endBuildCurve();
}

void HilbertCurve::changeN(int value)
{
    n = value;
}

void HilbertCurve::changeInitialLenght(int value)
{
    initialLenght = value;
}
