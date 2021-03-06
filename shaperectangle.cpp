#include "shaperectangle.h"
#include <QPainter>

ShapeRectangle::ShapeRectangle(const QPointF p1, const QPointF p2, QPen pen) :
    Shape::Shape{ p1, p2, pen },
    rectangle{ this->p1, this->p2 }
{
}

void ShapeRectangle::draw(QPainter &painter) const
{
    painter.drawRect(rectangle);
}

bool ShapeRectangle::select(const QPointF point)
{
    return isSelected = rectangle.contains(point);
}

void ShapeRectangle::move(const QPointF from, const QPointF to)
{
    QPointF move{ to - from };
    p1 += move;
    p2 += move;
    rectangle.moveTo(rectangle.topLeft() + move);
}

QString ShapeRectangle::getShapeName() const
{
    return "Rectangle";
}
