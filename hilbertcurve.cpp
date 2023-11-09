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
    nextPos.setY(nextPos.x() + lineLenght);
    lines.append(QLine(currentPos, nextPos));
    typeB(n-1); // возможен переход в скобу типа B
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
