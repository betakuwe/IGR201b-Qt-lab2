#include "shape.h"
#include <QPainter>
#include "shapeline.h"
#include "shaperectangle.h"
#include "shapeellipse.h"
#include "drawboard.h"
#include <QPen>
#include <QDebug>

Shape::Shape(const QPointF p1, const QPointF p2, const QPen pen) :
    pen{ pen },
    isSelected{ false },
    p1{ p1 },
    p2{ p2 }
{

}

void Shape::setPen(const QPen pen)
{
    this->pen = pen;
}

QPen Shape::getPen() const
{
    return pen;
}

QPointF Shape::getP1() const
{
    return p1;
}

QPointF Shape::getP2() const
{
    return p2;
}

void Shape::paint(QPainter &painter) const
{
    if (isSelected)
    {
        QPen selectedPen{ pen };
        selectedPen.setWidth(std::max<int>(pen.width() + 2, pen.width() * 1.5));
        painter.setPen(selectedPen);
    } else {
        painter.setPen(pen);
    }
    draw(painter);
}

void Shape::deselect()
{
    isSelected = false;
}

QDataStream &operator<<(QDataStream &out, const Shape &shape)
{
    out << shape.getP1()
        << shape.getP2()
        << shape.getPen()
        << DrawBoard::stringToInsertMode[shape.getShapeName()];
    return out;
}

QDataStream &operator>>(QDataStream &in, Shape &shape)
{
    QPointF p1;
    QPointF p2;
    QPen pen;
    QString shapeName;
    DrawBoard::InsertMode insertMode;
    in >> p1 >> p2 >> pen >> insertMode;
    switch (insertMode) {
    case DrawBoard::InsertMode::Line:
        shape = ShapeLine(p1, p2, pen);
        break;
    case DrawBoard::InsertMode::Rectangle:
        shape = ShapeRectangle(p1, p2, pen);
        break;
    case DrawBoard::InsertMode::Ellipse:
        shape = ShapeEllipse(p1, p2, pen);
        break;
    }
    return in;
}
