#include "drawingfield.h"

DrawingField::DrawingField(QWidget *parent)
    : QWidget{parent}
{
    // ставим перо в центр поля
    curPenPos.setX(this->width()/2);
    curPenPos.setY(this->height()/2);
    // остальные инициализации
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
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

void DrawingField::paintEvent(QPaintEvent *event)
{

}
