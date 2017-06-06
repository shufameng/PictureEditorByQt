#include "pegraphicsscene.h"
#include <QDebug>


PEGraphicsScene::PEGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    mSceneMode = NoShape;
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

    switch (mSceneMode) {
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
    switch (mSceneMode) {
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
        mCurRectItem->setRect(getDirectionalRect(mLButtonPressPos, event->scenePos()));
        break;

    case Shape_Ellipse:
        mCurEllipseItem->setRect(getDirectionalRect(mLButtonPressPos, event->scenePos()));
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

QRectF PEGraphicsScene::getDirectionalRect(const QPointF &startPos, const QPointF &endPos)
{
    QRectF r;

    if ((endPos.x() >= startPos.x()) && (endPos.y() >= startPos.y())) {
        r.setTopLeft(startPos);
        r.setBottomRight(endPos);

    } else if ((endPos.x() < startPos.x()) && (endPos.y() < startPos.y())) {
        r.setTopLeft(endPos);
        r.setBottomRight(startPos);

    } else if ((endPos.x() >= startPos.x()) && (endPos.y() < startPos.y())) {
        r.setLeft(startPos.x());
        r.setRight(endPos.x());
        r.setTop(endPos.y());
        r.setBottom(startPos.y());

    } else if ((endPos.x() < startPos.x()) && (endPos.y() >= startPos.y())) {
        r.setLeft(endPos.x());
        r.setRight(startPos.x());
        r.setTop(startPos.y());
        r.setBottom(endPos.y());

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
