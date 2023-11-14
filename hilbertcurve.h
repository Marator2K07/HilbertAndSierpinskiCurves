 #ifndef HILBERTCURVE_H
#define HILBERTCURVE_H

#include "irecursivecurve.h"

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
class HilbertCurve : public QObject,
                     public IRecursiveCurve
{
    Q_OBJECT

private:
    long pause; // пауза после нахождения элемента кривой в миллисекундах
    short n; // порядок кривой
    int initialLenght; // изначальная стартовая длина прямой для кривой
    int lineLenght; // длина прямой для составления кривой
    QPoint currentPos; // начало текущей линии
    QPoint nextPos; // конец текущей линии
    QQueue<QLine> lines; // из каких прямых состоит данная кривая

    // IRecursiveCurve interface
private:
    ///
    /// \brief typeA
    /// создает Гильбертову кривую как на схеме и
    /// в описании классе (A: D ← A ↓ A → B)
    void typeA(short n) override;
    ///
    /// \brief typeB
    /// создает Гильбертову кривую как на схеме и
    /// в описании классе (B: C ↑ B → B ↓ A)
    void typeB(short n) override;
    ///
    /// \brief typeC
    /// создает Гильбертову кривую как на схеме и
    /// в описании классе (C: B → C ↑ C ← D)
    void typeC(short n) override;
    ///
    /// \brief typeD
    /// создает Гильбертову кривую как на схеме и
    /// в описании классе (D: A ↓ D ← D ↑ C)
    void typeD(short n) override;

public:
    explicit HilbertCurve(QObject *parent = nullptr);

    short getN() const;
    int getInitialLenght() const;

    // IRecursiveCurve interface
public slots:
    void makeCalculation() override;
    void changeN(int value) override;
    void changeInitialLenght(int value) override;

    // IRecursiveCurve interface
signals:
    void endBuildCurve() override;
    void newLineReady(QLine line) override;
    void newLineFReady(QLineF line) override;
};

#endif // HILBERTCURVE_H
