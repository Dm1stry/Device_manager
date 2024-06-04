#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QtWidgets>
#include "../synchrodevices/sync_basedevice.hpp"
#include "items/device_axes.hpp"
#include "graphics_view.hpp"
#include "items/events/interval/interval.hpp"
#include "coordinates.hpp"
using namespace Coordinates;
#include "../../base/command.hpp"

class Graphics : public QWidget {
    Q_OBJECT 
public:
    QGraphicsScene* scene_;
    QGraphicsView* view_;

    Graphics(QWidget* parent = nullptr);

    void debugEvents();

    void setDevices(QVector<BaseSyncDevice*> devices);
    void reselectGroupComands(int id, quint8 address);

private:
    QVector<BaseSyncDevice*> devices_;

    int events_number_ = 0;     // Количество ивентов в одном таймлайне (интервалы, циклы)
    int total_number_ = 0;      // Для id

    QVector<Axes*> timelines_;  // Вектор с таймлайнами
    QVector<BaseEvent*> events_;    // Вектор с ивентами

    Command* interval_command_;

public slots:
    void addNewTimeline(QString name = "", quint8 address = 0x00); // Добавление нового таймлайна
    void removeTimeline(quint8 address = 0x00);      // Удаление последнего таймлайна 

    void addNewInterval();              // Добавление интервала в конец
    void addLeftInterval(int id, int mode);       // Добавить интервал слева от выбранного
    void addRightInterval(int id, int mode);      // Добавить интервал справа от выбранного
    void removeInterval(int id);        // Удаление интервала

    void moveEvents(int id);            // Смещение интервалов при изменении размеров 

    QByteArray buildSequence();
    QVector<unsigned long> getTimeIntervals();

signals:
    Q_SIGNAL void selectGroupCommandsSignal(int id, CommandArea* area);
    Q_SIGNAL void deleteGroupCommandsSignal();
};
#endif