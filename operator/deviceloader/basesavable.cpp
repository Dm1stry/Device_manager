#include "basesavable.hpp"

void BaseSavable::addChild(BaseSavable* child)
{
    children_.push_back(child);
}

QVector<BaseSavable*> BaseSavable::getChildren() const
{
    return children_;
}