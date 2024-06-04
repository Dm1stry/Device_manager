#ifndef DEVICE_EDITOR_HPP
#define DEVICE_EDITOR_HPP

#include <QtWidgets>
#include "commands_editor/command_block_editor.hpp"

class DeviceEditor : public QWidget
{
Q_OBJECT
public:
    DeviceEditor(QWidget* parent = nullptr);
    ~DeviceEditor();

private:
    //----------------- Внешний вид -----------------------------
    //Для удобства вся настройка графического интерфейса вынесена
    // в отдельный метод, раскрывающийся при компиляции
    void layoutSetup();
    void setConnections();

    QListWidget* block_list_;

    QVector<CommandBlockEditor*> blocks_;

    //-----------------------------------------------------------

public slots:
    void updateDeviceList();
};

#endif