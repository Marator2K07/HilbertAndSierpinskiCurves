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
    typeA(n);
    // запоминаем линию по диагонали вниз и вправо 🡦
    currentPos = nextPos;
    nextPos.setX(nextPos.x() + lineLenght/(sqrt(2)));
    nextPos.setY(nextPos.y() + lineLenght/(sqrt(2)));
    lines.append(QLineF(currentPos, nextPos));
    emit newLineReady(lines.dequeue()); // сигнализируем о готовности рисовать
    thread()->sleep(pause); // есть задержка для наглядности

    typeB(n);
    // запоминаем линию по диагонали вниз и влево 🡧
    currentPos = nextPos;
    nextPos.setX(nextPos.x() - lineLenght/(sqrt(2)));
    nextPos.setY(nextPos.y() + lineLenght/(sqrt(2)));
    lines.append(QLineF(currentPos, nextPos));
    emit newLineReady(lines.dequeue()); // сигнализируем о готовности рисовать
    thread()->sleep(pause); // есть задержка для наглядности

    typeC(n);
    // запоминаем линию по диагонали вверх и влево 🡤
    currentPos = nextPos;
    nextPos.setX(nextPos.x() - lineLenght/(sqrt(2)));
    nextPos.setY(nextPos.y() - lineLenght/(sqrt(2)));
    lines.append(QLineF(currentPos, nextPos));
    emit newLineReady(lines.dequeue()); // сигнализируем о готовности рисовать
    thread()->sleep(pause); // есть задержка для наглядности

    typeD(n);
    // запоминаем линию по диагонали вверх и вправо 🡥
    currentPos = nextPos;
    nextPos.setX(nextPos.x() + lineLenght/(sqrt(2)));
    nextPos.setY(nextPos.y() - lineLenght/(sqrt(2)));
    lines.append(QLineF(currentPos, nextPos));
    emit newLineReady(lines.dequeue()); // сигнализируем о готовности рисовать
    thread()->sleep(pause); // есть задержка для наглядности

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

void SierpinskiCurve::typeA(short n)
{
    if (n > 0) {
        typeA(n-1); // возможен переход в этот же тип
        // запоминаем линию по диагонали вниз и вправо 🡦
        currentPos = nextPos;
        nextPos.setX(nextPos.x() + lineLenght/(sqrt(2)));
        nextPos.setY(nextPos.y() + lineLenght/(sqrt(2)));
        lines.append(QLineF(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигнализируем о готовности рисовать
        thread()->sleep(pause); // есть задержка для наглядности
        typeB(n-1); // возможен переход в тип В
        // запоминаем линию по горизонтали вправо ->
        currentPos = nextPos;
        nextPos.setX(nextPos.x() + lineLenght * 2);
        lines.append(QLineF(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигнализируем о готовности рисовать
        thread()->sleep(pause); // есть задержка для наглядности
        typeD(n-1); // возможен переход в тип D
        // запоминаем линию по диагонали вправо и вверх 🡥
        currentPos = nextPos;
        nextPos.setX(nextPos.x() + lineLenght/(sqrt(2)));
        nextPos.setY(nextPos.y() - lineLenght/(sqrt(2)));
        lines.append(QLineF(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигнализируем о готовности рисовать
        thread()->sleep(pause); // есть задержка для наглядности
        typeA(n-1); // возможен переход в тип А
    }
}

void SierpinskiCurve::typeB(short n)
{
    if (n > 0) {
        typeB(n-1); // возможен переход в этот же тип
        // запоминаем линию по диагонали вниз и влево 🡧
        currentPos = nextPos;
        nextPos.setX(nextPos.x() - lineLenght/(sqrt(2)));
        nextPos.setY(nextPos.y() + lineLenght/(sqrt(2)));
        lines.append(QLineF(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигнализируем о готовности рисовать
        thread()->sleep(pause); // есть задержка для наглядности
        typeC(n-1); // возможен переход в тип C
        // запоминаем линию по вертикали вниз ↓
        currentPos = nextPos;
        nextPos.setY(nextPos.y() + lineLenght * 2);
        lines.append(QLineF(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигнализируем о готовности рисовать
        thread()->sleep(pause); // есть задержка для наглядности
        typeA(n-1); // возможен переход в тип A
        // запоминаем линию по диагонали вниз и вправо 🡦
        currentPos = nextPos;
        nextPos.setX(nextPos.x() + lineLenght/(sqrt(2)));
        nextPos.setY(nextPos.y() + lineLenght/(sqrt(2)));
        lines.append(QLineF(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигнализируем о готовности рисовать
        thread()->sleep(pause); // есть задержка для наглядности
        typeB(n-1); // возможен переход в тип B
    }
}

void SierpinskiCurve::typeC(short n)
{
    if (n > 0) {
        typeC(n-1); // возможен переход в этот же тип
        // запоминаем линию по диагонали вверх и влево 🡤
        currentPos = nextPos;
        nextPos.setX(nextPos.x() - lineLenght/(sqrt(2)));
        nextPos.setY(nextPos.y() - lineLenght/(sqrt(2)));
        lines.append(QLineF(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигнализируем о готовности рисовать
        thread()->sleep(pause); // есть задержка для наглядности
        typeD(n-1); // возможен переход в тип D
        // запоминаем линию по горизонтали вправо ←
        currentPos = nextPos;
        nextPos.setX(nextPos.x() - lineLenght * 2);
        lines.append(QLineF(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигнализируем о готовности рисовать
        thread()->sleep(pause); // есть задержка для наглядности
        typeB(n-1); // возможен переход в тип B
        // запоминаем линию по диагонали вниз и влево 🡧
        currentPos = nextPos;
        nextPos.setX(nextPos.x() - lineLenght/(sqrt(2)));
        nextPos.setY(nextPos.y() + lineLenght/(sqrt(2)));
        lines.append(QLineF(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигнализируем о готовности рисовать
        thread()->sleep(pause); // есть задержка для наглядности
        typeC(n-1); // возможен переход в тип С
    }
}

void SierpinskiCurve::typeD(short n)
{
    if (n > 0) {
        typeD(n-1); // возможен переход в этот же тип
        // запоминаем линию по диагонали вверх и вправо 🡥
        currentPos = nextPos;
        nextPos.setX(nextPos.x() + lineLenght/(sqrt(2)));
        nextPos.setY(nextPos.y() - lineLenght/(sqrt(2)));
        lines.append(QLineF(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигнализируем о готовности рисовать
        thread()->sleep(pause); // есть задержка для наглядности
        typeA(n-1); // возможен переход в тип A
        // запоминаем линию по вертикали вверх ↑
        currentPos = nextPos;
        nextPos.setY(nextPos.y() - lineLenght * 2);
        lines.append(QLineF(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигнализируем о готовности рисовать
        thread()->sleep(pause); // есть задержка для наглядности
        typeC(n-1); // возможен переход в тип C
        // запоминаем линию по диагонали влево и вверх 🡤
        currentPos = nextPos;
        nextPos.setX(nextPos.x() - lineLenght/(sqrt(2)));
        nextPos.setY(nextPos.y() - lineLenght/(sqrt(2)));
        lines.append(QLineF(currentPos, nextPos));
        emit newLineReady(lines.dequeue()); // сигнализируем о готовности рисовать
        thread()->sleep(pause); // есть задержка для наглядности
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
