#include "sierpinskicurve.h"

short SierpinskiCurve::getN() const
{
    return n;
}

int SierpinskiCurve::getInitialLenght() const
{
    return initialLenght;
}

void SierpinskiCurve::makeCalculation()
{
    // подготовка
    lineLenght = initialLenght / 2 / n; // чем больше порядок кривой - тем меньше узор
    currentPos.setX(0.0);
    currentPos.setY(0.0);
    nextPos.setX(0.0);
    nextPos.setY(0.0);
    lines.clear();

    // сам алгоритм начинается отсюда
    typeA(n); // рисуем участок кривой типа А
    // запоминаем линию по диагонали вниз и вправо 🡦
    moveAndSaveLine(lineLenght/(sqrt(2)), lineLenght/(sqrt(2)));
    typeB(n); // рисуем участок кривой типа В
    // запоминаем линию по диагонали вниз и влево 🡧
    moveAndSaveLine(-lineLenght/(sqrt(2)), lineLenght/(sqrt(2)));
    typeC(n); // рисуем участок кривой типа С
    // запоминаем линию по диагонали вверх и влево 🡤
    moveAndSaveLine(-lineLenght/(sqrt(2)), -lineLenght/(sqrt(2)));
    typeD(n); // рисуем участок кривой типа D
    // запоминаем линию по диагонали вверх и вправо 🡥
    moveAndSaveLine(lineLenght/(sqrt(2)), -lineLenght/(sqrt(2)));

    // даем сигнал потоку, что можно заканчивать
    emit endBuildCurve();
}

void SierpinskiCurve::changeN(int value)
{
    n = value;
}

void SierpinskiCurve::changeInitialLenght(int value)
{
    initialLenght = value;
}

void SierpinskiCurve::moveAndSaveLine(double xOffset, double yOffset)
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

void SierpinskiCurve::typeA(short n)
{
    if (n > 0) {
        typeA(n-1); // возможен переход в этот же тип
        // линия по диагонали вниз и вправо 🡦
        moveAndSaveLine(lineLenght/(sqrt(2)), lineLenght/(sqrt(2)));
        typeB(n-1); // возможен переход в тип В
        // линия по горизонтали вправо ->
        moveAndSaveLine(lineLenght * 2, 0);
        typeD(n-1); // возможен переход в тип D
        // линия по диагонали вправо и вверх 🡥
        moveAndSaveLine(lineLenght/(sqrt(2)), -lineLenght/(sqrt(2)));
        typeA(n-1); // возможен переход в тип А
    }
}

void SierpinskiCurve::typeB(short n)
{
    if (n > 0) {
        typeB(n-1); // возможен переход в этот же тип
        // линия по диагонали вниз и влево 🡧
        moveAndSaveLine(-lineLenght/(sqrt(2)), lineLenght/(sqrt(2)));
        typeC(n-1); // возможен переход в тип C
        // линия по вертикали вниз ↓
        moveAndSaveLine(0, lineLenght * 2);
        typeA(n-1); // возможен переход в тип A
        // линия по диагонали вниз и вправо 🡦
        moveAndSaveLine(lineLenght/(sqrt(2)), lineLenght/(sqrt(2)));
        typeB(n-1); // возможен переход в тип B
    }
}

void SierpinskiCurve::typeC(short n)
{
    if (n > 0) {
        typeC(n-1); // возможен переход в этот же тип
        // линия по диагонали вверх и влево 🡤
        moveAndSaveLine(-lineLenght/(sqrt(2)), -lineLenght/(sqrt(2)));
        typeD(n-1); // возможен переход в тип D
        // линия по горизонтали влево ←
        moveAndSaveLine(-lineLenght * 2, 0);
        typeB(n-1); // возможен переход в тип B
        // линия по диагонали вниз и влево 🡧
        moveAndSaveLine(-lineLenght/(sqrt(2)), lineLenght/(sqrt(2)));
        typeC(n-1); // возможен переход в тип С
    }
}

void SierpinskiCurve::typeD(short n)
{
    if (n > 0) {
        typeD(n-1); // возможен переход в этот же тип
        // линия по диагонали вверх и вправо 🡥
        moveAndSaveLine(lineLenght/(sqrt(2)), -lineLenght/(sqrt(2)));
        typeA(n-1); // возможен переход в тип A
        // линия по вертикали вверх ↑
        moveAndSaveLine(0, -lineLenght * 2);
        typeC(n-1); // возможен переход в тип C
        // линия по диагонали влево и вверх 🡤
        moveAndSaveLine(-lineLenght/(sqrt(2)), -lineLenght/(sqrt(2)));
        typeD(n-1); // возможен переход в тип D
    }
}

SierpinskiCurve::SierpinskiCurve(QObject *parent)
    : QObject{parent}
{
    n = 0;
    pause = 32;
    initialLenght = 128;
    currentPos.setX(0.0);
    currentPos.setY(0.0);
    nextPos.setX(0.0);
    nextPos.setY(0.0);
}
