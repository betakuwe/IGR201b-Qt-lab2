#ifndef SHAPERECTANGLE_H
#define SHAPERECTANGLE_H

#include "shape.h"

class ShapeRectangle : public Shape
{
public:
    ShapeRectangle(const QPointF p1, const QPointF p2, QPen pen);
    void draw(QPainter &painter) const override;
    bool select(const QPointF point) override;
    void move(const QPointF from, const QPointF to) override;
    QString getShapeName() const override;

private:
    QRectF rectangle;
};

#endif // SHAPERECTANGLE_H
