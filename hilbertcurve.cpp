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

int HilbertCurve::getLineLenght() const
{
    return lineLenght;
}

void HilbertCurve::setLineLenght(int newLineLenght)
{
    lineLenght = newLineLenght;
}

void HilbertCurve::typeA(short n)
{
    if (n > 0) {
        typeD(n-1); // возможен переход в скобу типа D
        // запоминаем линию влево по горизонтали
        currentPos = nextPos;
        nextPos.setX(nextPos.x() - lineLenght);
        lines.append(QLine(currentPos, nextPos));
        typeA(n-1); // возможен переход в скобу типа A
        // запоминаем линию вниз по вертикали
        currentPos = nextPos;
        nextPos.setY(nextPos.y() + lineLenght);
        lines.append(QLine(currentPos, nextPos));
        typeA(n-1); // возможен переход в скобу типа A
        // запоминаем линию вправо по горизонтали
        currentPos = nextPos;
        nextPos.setX(nextPos.x() + lineLenght);
        lines.append(QLine(currentPos, nextPos));
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
        typeB(n-1); // возможен переход в скобу типа B
        // запоминаем линию вправо по горизонтали
        currentPos = nextPos;
        nextPos.setX(nextPos.x() + lineLenght);
        lines.append(QLine(currentPos, nextPos));
        typeB(n-1); // возможен переход в скобу типа B
        // запоминаем линию вниз по вертикали
        currentPos = nextPos;
        nextPos.setY(nextPos.y() + lineLenght);
        lines.append(QLine(currentPos, nextPos));
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
        typeC(n-1); // возможен переход в скобу типа C
        // запоминаем линию вверх по вертикали
        currentPos = nextPos;
        nextPos.setY(nextPos.y() - lineLenght);
        lines.append(QLine(currentPos, nextPos));
        typeC(n-1); // возможен переход в скобу типа C
        // запоминаем линию влево по горизонтали
        currentPos = nextPos;
        nextPos.setX(nextPos.x() - lineLenght);
        lines.append(QLine(currentPos, nextPos));
        typeA(n-1); // возможен переход в скобу типа D
    }
}

HilbertCurve::HilbertCurve()
{
    n = 0;
    lineLenght = 55;
    currentPos.setX(0);
    currentPos.setY(0);
    nextPos.setX(0);
    nextPos.setY(0);
}

void HilbertCurve::makeCalculation()
{

}
