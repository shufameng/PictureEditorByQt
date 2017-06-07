#include "pegraphicsscene.h"
#include <QDebug>


PEGraphicsScene::PEGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    mToolShape = NoShape;
    mCurLineItem = NULL;
    mCurRectItem = NULL;
    mCurEllipseItem = NULL;
    mCurPathItem = NULL;
    mBackgroundItem = NULL;
}

void PEGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (Qt::LeftButton != event->button())
        return;
    if (!mBackgroundItem)
        return;

    switch (mToolShape) {
    case NoShape:
        break;

    case Shape_HorLine:
    case Shape_VerLine:
    case Shape_Line:
        mLButtonPressPos = event->scenePos();
        mCurLineItem = addLine(QLineF(event->scenePos(), event->scenePos()), mPen);
        mCurLineItem->setParentItem(mBackgroundItem);
        break;

    case Shape_Rect:
        mLButtonPressPos = event->scenePos();
        mCurRectItem = addRect(QRectF(event->scenePos(), event->scenePos()), mPen, mBrush);
        mCurRectItem->setParentItem(mBackgroundItem);
        break;

    case Shape_Ellipse:
        mLButtonPressPos = event->scenePos();
        mCurEllipseItem = addEllipse(QRectF(event->scenePos(), event->scenePos()), mPen, mBrush);
        mCurEllipseItem->setParentItem(mBackgroundItem);
        break;

    case Shape_Path:
    {
        mCurPathItem = new QGraphicsPathItem;
        mCurPathItem->setPen(mPen);
        mCurPathItem->setBrush(mBrush);
        mCurPathItem->setPath(QPainterPath(event->scenePos()));
        mCurPathItem->setParentItem(mBackgroundItem);
    }
        break;

    default:
        break;
    }
}

void PEGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    switch (mToolShape) {
    case NoShape:
        break;

    case Shape_HorLine:
        mCurLineItem->setLine(getHorizontalLine(mLButtonPressPos, event->scenePos()));
        break;

    case Shape_VerLine:
        mCurLineItem->setLine(getVerticalLine(mLButtonPressPos, event->scenePos()));
        break;

    case Shape_Line:
        mCurLineItem->setLine(QLineF(mLButtonPressPos, event->scenePos()));
        break;

    case Shape_Rect:
        mCurRectItem->setRect(getRectByPoints(mLButtonPressPos, event->scenePos()));
        break;

    case Shape_Ellipse:
        mCurEllipseItem->setRect(getRectByPoints(mLButtonPressPos, event->scenePos()));
        break;

    case Shape_Path:
    {
        QPainterPath path = mCurPathItem->path();
        path.lineTo(event->scenePos());
        mCurPathItem->setPath(path);
    }
        break;

    default:
        break;
    }
}

void PEGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (Qt::LeftButton != event->button())
        return;
}

QRectF PEGraphicsScene::getRectByPoints(const QPointF &p1, const QPointF &p2)
{
    QRectF r;

    if ((p2.x() >= p1.x()) && (p2.y() >= p1.y())) {
        r.setTopLeft(p1);
        r.setBottomRight(p2);

    } else if ((p2.x() < p1.x()) && (p2.y() < p1.y())) {
        r.setTopLeft(p2);
        r.setBottomRight(p1);

    } else if ((p2.x() >= p1.x()) && (p2.y() < p1.y())) {
        r.setLeft(p1.x());
        r.setRight(p2.x());
        r.setTop(p2.y());
        r.setBottom(p1.y());

    } else if ((p2.x() < p1.x()) && (p2.y() >= p1.y())) {
        r.setLeft(p2.x());
        r.setRight(p1.x());
        r.setTop(p1.y());
        r.setBottom(p2.y());

    }

    return r;
}

QLineF PEGraphicsScene::getHorizontalLine(const QPointF &startPos, const QPointF &endPos)
{
    QLineF line;
    line.setP1(startPos);
    line.setP2(QPointF(endPos.x(), startPos.y()));
    return line;
}

QLineF PEGraphicsScene::getVerticalLine(const QPointF &startPos, const QPointF &endPos)
{
    QLineF line;
    line.setP1(startPos);
    line.setP2(QPointF(startPos.x(), endPos.y()));
    return line;
}

bool PEGraphicsScene::openFile(const QString &filePath)
{
    clear();
    setSceneRect(QRectF());

    QPixmap pixmap;
    pixmap.load(filePath);
    if (pixmap.isNull())
        return false;

    mBackgroundItem = addPixmap(pixmap);

    return true;
}
