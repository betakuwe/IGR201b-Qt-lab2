#ifndef SHAPE_H
#define SHAPE_H

#include <QPen>

class Shape
{
public:
    Shape(const QPointF p1, const QPointF p2, const QPen pen);
    virtual void draw(QPainter &painter) const = 0;
    virtual bool select(const QPointF point) = 0;
    virtual void move(const QPointF from, const QPointF to) = 0;
    virtual QString getShapeName() const = 0;

    void setPen(const QPen pen);
    QPen getPen() const;
    QPointF getP1() const;
    QPointF getP2() const;
    void paint(QPainter &painter) const;
    void deselect();

protected:
    QPen pen;
    bool isSelected;
    QPointF p1;
    QPointF p2;
};

QDataStream &operator<<(QDataStream &out, const Shape &shape);
QDataStream &operator>>(QDataStream &in, Shape &shape);

#endif // SHAPE_H
