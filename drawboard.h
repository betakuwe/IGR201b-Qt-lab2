#ifndef DRAWBOARD_H
#define DRAWBOARD_H

#include <QWidget>
#include <QPen>

class Shape;

class DrawBoard : public QWidget
{
    Q_OBJECT
public:
    enum Mode { Insert, Edit };
    enum InsertMode { Line, Rectangle, Ellipse };

    explicit DrawBoard(QWidget *parent = nullptr);
    void pickColor(const QColor color);
    void setWidth(const int width);
    void setStyle(const QString &styleString);
    void setMode(const QString &modeString);
    void setInsertMode(const QString &insertModeString);
    QVector<Shape*> getShapes() const;
    void setShapes(QVector<Shape*> shapes);

    static std::map<QString, Qt::PenStyle> stringToPenStyle;
    static std::map<Qt::PenStyle, QString> penStyleToString;
    static std::map<QString, Mode> stringToMode;
    static std::map<Mode, QString> modeToString;
    static std::map<QString, InsertMode> stringToInsertMode;

private:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void myDrawShape(const QPointF &endPoint);

    void selectShape(const QPointF &selectedPoint);
    void deselectShape();
    void moveShape(const QPointF &endPoint);
    void applyStyle();

    QVector<std::pair<QPen, QPainterPath>> shapes;
    QPointF lastPoint;
    std::pair<QPen, QPainterPath> currentShape;
    bool drawing;

    Mode mode;
    InsertMode insertMode;

    int selectedShapeIndex;
    bool dragging;
    QPointF lastTranslationPoint;

    QVector<Shape*> myShapes;
    Shape *myCurrentShape;
    QPen pen;

signals:
    void shapeSelected(const Shape &shape);
};

QDataStream &operator<<(QDataStream &out, const QVector<Shape*> &vectorShape);
QDataStream &operator>>(QDataStream &in, QVector<Shape*> &vectorShape);

#endif // DRAWBOARD_H
