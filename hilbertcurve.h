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
    void setN(short newN);
    QQueue<QLine> getLines() const;
    int getInitialLenght() const;
    void setInitialLenght(int newInitialLenght);

public slots:
    void makeCalculation() override; // описание в интерфейсе
    void changeN(int value) override; // описание в интерфейсе
    void changeInitialLenght(int value) override; // описание в интерфейсе

signals:
    ///
    /// \brief endBuildCurve
    /// вычисление кривой закончилось
    void endBuildCurve();
    ///
    /// \brief newLineReady
    /// оповещает о том, что очереденая прямая кривой
    /// готова для использования.
    void newLineReady(QLine line);
};

#endif // HILBERTCURVE_H
