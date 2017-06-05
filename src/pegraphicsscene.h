#ifndef PEGRAPHICSSCENE_H
#define PEGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>

class PEGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    PEGraphicsScene(QObject *parent = 0);

    enum SceneMode {
        NORMAL_MODE = 0,
        ADD_RECT_MODE,
        ADD_ELLIPSE_MODE
    };

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QRectF getDirectionalRect(const QPointF &startPos, const QPointF &endPos);

public:
    bool openFile(const QString &filePath);

private:
    SceneMode       mSceneMode;

    QPointF                         mAddItemPoint;
    QGraphicsRectItem       *mCurRectItem;
    QGraphicsEllipseItem    *mCurEllipseItem;
    QPen                                mPen;
    QBrush                          mBrush;
    QGraphicsPixmapItem     *mBackgroundItem;
};

#endif // PEGRAPHICSSCENE_H
