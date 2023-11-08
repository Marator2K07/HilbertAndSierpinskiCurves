#ifndef HILBERTCURVE_H
#define HILBERTCURVE_H

#include <QLine>
#include <QQueue>

///
/// \brief The HilbertCurve class
/// представляет собой Гибельтову кривую n-порядка
/// ниже изображены четыре по-разному повернутые
/// варианты базовой кривой (которая выглядит как скоба,
/// состоящая из трех прямый линий), а шаги рисования
/// соединительных линий обозначены стрелками, направленными
/// соответственно.
/// A: D ← A ↓ A → B
/// B: C ↑ B → B ↓ A
/// C: B → C ↑ C ← D
/// D: A ↓ D ← D ↑ C
class HilbertCurve
{
private:
    short n; // порядок кривой
    QQueue<QLine> lines; // из каких прямых состоит данная кривая

public:
    HilbertCurve();
    short getN() const;
    void setN(short newN);
    QQueue<QLine> getLines() const;
    ///
    /// \brief makeCalculation
    /// исходя из порядка кривой высчитывает
    /// общий рисунок, записывая полученные
    /// линии в соотвествующее поле
    void makeCalculation();

};

#endif // HILBERTCURVE_H
