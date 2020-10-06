#include "shaperectangle.h"
#include <QPainter>

ShapeRectangle::ShapeRectangle(const QPointF &p1, const QPointF &p2, QPen &pen) :
    Shape::Shape{ p1, p2, pen },
    rectangle{ this->p1, this->p2 }
{
}

void ShapeRectangle::draw(QPainter &painter) const
{
    painter.drawRect(rectangle);
}

bool ShapeRectangle::select(const QPointF &point)
{
    return isSelected = rectangle.contains(point);
}

void ShapeRectangle::move(const QPointF &from, const QPointF &to)
{
    rectangle.moveTo(rectangle.topLeft() + to - from);
}

QString ShapeRectangle::getShapeName() const
{
    return "Rectangle";
}
