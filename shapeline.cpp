#include "shapeline.h"
#include <QPainter>

ShapeLine::ShapeLine(const QPointF &p1, const QPointF &p2, QPen &pen) :
    Shape::Shape{ p1, p2, pen },
    line{ this->p1, this->p2 }
{
}

void ShapeLine::draw(QPainter &painter) const
{
    painter.drawLine(line);
}

bool ShapeLine::select(const QPointF &point)
{
    // check if the distance from point to line is at most 2
    return isSelected = square
            (
                (line.y2() - line.y1()) * point.x()
                    - (line.x2() - line.x1()) * point.y()
                    + line.x2() * line.y1()
                    - line.y2() * line.x1()
            ) /
            (
                square(line.y2() - line.y1())
                + square(line.x2() - line.x1())
            ) <= square(pen.width() + 2);
}

void ShapeLine::move(const QPointF &from, const QPointF &to)
{
    QPointF move{ to - from };
    line.setP1(line.p1() + move);
    line.setP2(line.p2() + move);

}

QString ShapeLine::getShapeName() const
{
    return "Line";
}

qreal ShapeLine::square(const qreal &real)
{
    return real * real;
}
