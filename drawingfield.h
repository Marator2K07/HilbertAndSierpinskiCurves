#ifndef DRAWINGFIELD_H
#define DRAWINGFIELD_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QPen>
#include <QPointF>
#include <QBrush>
#include <QColor>

class DrawingField : public QGraphicsView
{
    Q_OBJECT

public:
    explicit DrawingField(QWidget *parent = nullptr,
                          QGraphicsScene *pScene = nullptr);

    QPointF getCurPenPos() const;
    void setCurPenPos(QPointF newCurPenPos);
    void setCurPenPos(int x, int y);

private:
    QPen pen;
    QBrush brush;
    QPointF curPenPos; // поле с текущей позицией пишущей ручки
    QGraphicsScene *scene; // текущая сцена отображения элементов

public slots:
    void drawLine(QLine line);
    void drawFLine(QLineF line);
    void clean(); // слот для чистки текущей сцены
};

#endif // DRAWINGFIELD_H
