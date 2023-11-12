#include "drawingfield.h"

DrawingField::DrawingField(QWidget *parent, QGraphicsScene *pScene)
    : QGraphicsView{pScene, parent}
{
    // ставим черный цвет для пера и инициализируем обьект сцены
    pen.setColor(QColor("black"));
    scene = new QGraphicsScene(QRect(0, 0, 3750, 2550));
    scene->addRect(scene->sceneRect(), pen, brush);
    this->setScene(scene);
    // инициализируем перо
    curPenPos = scene->sceneRect().center();
}

QPointF DrawingField::getCurPenPos() const
{
    return curPenPos;
}

void DrawingField::setCurPenPos(QPointF newCurPenPos)
{
    curPenPos = newCurPenPos;
}

void DrawingField::setCurPenPos(int x, int y)
{
    curPenPos.setX(x);
    curPenPos.setY(y);
}

void DrawingField::drawLine(QLine line)
{
    QGraphicsLineItem *lineItem = new QGraphicsLineItem(line);
    lineItem->setPen(pen);
    lineItem->setPos(curPenPos);
    scene->addItem(lineItem);
}

void DrawingField::clean()
{
    scene->clear();
}
