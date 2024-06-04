#ifndef BASE_EVENT_HPP
#define BASE_EVENT_HPP

#include <QtWidgets>
#include "../../coordinates.hpp"
using namespace Coordinates;

class BaseEvent : public QObject, public QGraphicsItem 
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    BaseEvent(QGraphicsScene* scene, int id, int x, int y, QObject * parent = nullptr);
    ~BaseEvent();

    virtual void setHeight(int numbers_timelines);  // Установка высоты айтема согластно колличеству таймлайнов
    
    virtual void setWidth(int delta_x);     // Изменнение ширины айтема
    virtual int getWidth();     // Получение ширины
    
    virtual void setX(int x);   // Установка X
    virtual int getX();         // Получение X

    virtual int getID();        // Получение id ивента

    virtual int getRight();     // Получение координат правой стороны айтема (для позиционирования следующих айтемов)

    virtual void removeThis();  // Удаление ивента

    virtual void updateThis();  // Обновление ивента на сцене

    virtual void addNewTimeline(quint8 address);    // Добавление таймлайна для нового устройства
    virtual void removeTimeline(quint8 address);    // Удаление таймлайна устройства

    virtual QVector<unsigned long> getTime();
private:

protected:

    QGraphicsScene* scene_;

    int id_;    // id ивента
    int device_number_ = 0;     // Колличество устройств

    // ------------------------------- Графические параметры
    
    int x_;             // X левый верхний угол айтема
    const int y_;             // Y левый верхний угол айтема
    int width_ = MINIMAL_WEIGHT_EVENT;   // Ширина
    int min_width_ = MINIMAL_WEIGHT_EVENT;
    int height_ = HEIGHT_HEADER_INTERVAL + HEIGHT_ONE_LINE;  // Высота
    
    bool resize_ = false;       // Происходит ли изменение размера
    bool selected_ = false;     // Выбран ли ивент
    int n_devise_selected = -1; // Номер выбранного устройства

    // ------------------------------- Управление

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

public slots:

    virtual QByteArray buildCommand();

protected slots:
    
    void closeButtonClicked();

signals:
    void widthChanged(int);     // Сигнал при изменении размера интервала
    void closeThis(int);        // Сигнал при удаления
    void isSelected(int);       // Сигнал при выборе ивента
    void addRight(int, int);         // Сигнал добавления ивента справа от выбранного
    void addLeft(int, int);          // Сигнал добавления ивента слева от выбранного
};

#endif