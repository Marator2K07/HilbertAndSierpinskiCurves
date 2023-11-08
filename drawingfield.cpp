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

void DrawingField::paintEvent(QPaintEvent *event)
{

}
