#ifndef DRAWINGFIELD_H
#define DRAWINGFIELD_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPen>
#include <QPoint>
#include <QBrush>
#include <QColor>

class DrawingField : public QGraphicsView
{
    Q_OBJECT

public:
    explicit DrawingField(QWidget *parent = nullptr,
                          QGraphicsScene *pScene = nullptr);

    QPoint getCurPenPos() const;
    void setCurPenPos(QPoint newCurPenPos);
    void setCurPenPos(int x, int y);

private:
    QPen pen;
    QBrush brush;
    QPoint curPenPos; // поле с текущей позицией пишущей ручки
    QGraphicsScene *scene; // текущая сцена отображения элементов

public slots:
    void drawLine(QLine line);
};

#endif // DRAWINGFIELD_H
