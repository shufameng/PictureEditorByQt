#include "pegraphicsscene.h"
#include <QDebug>


PEGraphicsScene::PEGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    mSceneMode = ADD_ELLIPSE_MODE;

    mCurRectItem = NULL;
    mCurEllipseItem = NULL;
    mBackgroundItem = NULL;
}

void PEGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "PEGraphicsScene::mousePressEvent" << event->scenePos();
    qDebug() << "item count:" << items().size();

    if (Qt::LeftButton != event->button())
        return;

    switch (mSceneMode) {
    case NORMAL_MODE:

        break;
    case ADD_RECT_MODE:
    {
        mAddItemPoint = event->scenePos();
        QRectF r(event->scenePos(), event->scenePos());
        mCurRectItem = new QGraphicsRectItem(mBackgroundItem);
        mCurRectItem->setRect(r);
    }
        break;
    case ADD_ELLIPSE_MODE:
    {
        mAddItemPoint = event->scenePos();
        QRectF r(event->scenePos(), event->scenePos());
        mCurEllipseItem = new QGraphicsEllipseItem(mBackgroundItem);
        mCurEllipseItem->setRect(r);
    }
        break;
    default:
        break;
    }
}

void PEGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "PEGraphicsScene::mouseMoveEvent";

    switch (mSceneMode) {
    case NORMAL_MODE:
    {
        qDebug() << "MORMAL_MODE";
    }

        break;
    case ADD_RECT_MODE:
    {
        QRectF r = getDirectionalRect(mAddItemPoint, event->scenePos());
        mCurRectItem->setRect(r);
    }
        break;
    case ADD_ELLIPSE_MODE:
    {
        QRectF r = getDirectionalRect(mAddItemPoint, event->scenePos());
        mCurEllipseItem->setRect(r);
    }
        break;
    default:
        break;
    }
}

void PEGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "PEGraphicsScene::mouseReleaseEvent";

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
