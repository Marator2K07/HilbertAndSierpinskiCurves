#include "drawingfield.h"

DrawingField::DrawingField(QWidget *parent)
    : QWidget{parent}
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

void DrawingField::paintEvent(QPaintEvent *event)
{

}
