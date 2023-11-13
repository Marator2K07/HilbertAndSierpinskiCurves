#ifndef SIERPINSKICURVE_H
#define SIERPINSKICURVE_H

#include "irecursivecurve.h"

///
/// \brief The SierpinskiCurve class
/// представляет возможности для нахождения
/// и отображения кривой Серпинского n-порядка
/// ниже изображены четыре по-разному повернутые
/// варианты базовой кривой (которая выглядит как скоба,
/// состоящая из трех прямый линий, крайние из которых повренуты
/// на 45% относительно продолжения центральной прямой), а шаги рисования
/// соединительных линий обозначены стрелками, направленными соответственно.
/// A: A 🡦 B → D 🡥 A
/// B: B 🡧 C ↓ A 🡦 B
/// C: C 🡤 D ← B 🡧 C
/// D: D 🡥 A ↑ C 🡤 D
class SierpinskiCurve : public QObject,
                        public IRecursiveCurve
{
    Q_OBJECT

private:
    long pause; // пауза отрисовки в миллисекундах
    short n; // порядок кривой
    int initialLenght; // изначальная стартовая длина прямой для кривой
    int lineLenght; // длина прямой для составления кривой
    QPoint currentPos; // начало текущей линии
    QPoint nextPos; // конец текущей линии
    QQueue<QLine> lines; // очередь из прямых

public:
    explicit SierpinskiCurve(QObject *parent = nullptr);

signals:

};

#endif // SIERPINSKICURVE_H
