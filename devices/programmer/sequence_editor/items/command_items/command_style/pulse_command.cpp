#include "pulse_command.hpp"
#include <QDebug>

PulseCommand::PulseCommand(int x, int y, QObject* parent) :
    BaseCommandStyle(x, y, parent)
{  

    this->setCursor(Qt::PointingHandCursor);

    this->setAcceptHoverEvents(true); // Разрешение на hover event
    //this->setSelected(true);
    //this->setAcceptDrops(true);

    //this->setFlag(QGraphicsItem::ItemIsMovable);
    //this->setFlag(QGraphicsItem::ItemIsFocusable);
    //this->setFlag(ItemSendsGeometryChanges);
}

PulseCommand::~PulseCommand()
{

}

QRectF PulseCommand::boundingRect() const
{ 
    return QRectF(x_,y_,width_,height_);
}

void PulseCommand::paint(QPainter* ppainter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    /*
        Отрисовка интервала
    */
    ppainter->setPen(QPen(Qt::black, 2));

    ppainter->drawLine(x_+2, y_, x_+2, y_-height_);
    ppainter->drawLine(x_+2, y_-height_, x_+width_, y_-height_);
    ppainter->drawLine(x_+width_, y_-height_, x_+width_, y_);
        
    ppainter->restore();

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

// -------------------------------------------------------------- Методы

// void PulseCommand::removeThis()
// {
//     // scene_->removeItem(proxyHeader_);
//     // delete proxyEdit_; 
//     // scene_->removeItem(this);
//     // pWidget_ = nullptr;
//     // LineEdit_ = nullptr;
//     // scene_->removeItem(this);
//     // while(devices_.count())
//     // {
//     //     devices_.back()->removeThis();
//     //     delete devices_.back();
//     //     devices_.back() = nullptr;
//     //     devices_.pop_back();
//     // }
//     // scene_->update();
// }

// -------------------------------------------------------------- Слоты



// ---------------------------------------- Ивенты

/*
void Interval::mousePressEvent(QGraphicsSceneMouseEvent *event)
{   
    BaseEvent::mousePressEvent(event);
    if ((event->button() == Qt::RightButton) && (event->pos().x() >= x_) && (event->pos().x() <= x_+width_) && ((event->pos().x() >= y_))){
        QPoint temp = event->screenPos();
        this->showContextMenu(temp);
    }
}

void Interval::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        cMenu = new ContextMenu();
        cMenu->setVisible(true);

        qDebug() << "RightButton";
    }
}


void Interval::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(resize_){
        this->setWidth((event->pos().x()-x_));
        initial_x_ = (event->pos().x()-x_);
        emit widthChanged(id_);

        qDebug() << "move";
    }
}

void Interval::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "release";
    if(resize_){
        resize_ = false;
        scene_->removeItem(this);
        scene_->addItem(this);
    }
}

void Interval::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug()<<"hover enter";
}

void Interval::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug()<<"hover move";
    if(((event->pos().x()-x_) >= (width_-3)) && ((event->pos().x()-x_) <= (width_+2))){
        this->setCursor(Qt::SizeHorCursor);
    }
    else{
        //this->setCursor(Qt::ArrowCursor);
        this->setCursor(Qt::PointingHandCursor);
    }
}

void Interval::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug()<<"hover leave";
}
*/