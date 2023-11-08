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

HilbertCurve::HilbertCurve()
{
    n = 0;
}

void HilbertCurve::makeCalculation()
{

}
