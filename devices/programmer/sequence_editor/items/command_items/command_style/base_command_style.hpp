#ifndef BASE_COMMAND_ICON_HPP
#define BASE_COMMAND_ICON_HPP

#include <QtWidgets>

class BaseCommandStyle : public QObject, public QGraphicsItem 
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    BaseCommandStyle(int x, int y, QObject * parent = nullptr);
    ~BaseCommandStyle();

    
    virtual void setX(int x);   // Установка X
    virtual int getX();         // Получение X
    virtual void setY(int y);   // Установка Y
    virtual int getY();         // Получение Y

    virtual void updateThis();  // Обновление ивента на сцене

private:

protected:

    // ------------------------------- Графические параметры

    int x_;             // X левый верхний угол айтема
    int y_;             // Y левый верхний угол айтема
    int width_ = 30;      // Ширина
    int height_ = 50;   // Высота

    // ------------------------------- Управление

    // virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    // virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    // virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    
    // virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    // virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    // virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

protected slots:
    
    //void closeButtonClicked();

signals:
    void closeThis(int);        // Сигнал при удаления
    void isSelected(int);       // Сигнал при выборе ивента
};

#endif