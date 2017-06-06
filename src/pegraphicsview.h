#ifndef PEGRAPHICSVIEW_H
#define PEGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>

class PEGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    PEGraphicsView(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private slots:
    void onScorllBarRangeChanged(int min, int max);

public slots:
    void zoomIn();
    void zoomOut();
    void showOriginalSize();
    void showFitViewSize();
    void rotate90Clockwise();
    void rotate90AntiClockwise();
    void rotate180();

private:
    QPointF mLButtonPressPos;
};

#endif // PEGRAPHICSVIEW_H
