#ifndef SHAPEELLIPSE_H
#define SHAPEELLIPSE_H

#include "shape.h"

class ShapeEllipse : public Shape
{
public:
    ShapeEllipse(const QPointF p1, const QPointF p2, QPen pen);
    void draw(QPainter &painter) const override;
    bool select(const QPointF point) override;
    void move(const QPointF from, const QPointF to) override;
    QString getShapeName() const override;

private:
    QPainterPath path;
};

#endif // SHAPEELLIPSE_H
