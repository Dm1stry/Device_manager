#include "baseevent.hpp"

BaseEvent::BaseEvent(QGraphicsScene* scene, int id, int x, int y, QObject * parent):
  scene_(scene),
  id_(id),
  x_(x+LEFT_OFFSET),
  y_(y+(UP_OFFSET - OFFSET_BETWEEN - HEIGHT_HEADER_INTERVAL)),
  QObject(parent)
{
  this->setAcceptHoverEvents(true); // Разрешение на hover event
  this->setFlags(QGraphicsItem::ItemIsMovable);
  //this->setSelected(true);
  //this->setFlags(QGraphicsItem::ItemIsSelectable);
}

BaseEvent::~BaseEvent()
{
    
}

// ---------------------------------------- Методы

void BaseEvent::setHeight(int device_number)
{
    height_ = HEIGHT_HEADER_INTERVAL + HEIGHT_ONE_LINE*(device_number);
    
    device_number_ = device_number;
    this->updateThis();
    scene_->update();
}

void BaseEvent::setWidth(int new_width)
{
    if (new_width > MINIMAL_WEIGHT_EVENT){
        width_ = new_width;
        scene_->update();
    }
}

int BaseEvent::getWidth()
{
    return width_;
}

void BaseEvent::setX(int x)
{
    //this->setPos(x,y_);
    x_ = x;
    this->updateThis();
    scene_->update();
}

int BaseEvent::getX()
{
    return x_;
}

int BaseEvent::getID()
{
    return id_;
}

int BaseEvent::getRight()
{
    return x_+width_;
}

void BaseEvent::removeThis()
{

}

void BaseEvent::updateThis()
{
    scene_->removeItem(this);
    qDebug() << "Hello";
    scene_->addItem(this);
}

void BaseEvent::addNewTimeline(quint8 address)
{

}

void BaseEvent::removeTimeline(quint8 address)
{

}

QVector<unsigned long> BaseEvent::getTime()
{
    return QVector<unsigned long>();
}
// ---------------------------------------- Слоты

void BaseEvent::closeButtonClicked()
{
    emit closeThis(id_);
}

QByteArray BaseEvent::buildCommand()
{
    return QByteArray();
}

// ---------------------------------------- Ивенты

void BaseEvent::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    
    if(((event->pos().x()-x_) >= (width_-3)) && ((event->pos().x()-x_) <= (width_+2))){
        resize_ = true;
        //qDebug() << "pressed" << event->pos().x();
    }

    if (event->button() == Qt::MouseButton::LeftButton) {
        this->setSelected(true);
        qDebug() << "Selected";
    }
    //qDebug() << "pressed" << event->pos().x();
}

void BaseEvent::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(resize_){
        this->setWidth((event->pos().x()-x_));
        emit widthChanged(id_);
        //qDebug() << "move";
    }
}

void BaseEvent::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(resize_){
        resize_ = false;
        this->updateThis();
    }
    //qDebug() << "release";
}

void BaseEvent::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //qDebug()<<"hover enter";
}

void BaseEvent::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(((event->pos().x()-x_) >= (width_-3)) && ((event->pos().x()-x_) <= (width_+2))){
        this->setCursor(Qt::SizeHorCursor);
    }
    else{
        //this->setCursor(Qt::ArrowCursor);
        this->setCursor(Qt::PointingHandCursor);
    }
    //qDebug()<<"hover move";
}

void BaseEvent::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    //qDebug()<<"hover leave";
}