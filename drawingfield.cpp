#include "drawingfield.h"

DrawingField::DrawingField(QWidget *parent, QGraphicsScene *pScene)
    : QGraphicsView{pScene, parent}
{
    // инициализируем перо
    curPenPos.setX(this->width()/2);
    curPenPos.setY(this->height()/2);
    // ставим черный цвет для пера и инициализируем обьект сцены
    pen.setColor(QColor("black"));
    scene = new QGraphicsScene(this->rect());
}

QPoint DrawingField::getCurPenPos() const
{
    return curPenPos;
}

void DrawingField::setCurPenPos(QPoint newCurPenPos)
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

}
