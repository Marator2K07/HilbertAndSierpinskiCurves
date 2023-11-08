#ifndef DRAWINGFIELD_H
#define DRAWINGFIELD_H

#include <QWidget>
#include <QPen>
#include <QPoint>
#include <QBrush>
#include <QPalette>
#include <QPainter>

class DrawingField : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingField(QWidget *parent = nullptr);

    QPoint getCurPenPos() const;
    void setCurPenPos(QPoint newCurPenPos);
    void setCurPenPos(int x, int y);

private:
    QPen pen;
    QBrush brush;
    QPainter painter;
    QPoint curPenPos; // поле с текущей позицией пишущей ручки



protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // DRAWINGFIELD_H
