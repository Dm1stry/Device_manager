#include "sync_basedevice.hpp"

BaseSyncDevice::BaseSyncDevice(QString name, quint8 address, QListWidget* devices, QWidget* parent):
name_(name),
address_(address),
QWidget(parent)
{
    widget_ = new SyncDeviceWidget(name, address);
    list_widget_ = new QListWidgetItem(devices);
    list_widget_->setSizeHint(QSize(80, 40));
    list_widget_->setFlags(list_widget_->flags() & ~Qt::ItemIsSelectable);

    widget_->setParent(this);
    devices->setItemWidget(list_widget_, widget_);
}

BaseSyncDevice::~BaseSyncDevice()
{

}

SyncDeviceWidget* BaseSyncDevice::getWidget()
{
    return widget_;
}

QListWidgetItem* BaseSyncDevice::getListWidgetItem()
{
    return list_widget_;
}

quint8 BaseSyncDevice::getAddress()
{
    return address_;
}

void BaseSyncDevice::addCommandBlock(CommandBlock* command_block)
{
    command_blocks_.append(command_block);
}

CommandBlock* BaseSyncDevice::getCommandBlock(quint8 command_index)
{
    return command_blocks_[command_index];
}

int BaseSyncDevice::getCommandBlockCount()
{
    return command_blocks_.size();
}