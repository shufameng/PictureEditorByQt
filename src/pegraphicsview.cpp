#include "pegraphicsview.h"
#include <QDebug>
#include <QScrollBar>

PEGraphicsView::PEGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
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
    }
}

void PEGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void PEGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

    QPointF p = mLButtonPressPos - event->pos();
    horizontalScrollBar()->setValue(horizontalScrollBar()->value() + p.x());
    verticalScrollBar()->setValue(verticalScrollBar()->value() + p.y());
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

    if (horizontalScrollBar()->maximum() <= 0 && verticalScrollBar()->maximum() <= 0) {
        setCursor(QCursor(Qt::ArrowCursor));
    } else {
        setCursor(QCursor(Qt::OpenHandCursor));
    }
}

void PEGraphicsView::zoomIn()
{
    scale(1.1, 1.1);
}

void PEGraphicsView::zoomOut()
{
    scale(0.9, 0.9);
}

void PEGraphicsView::showOriginalSize()
{
    resetMatrix();
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

