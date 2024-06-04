#include "device_axes.hpp"

Axes::Axes(QString name, quint8 address, int position, QObject* parent) :
    name_(name),
    address_(address),
    position_(position),
    QObject(parent)
{
    y_ = UP_OFFSET + position_*HEIGHT_ONE_LINE;
    this->setAcceptHoverEvents(true); 
    this->setFlags(QGraphicsItem::ItemIsSelectable);
}

Axes::~Axes()
{

}

QRectF Axes::boundingRect() const
{ 
    return QRectF(x_,y_,length_,HEIGHT_AXES);
}

void Axes::paint(QPainter* ppainter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    ppainter->setPen(QPen(Qt::black, 2));
    ppainter->drawLine(x_, y_ + HEIGHT_AXES, x_ + length_, y_ + HEIGHT_AXES);
    ppainter->drawLine(x_, y_, x_, y_ + HEIGHT_AXES);

    QFont font = ppainter->font();    // получаем шрифт
    font.setPixelSize(TEXT_FONT_SIZE_AXES);          // изменяем высоту шрифта
    ppainter->setFont(font);          // переустанавливаем шрифт

    ppainter->drawText(x_+TEXT_X_AXES,y_+TEXT_Y_AXES,name_);
    ppainter->restore();
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

// -------------------------------------------------------------- Методы

quint8 Axes::getAddress()
{
    return address_;
}

int Axes::getPosition()
{
    return position_;
}

void Axes::setPosition(int position)
{
    position_ = position;
    y_ = UP_OFFSET + position_*HEIGHT_ONE_LINE;
}

void Axes::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //emit clicked();
}

void Axes::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}