#include "sierpinskicurve.h"

short SierpinskiCurve::getN() const
{
    return n;
}

void SierpinskiCurve::setN(short newN)
{
    n = newN;
}

int SierpinskiCurve::getInitialLenght() const
{
    return initialLenght;
}

void SierpinskiCurve::setInitialLenght(int newInitialLenght)
{
    initialLenght = newInitialLenght;
}

void SierpinskiCurve::typeA(short n)
{
    /*
    if (n > 0) {
        typeA(n-1); // возможен переход в этот же тип
        // запоминаем линию по диагонали вниз и вправо 🡦
        currentPos = nextPos;
    }
    */
}

SierpinskiCurve::SierpinskiCurve(QObject *parent)
    : QObject{parent}
{

}
