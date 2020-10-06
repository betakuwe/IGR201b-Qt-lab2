#ifndef SHAPELINE_H
#define SHAPELINE_H

#include "shape.h"

class ShapeLine : public Shape
{
public:
    ShapeLine(const QPointF &p1, const QPointF &p2, QPen &pen);
    void draw(QPainter &painter) const override;
    bool select(const QPointF &point) override;
    void move(const QPointF &from, const QPointF &to) override;
    QString getShapeName() const override;

private:
    QLineF line;

    static qreal square(const qreal &real);
};

#endif // SHAPELINE_H
