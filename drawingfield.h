#ifndef DRAWINGFIELD_H
#define DRAWINGFIELD_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPalette>
#include <QPainter>

class DrawingField : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingField(QWidget *parent = nullptr);

private:
    QPen pen;
    QBrush brush;
    QPainter painter;

protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // DRAWINGFIELD_H
