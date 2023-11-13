#ifndef SIERPINSKICURVE_H
#define SIERPINSKICURVE_H

#include "irecursivecurve.h"

using namespace  std;

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
    double lineLenght; // длина прямой для составления кривой
    QPointF currentPos; // начало текущей линии
    QPointF nextPos; // конец текущей линии
    QQueue<QLineF> lines; // очередь из прямых

    ///
    /// \brief typeA
    /// создает кривую Серпинского как на схеме и
    /// в описании класса (A: A 🡦 B → D 🡥 A)
    void typeA(short n) override;
    ///
    /// \brief typeB
    /// создает кривую Серпинского как на схеме и
    /// в описании класса (B: B 🡧 C ↓ A 🡦 B)
    void typeB(short n) override;

public:
    explicit SierpinskiCurve(QObject *parent = nullptr);

    short getN() const;
    void setN(short newN);
    int getInitialLenght() const;
    void setInitialLenght(int newInitialLenght);

signals:
    ///
    /// \brief endBuildCurve
    /// вычисление кривой закончилось
    void endBuildCurve();
    ///
    /// \brief newLineReady
    /// оповещает о том, что очереденая прямая кривой
    /// готова для использования.
    void newLineReady(QLineF line);
};

#endif // SIERPINSKICURVE_H
