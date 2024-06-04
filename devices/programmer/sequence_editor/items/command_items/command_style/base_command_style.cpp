#include "base_command_style.hpp"

BaseCommandStyle::BaseCommandStyle(int x, int y, QObject * parent):
  x_(x),
  y_(y),
  QObject(parent)
{
  this->setAcceptHoverEvents(true); // Разрешение на hover event
  this->setFlags(QGraphicsItem::ItemIsMovable);
}

BaseCommandStyle::~BaseCommandStyle()
{
    
}

void BaseCommandStyle::setX(int x)
{
    x_ = x;
}

int BaseCommandStyle::getX()
{
    return x_;
}

void BaseCommandStyle::setY(int y)
{
    y_ = y;
}

int BaseCommandStyle::getY()
{
    return y_;
}

void BaseCommandStyle::updateThis()
{

}