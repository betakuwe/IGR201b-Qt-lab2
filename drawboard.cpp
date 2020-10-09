#include "drawboard.h"
#include <QPainter>
#include <QMouseEvent>
#include "shapeline.h"
#include "shaperectangle.h"
#include "shapeellipse.h"

DrawBoard::DrawBoard(QWidget *parent) :
    QWidget(parent),
    drawing{ false },
    insertMode{ Line },
    selectedShapeIndex{ -1 },
    dragging{ false },
    myCurrentShape{ nullptr }
{

}

void DrawBoard::pickColor(const QColor color)
{
    pen.setColor(color);
    applyStyle();
}

void DrawBoard::setWidth(const int width)
{
    pen.setWidth(width);
    applyStyle();
}

void DrawBoard::setStyle(const QString &styleString)
{
    pen.setStyle(stringToPenStyle[styleString]);
    applyStyle();
}

void DrawBoard::setMode(const QString &modeString)
{
    mode = stringToMode[modeString];
    if (mode == Insert)
    {
        deselectShape();
        update();
    }
}

void DrawBoard::setInsertMode(const QString &insertModeString)
{
    insertMode = stringToInsertMode[insertModeString];
}

QVector<Shape*> DrawBoard::getShapes() const
{
    return myShapes;
}

void DrawBoard::setShapes(QVector<Shape*> shapes)
{
    myShapes = shapes;
    update();
}

void DrawBoard::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    for (Shape *shape : myShapes)
    {
        shape->paint(painter);
    }
    if (drawing && myCurrentShape != nullptr)
    {
        myCurrentShape->paint(painter);
    }
    // TODO edit mode
}

void DrawBoard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) return;
    switch (mode)
    {
    case Edit:
        lastTranslationPoint = event->pos();
        selectShape(event->pos());
        break;
    case Insert:
        lastPoint = event->pos();
        myDrawShape(event->pos());
        drawing = true;
        update();
    }
}

void DrawBoard::mouseMoveEvent(QMouseEvent *event)
{
    dragging = true;
    switch (mode)
    {
    case Edit:
        moveShape(event->pos());
        lastTranslationPoint = event->pos();
        update();
        break;
    case Insert:
        if (!drawing) return;
        myDrawShape(event->pos());
        update();
    }
}

void DrawBoard::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) return;
    switch (mode)
    {
    case Edit:
        if (dragging) {
            moveShape(event->pos());
//            selectedShapeIndex = -1;
        }
        dragging = false;
        update();
        break;
    case Insert:
        myDrawShape(event->pos());
        myShapes += myCurrentShape;
        drawing = false;
        dragging = false;
    }
}

void DrawBoard::myDrawShape(const QPointF &endPoint)
{
    switch (insertMode)
    {
    case Line:
        myCurrentShape = new ShapeLine{ lastPoint, endPoint, pen };
        break;
    case Rectangle:
        myCurrentShape = new ShapeRectangle{ lastPoint, endPoint, pen };
        break;
    case Ellipse:
        myCurrentShape = new ShapeEllipse{ lastPoint, endPoint, pen };
        break;
    }
}

void DrawBoard::selectShape(const QPointF &selectedPoint)
{
    deselectShape();
    for (int i = 0; i < myShapes.length(); ++i)
    {
        if (myShapes[i]->select(selectedPoint))
        {
            emit shapeSelected(*myShapes[i]);
            selectedShapeIndex = i;
            return;
        }
    }
    selectedShapeIndex = -1;
}

void DrawBoard::deselectShape()
{
    if (selectedShapeIndex >= 0) {
        myShapes[selectedShapeIndex]->deselect();
    }
}

void DrawBoard::moveShape(const QPointF &endPoint)
{
    if (selectedShapeIndex < 0) return;
    myShapes[selectedShapeIndex]->move(lastTranslationPoint, endPoint);
}

void DrawBoard::applyStyle() {
    if (mode == Edit && selectedShapeIndex >= 0)
    {
        myShapes[selectedShapeIndex]->setPen(pen);
//        shapes.replace(selectedShapeIndex, std::make_pair(currentShape.first, shapes[selectedShapeIndex].second));
        update();
    }
}

std::map<QString, Qt::PenStyle> DrawBoard::stringToPenStyle =
{
    { "Solid Line", Qt::SolidLine },
    { "Dash Line", Qt::DashLine },
    { "Dot Line", Qt::DotLine },
    { "Dash Dot Line", Qt::DashDotLine },
    { "Dash Dot Dot Line", Qt::DashDotDotLine }
};

std::map<Qt::PenStyle, QString> DrawBoard::penStyleToString =
{
    { Qt::SolidLine, "Solid Line" },
    { Qt::DashLine, "Dash Line" },
    { Qt::DotLine, "Dot Line" },
    { Qt::DashDotLine, "Dash Dot Line" },
    { Qt::DashDotDotLine, "Dash Dot Dot Line" }
};


std::map<QString, DrawBoard::Mode> DrawBoard::stringToMode =
{
    { "Insert", DrawBoard::Mode::Insert },
    { "Edit", DrawBoard::Mode::Edit }
};

std::map<DrawBoard::Mode, QString> DrawBoard::modeToString =
{
    { DrawBoard::Mode::Insert, "Insert" },
    { DrawBoard::Mode::Edit, "Edit" }
};

std::map<QString, DrawBoard::InsertMode> DrawBoard::stringToInsertMode =
{
    { "Line", DrawBoard::InsertMode::Line },
    { "Rectangle", DrawBoard::InsertMode::Rectangle },
    { "Ellipse", DrawBoard::InsertMode::Ellipse }
};

QDataStream &operator<<(QDataStream &out, const QVector<Shape*> &vectorShape)
{
    for (Shape *shape : vectorShape)
    {
        shape->deselect();
        out << *shape;
    }
    return out;
}

QDataStream &operator>>(QDataStream &in, QVector<Shape*> &vectorShape)
{
    while (!in.atEnd()) {
        Shape *shape = nullptr;
        in >> *shape;
        if (shape != nullptr) vectorShape += shape;
    }
    return in;
}
