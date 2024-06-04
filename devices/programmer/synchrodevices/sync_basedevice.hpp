#ifndef BASE_SYNC_DEVICE_HPP
#define BASE_SYNC_DEVICE_HPP

#include <QtWidgets>
#include "syncdevicewidget/sync_device_widget.hpp"

#include "command_block/command_block.hpp"


/*
Класс виджета, отображаемого в программаторе, для управления синхронным устройством. 
*/
class BaseSyncDevice : public QWidget
{
Q_OBJECT
public:
    BaseSyncDevice(QString name, quint8 address, QListWidget* devices, QWidget* parent = nullptr);
    ~BaseSyncDevice();

    SyncDeviceWidget* getWidget();

    QListWidgetItem* getListWidgetItem();

    quint8 getAddress();

    void addCommandBlock(CommandBlock* command_block);
    CommandBlock* getCommandBlock(quint8 command_index);
    int getCommandBlockCount();

private:
    QString name_ = "Undefined";
    quint8 address_ = 0x00;

    SyncDeviceWidget* widget_;
    QListWidgetItem* list_widget_;

    QVector<CommandBlock*> command_blocks_;

public slots:

signals:
    Q_SIGNAL void selectDevice(quint8);

protected:

};

#endif