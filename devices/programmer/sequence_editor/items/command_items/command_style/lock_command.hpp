#ifndef LOCK_COMMAND_H
#define LOCK_COMMAND_H

#include <QtWidgets>
#include <QGraphicsSceneMouseEvent>
#include "base_command_style.hpp"

class LockCommand : public BaseCommandStyle
{
    Q_OBJECT 
public:
    LockCommand(int x = 0, int y = 0, QObject* parent = nullptr);
    ~LockCommand();

    // void removeThis();    // Удаление

private:

    // ------------------------------- Физические параметры
    
    // ------------------------------- Служебное

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* ppainter, const QStyleOptionGraphicsItem* option, QWidget* widget);

protected:

    // virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    // void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    // void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    // void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    // void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    // void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    // void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private slots:

signals:

};

#endif