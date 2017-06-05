#ifndef PEGRAPHICSVIEW_H
#define PEGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

class PEGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    PEGraphicsView(QWidget *parent = 0);

protected:
//    void mousePressEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
};

#endif // PEGRAPHICSVIEW_H
