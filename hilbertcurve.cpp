#include "hilbertcurve.h"

short HilbertCurve::getN() const
{
    return n;
}

void HilbertCurve::setN(short newN)
{
    n = newN;
}

QQueue<QLine> HilbertCurve::getLines() const
{
    return lines;
}

int HilbertCurve::getInitialLenght() const
{
    return initialLenght;
}

void HilbertCurve::setInitialLenght(int newInitialLenght)
{
    initialLenght = newInitialLenght;
}

void HilbertCurve::typeA(short n)
{
    if (n > 0) {
        typeD(n-1); // возможен переход в скобу типа D
        // запоминаем линию влево по горизонтали
        currentPos = nextPos;
        nextPos.setX(nextPos.x() - lineLenght);
        lines.append(QLine(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигналим, что можно рисовать эту линию
        thread()->msleep(pause);
        typeA(n-1); // возможен переход в скобу типа A
        // запоминаем линию вниз по вертикали
        currentPos = nextPos;
        nextPos.setY(nextPos.y() + lineLenght);
        lines.append(QLine(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигналим, что можно рисовать эту линию
        thread()->msleep(pause);
        typeA(n-1); // возможен переход в скобу типа A
        // запоминаем линию вправо по горизонтали
        currentPos = nextPos;
        nextPos.setX(nextPos.x() + lineLenght);
        lines.append(QLine(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигналим, что можно рисовать эту линию
        thread()->msleep(pause);
        typeB(n-1); // возможен переход в скобу типа B
    }
}

void HilbertCurve::typeB(short n)
{
    if (n > 0) {
        typeC(n-1); // возможен переход в скобу типа C
        // запоминаем линию вверх по вертикали
        currentPos = nextPos;
        nextPos.setY(nextPos.y() - lineLenght);
        lines.append(QLine(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигналим, что можно рисовать эту линию
        thread()->msleep(pause);
        typeB(n-1); // возможен переход в скобу типа B
        // запоминаем линию вправо по горизонтали
        currentPos = nextPos;
        nextPos.setX(nextPos.x() + lineLenght);
        lines.append(QLine(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигналим, что можно рисовать эту линию
        thread()->msleep(pause);
        typeB(n-1); // возможен переход в скобу типа B
        // запоминаем линию вниз по вертикали
        currentPos = nextPos;
        nextPos.setY(nextPos.y() + lineLenght);
        lines.append(QLine(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигналим, что можно рисовать эту линию
        thread()->msleep(pause);
        typeA(n-1); // возможен переход в скобу типа A
    }
}

void HilbertCurve::typeC(short n)
{
    if (n > 0) {
        typeB(n-1); // возможен переход в скобу типа B
        // запоминаем линию вправо по горизонтали
        currentPos = nextPos;
        nextPos.setX(nextPos.x() + lineLenght);
        lines.append(QLine(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигналим, что можно рисовать эту линию
        thread()->msleep(pause);
        typeC(n-1); // возможен переход в скобу типа C
        // запоминаем линию вверх по вертикали
        currentPos = nextPos;
        nextPos.setY(nextPos.y() - lineLenght);
        lines.append(QLine(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигналим, что можно рисовать эту линию
        thread()->msleep(pause);
        typeC(n-1); // возможен переход в скобу типа C
        // запоминаем линию влево по горизонтали
        currentPos = nextPos;
        nextPos.setX(nextPos.x() - lineLenght);
        lines.append(QLine(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигналим, что можно рисовать эту линию
        thread()->msleep(pause);
        typeD(n-1); // возможен переход в скобу типа D
    }
}

void HilbertCurve::typeD(short n)
{
    if (n > 0) {
        typeA(n-1); // возможен переход в скобу типа A
        // запоминаем линию вниз по вертикали
        currentPos = nextPos;
        nextPos.setY(nextPos.y() + lineLenght);
        lines.append(QLine(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигналим, что можно рисовать эту линию
        thread()->msleep(pause);
        typeD(n-1); // возможен переход в скобу типа D
        // запоминаем линию влево по горизонтали
        currentPos = nextPos;
        nextPos.setX(nextPos.x() - lineLenght);
        lines.append(QLine(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигналим, что можно рисовать эту линию
        thread()->msleep(pause);
        typeD(n-1); // возможен переход в скобу типа D
        // запоминаем линию вверх по вертикали
        currentPos = nextPos;
        nextPos.setY(nextPos.y() - lineLenght);
        lines.append(QLine(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигналим, что можно рисовать эту линию
        thread()->msleep(pause);
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

void HilbertCurve::changeN(short value)
{
    setN(value);
}

void HilbertCurve::initialLenght(int value)
{
    setInitialLenght(value);
}
