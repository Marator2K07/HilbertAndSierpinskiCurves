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
