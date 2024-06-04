#include "graphics_view.hpp"
#include <QDebug>

MyGraphicsView::MyGraphicsView(QGraphicsScene* scene, QWidget* pwgt):
    QGraphicsView(scene, pwgt)
{
    scene_ = scene;
    //this->setContextMenuPolicy(Qt::CustomContextMenu);
}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    scene_->update();
    QGraphicsView::wheelEvent(event);
}

// void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
// {
//     QGraphicsView::mouseMoveEvent(event);
// }

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    if (QGraphicsItem *item = itemAt(event->pos()))
    {
        // qDebug() << "You clicked on item";
    } 
    else 
    {
        // qDebug() << "You didn't click on an item.";
        emit clickedOut();
    }
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}
