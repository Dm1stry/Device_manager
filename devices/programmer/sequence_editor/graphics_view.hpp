#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

class MyGraphicsView: public QGraphicsView {
    Q_OBJECT
private:
    QGraphicsScene* scene_;

public:
    MyGraphicsView(QGraphicsScene* pScene, QWidget* pwgt = 0);
    void wheelEvent(QWheelEvent *event);
    // void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    Q_SIGNAL void clickedOut();
};
#endif