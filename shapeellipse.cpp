#include "shapeellipse.h"
#include <QPainter>

ShapeEllipse::ShapeEllipse(const QPointF &p1, const QPointF &p2, QPen &pen) :
    Shape::Shape{ p1, p2, pen }
{
    path.addEllipse(QRectF{ this->p1, this->p2 });
}

void ShapeEllipse::draw(QPainter &painter) const
{
    painter.drawPath(path);
}

bool ShapeEllipse::select(const QPointF &point)
{
    return isSelected = path.contains(point);
}

void ShapeEllipse::move(const QPointF &from, const QPointF &to)
{
    path.translate(to - from);
}

QString ShapeEllipse::getShapeName() const
{
    return "Ellipse";
}
