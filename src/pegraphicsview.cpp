#include "pegraphicsview.h"
#include <QDebug>
#include <QScrollBar>
#include "pegraphicsscene.h"

PEGraphicsView::PEGraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    mZoomRate(1.0)
{
    connect(horizontalScrollBar(), SIGNAL(rangeChanged(int,int)),
            this, SLOT(onScorllBarRangeChanged(int,int)));
    connect(verticalScrollBar(), SIGNAL(rangeChanged(int,int)),
            this, SLOT(onScorllBarRangeChanged(int,int)));
}

void PEGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    if (event->button() == Qt::LeftButton) {
        mLButtonPressPos = event->pos();
        mViewCenterAtScene = mapToScene(viewport()->rect().center());
    }
}

void PEGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void PEGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    QPointF point = event->pos() - mLButtonPressPos;
    centerOn(mViewCenterAtScene - point/mZoomRate);
}

void PEGraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() < 0) {
        zoomOut();
    } else {
        zoomIn();
    }
}

void PEGraphicsView::onScorllBarRangeChanged(int min, int max)
{
    Q_UNUSED(min);
    Q_UNUSED(max);

    PEGraphicsScene *pScene = dynamic_cast<PEGraphicsScene*>(scene());
    if (pScene) {
        if (PEGraphicsScene::NoShape == pScene->toolShape()) {
            if (horizontalScrollBar()->maximum() <= 0 && verticalScrollBar()->maximum() <= 0) {
                setCursor(QCursor(Qt::ArrowCursor));
            } else {
                setCursor(QCursor(Qt::OpenHandCursor));
            }
        } else {
            setCursor(QCursor(Qt::ArrowCursor));
        }
    }
}

void PEGraphicsView::zoomIn()
{
    qreal rate = 1.1;
    scale(rate, rate);
    mZoomRate *= rate;
}

void PEGraphicsView::zoomOut()
{
    qreal rate = 1.0/1.1;
    scale(rate, rate);
    mZoomRate *= rate;
}

void PEGraphicsView::showOriginalSize()
{
    resetMatrix();
    mZoomRate = 1.0;
}

void PEGraphicsView::showFitViewSize()
{
    QSizeF viewSize = viewport()->rect().size();
    QSizeF sceneSize = scene()->sceneRect().size();

    if (viewSize.width() / viewSize.height() >= sceneSize.width() / sceneSize.height()) {
        resetMatrix();
        scale(viewSize.height() / sceneSize.height(), viewSize.height() / sceneSize.height());
    } else {
        resetMatrix();
        scale(viewSize.width() / sceneSize.width(), viewSize.width() / sceneSize.width());
    }

    mZoomRate = viewSize.width() / sceneSize.width();
}

void PEGraphicsView::rotate90Clockwise()
{
    rotate(90);
}

void PEGraphicsView::rotate90AntiClockwise()
{
    rotate(-90);
}

void PEGraphicsView::rotate180()
{
    rotate(180);
}

QSize PEGraphicsView::getViewEntireSize()
{
    QSize s = viewport()->size();
    s.setWidth(s.width() + horizontalScrollBar()->maximum());
    s.setHeight(s.height() + verticalScrollBar()->maximum());
    return s;
}

