#ifndef PEGRAPHICSSCENE_H
#define PEGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPathItem>

class PEGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    PEGraphicsScene(QObject *parent = 0);

    enum ToolShape {
        NoShape = 0,
        Shape_HorLine,
        Shape_VerLine,
        Shape_Line,
        Shape_Rect,
        Shape_Ellipse,
        Shape_Path
    };

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public:
    static QRectF getRectByPoints(const QPointF &p1, const QPointF &p2);
    static QLineF getHorizontalLine(const QPointF &startPos, const QPointF &endPos);
    static QLineF getVerticalLine(const QPointF &startPos, const QPointF &endPos);

public slots:
    bool openFile(const QString &filePath);
    void setPenWidth(const int w)                   { mPen.setWidth(w); }
    void setPenColor(const QColor &color)       { mPen.setColor(color); }
    QPen pen()                                                  { return mPen; }
    void setBrushColor(const QColor &color)     { mBrush.setColor(color); }
    QBrush brush()                                          { return mBrush; }
    ToolShape toolShape()                           { return mToolShape; }
    void setToolShape(ToolShape shape)       { mToolShape = shape; }

private:
     ToolShape       mToolShape;

    QPointF                         mLButtonPressPos;
    QGraphicsLineItem       *mCurLineItem;
    QGraphicsRectItem       *mCurRectItem;
    QGraphicsEllipseItem    *mCurEllipseItem;
    QGraphicsPathItem       *mCurPathItem;
    QPen                                mPen;
    QBrush                          mBrush;
    QGraphicsPixmapItem     *mBackgroundItem;
};

#endif // PEGRAPHICSSCENE_H
