#ifndef DRAWINGFIELD_H
#define DRAWINGFIELD_H

#include <QWidget>
#include <QPen>
#include <QBrush>

class DrawingField : public QWidget
{
    Q_OBJECT

public:
    enum Shape {Line, Points};
    explicit DrawingField(QWidget *parent = nullptr);

private:
    Shape shape;
    QPen pen;
    QBrush brush;

protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // DRAWINGFIELD_H
