#include "command_area.hpp"

CommandArea::CommandArea(QGraphicsScene* scene, quint8 address, int x, int device_number_, QObject * parent):
  scene_(scene),
  address_(address),
  x_(x),
  QObject(parent)
{
    y_ = UP_OFFSET + (device_number_-1)*HEIGHT_ONE_LINE + HEIGHT_AXES-HEIGHT_GROUPCOMMAND;

    this->setZValue(2);
        
    this->setCursor(Qt::CrossCursor);

    this->setAcceptHoverEvents(true); // Разрешение на hover event
    //this->setFlags(QGraphicsItem::ItemIsMovable);
    this->setFlags(QGraphicsItem::ItemIsSelectable);
}

CommandArea::~CommandArea()
{
    
}

QRectF CommandArea::boundingRect() const
{ 
    return QRectF(x_,y_,width_,height_);
}

void CommandArea::paint(QPainter* ppainter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    /*
        Отрисовка группы
    */
    ppainter->setPen(QPen(Qt::gray, 0.5));
    //ppainter->setBrush(QBrush(Qt::gray));
    ppainter->drawRect(QRect(x_, y_, width_, height_));
    
    QFont font = ppainter->font();    // получаем шрифт
    font.setPixelSize(TEXT_FONT_SIZE_AXES);          // изменяем высоту шрифта
    ppainter->setFont(font);          // переустанавливаем шрифт

    ppainter->drawText(x_+TEXT_X_AXES,y_+TEXT_Y_AXES,QString::number(address_,16));

    ppainter->restore();

    
    QStyleOptionGraphicsItem op;

    if (option->state & QStyle::State_Selected)
        op.state = QStyle::State_None;

    if (option->state & QStyle::State_Selected) {
        qreal itemPenWidth = ppainter->pen().widthF();
        const qreal pad = itemPenWidth / 2;
        const qreal penWidth = 0;
                        // Border area color
        QColor color = QColor(Qt::blue);
                        // Draw a solid line
        // ppainter->setPen(QPen(color, penWidth, Qt::SolidLine));
        // ppainter->setBrush(Qt::NoBrush);
        // ppainter->drawRect(boundingRect().adjusted(pad, pad, -pad, -pad));
                        // Draw a broken line
        ppainter->setPen(QPen(color, 0, Qt::DashLine));
        ppainter->setBrush(Qt::NoBrush);
        ppainter->drawRect(boundingRect().adjusted(pad, pad, -pad, -pad));
    }
    
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

// ---------------------------------------- Методы

void CommandArea::setWidth(int new_width)
{
    if (new_width > MINIMAL_WEIGHT_GROUPCOMMAND){
        width_ = new_width;
        scene_->update();
    }
}

int CommandArea::getWidth()
{
    return width_;
}

void CommandArea::setX(int x)
{
    //this->setPos(x,y_);
    x_ = x;
    this->updateThis();
    if (block_data_ != nullptr)
    {
        block_data_->getCommandStyle()->setX(x_+2);
        scene_->removeItem(block_data_->getCommandStyle());
        scene_->addItem(block_data_->getCommandStyle());
    }
}

int CommandArea::getX()
{
    return x_;
}

void CommandArea::setPosition(int position)
{
    y_ = UP_OFFSET + (position-1)*HEIGHT_ONE_LINE + HEIGHT_AXES-HEIGHT_GROUPCOMMAND;
    this->updateThis();
    if (block_data_ != nullptr)
    {
        block_data_->getCommandStyle()->setY(y_+HEIGHT_GROUPCOMMAND);
        scene_->removeItem(block_data_->getCommandStyle());
        scene_->addItem(block_data_->getCommandStyle());
    }
}

int CommandArea::getAddress()
{
    return address_;
}

void CommandArea::removeThis()
{
    if (this->QGraphicsItem::isSelected())  // ------------------------------------------aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaadddddddddddddddddddddddddddddddddddddddddddddddddd
    {
        emit deleted(); 
    }
    if (block_data_ != nullptr)
    {
        scene_->removeItem(block_data_->getCommandStyle());
        scene_->update();
        delete block_data_;
        block_data_ = nullptr;
    }
    scene_->removeItem(this);
}

void CommandArea::updateThis()
{
    if (block_data_ != nullptr)
    {
        scene_->removeItem(block_data_->getCommandStyle());
        scene_->addItem(block_data_->getCommandStyle());
    }
    
    scene_->removeItem(this);
    scene_->addItem(this);
}

void CommandArea::setCommandBlock(BlockData* block_data)
{
    if (block_data_ == nullptr)
    {
        block_data_ = block_data;
        block_data_->getCommandStyle()->setX(x_+2);
        block_data_->getCommandStyle()->setY(y_+HEIGHT_GROUPCOMMAND);
        scene_->addItem(block_data_->getCommandStyle());
        scene_->update();
        busy_ = true;
    }
}

CommandBlock* CommandArea::getCommandBlock()
{
    return (CommandBlock*)block_data_->parent();
}

BlockData* CommandArea::getBlockData()
{
    return block_data_;
}

void CommandArea::removeCommandBlock()
{
    if (block_data_ != nullptr)
    {
        scene_->removeItem(block_data_->getCommandStyle());
        scene_->update();
        delete block_data_;
        block_data_ = nullptr;
        busy_ = false;
    }
}

void CommandArea::setState(bool new_state)
{
    busy_ = new_state;
}

bool CommandArea::getState()
{
    return busy_;
}

QByteArray CommandArea::buildCommand()
{
    QByteArray command = QByteArray();
    if (block_data_ != nullptr)
    {
        // qDebug() << "Импульс";
        command.append(block_data_->buildCommand());
    }
    return command;
}

// ---------------------------------------- Слоты



// ---------------------------------------- Ивенты

void CommandArea::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    scene_->clearSelection();
    this->setSelected(true);
    emit selected(this);
}

void CommandArea::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

/*
void BaseEvent::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(resize_){
        this->setWidth((event->pos().x()-x_));
        emit widthChanged(id_);
        //qDebug() << "move";
    }
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

*/