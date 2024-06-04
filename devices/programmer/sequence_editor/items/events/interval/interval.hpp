#ifndef INTERVAL_H
#define INTERVAL_H

#include <QtWidgets>
#include <QGraphicsSceneMouseEvent>
#include "../baseevent.hpp"
#include "../../command_items/command_area.hpp"
#include "../../device_axes.hpp"
#include "interval_header.hpp"
#include "../../../../../base/command.hpp"


class Interval : public BaseEvent
{
    Q_OBJECT 
public:
    Interval(QGraphicsScene* scene, Command* interval_command, int id, QVector<Axes*> devices, unsigned long t_interval = 100, int x = 0, int y = 0, QObject* parent = nullptr);
    ~Interval();

    void removeThis();    // Удаление интервала

    void setX(int x);   // Установка X

    void setWidth(int new_width);           // Установка ширины айтема

    void addNewTimeline(quint8 address);    // добавление группы команд для нового устройства
    void removeTimeline(quint8 address);    // удаление группы команд для устройства

private:

    // ------------------------------- Физические параметры
    
    Command* interval_command_ = nullptr;
    unsigned long t_interval_ = 100;

    // ------------------------------- Для виджетов в шапке интервала
    
    IntervalHeader* header_;                 // Виджет заголовка

    QGraphicsProxyWidget* proxyHeader_;      // Объект для отображения заголовка

    QTransform transformHeader_;             // Объект для перемещения заголовка
    
    int header_x, header_y;                      // Положение заголовка

    // ------------------------------- Группы
    
    QVector<CommandArea*> devices_;        // Вектор с группами команд

    // ------------------------------- Служебное

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* ppainter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    void headerSetup();

public slots:

    QByteArray buildCommand() override;

private slots:
    void setTimeInterval(unsigned long time);
    QVector<unsigned long> getTime();

    void selectGroupCommands(CommandArea* area);
    void addLeftInterval();
    void addRightInterval();

signals:
    Q_SIGNAL void selectGroupCommandsSignal(int id, CommandArea* area);
    Q_SIGNAL void deleteGroupCommandsSignal();
};

#endif