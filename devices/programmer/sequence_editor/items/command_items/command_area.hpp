#ifndef GROUP_COMMAND_HPP
#define GROUP_COMMAND_HPP

#include <QtWidgets>
#include "../../coordinates.hpp"
#include "../../../synchrodevices/command_block/command_block.hpp"

//#include "command_type/base_command_icon.hpp"
//#include "command_type/pulse_command.hpp"

using namespace Coordinates;

class CommandArea : public QObject, public QGraphicsItem 
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    CommandArea(QGraphicsScene* scene, quint8 address, int x, int y, QObject * parent = nullptr);
    ~CommandArea();
    
    void setWidth(int delta_x);     // Изменнение ширины группы
    int getWidth();     // Получение ширины
    
    void setX(int x);   // Установка X
    int getX();         // Получение X

    void setPosition(int position);

    int getAddress();  // Получение номера управляемого устройста

    void removeThis();  // Удаление группы

    void updateThis();  // Обновление группы на графической сцене

    void setCommandBlock(BlockData* block_data);    // Добавить блок команд
    CommandBlock* getCommandBlock();
    BlockData* getBlockData();
    void removeCommandBlock();                      // Удалить блок команд
    
    void setState(bool new_state);
    bool getState();

    QByteArray buildCommand(); 

private:

    QRectF boundingRect() const;
    void paint(QPainter* ppainter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    
protected:

    QGraphicsScene* scene_;

    int address_;    // id устройства

    BlockData* block_data_ = nullptr;
    bool busy_ = false;

    // ------------------------------- Графические параметры
    
    int x_;     // X левый верхний угол айтема
    int y_;     // Y левый верхний угол айтема
    int width_ = MINIMAL_WEIGHT_GROUPCOMMAND;   // Ширина
    int height_ = HEIGHT_GROUPCOMMAND;  // Высота

    // ------------------------------- Управление

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    // virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    
    // virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    // virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    // virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

protected slots:

signals:
    Q_SIGNAL void selected(CommandArea* area);    // Сигнал при выборе области
    Q_SIGNAL void deleted();       // Сигнал при удалении области
};

#endif