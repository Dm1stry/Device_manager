#ifndef PROGRAMMER_DEVICE_WIDGET_HPP
#define PROGRAMMER_DEVICE_WIDGET_HPP

#include <QtWidgets>
#include "sequence_editor/graphics.hpp"
#include "devices/base/basedevicewidget.hpp"
#include "synchrodevices/sync_basedevice.hpp"
#include "device_editor/device_editor.hpp"
#include "device_editor/editor_size.hpp"
using namespace EditorSize;
#include "synchrodevices/command_block/command_settings/block_settings_widget.hpp"
#include <QThread>


class ProgrammerDeviceWidget : public BaseDeviceWidget
{
Q_OBJECT
public:
    ProgrammerDeviceWidget(QWidget * parent = nullptr);

	// ---------------------------------------------------
    // Реализация метода, обрабатывающего пришедшие данные
    void processData(QByteArray data);
    // -------------------------------  

    // -------------------------------------------------------------------------------------------------------------
    // BaseSavable методы, позволяющие получить данные для сохранения класса и 
    // восстановить состояние класса из сохраненных данных, 
    // необходимо для функционирования DeviceLoader
    
    // Возвращает данные о состоянии в виде вектора состояния
    json getStateToSave();
    // Восстанавливает состояние класса из вектора состояния
    bool restoreState(json state);
    // ------------------------------------------

private:
    //----------------- Внешний вид -----------------------------
    //Для удобства вся настройка графического интерфейса вынесена
    // в отдельный метод, раскрывающийся при компиляции
    void layoutSetup();
    void setConnections();
    void setDevice();
    //-----------------------------------------------------------

    Command* programmer_;
    quint8 programmer_state_ = 0; // Состояние программатора: 0 - stop, 1 - start

    Graphics* graph_;

    QPushButton* button_add_interval_;
    QPushButton* button_add_loop_;
    QPushButton* button_add_macros_;

    QComboBox* combobox_select_block_;
    QPushButton* button_add_command_;
    QPushButton* button_remove_command_;

    QPushButton* button_start_sequence_;
    QPushButton* button_stop_sequence_;

    QLineEdit* test_; // Временно для тестов
    QPushButton* test_button_; // Временно для тестов

    QVector<BaseSyncDevice*> devices_;
    QListWidget* list_devices_;

    CommandArea* selected_command_ = nullptr;

    BlockSettings* command_settings_;

public slots:
//  void setAddress(quint8 address);  //Устанавливает значение адреса данного устройства на шине
//  void setName(QString name);
//  void processData(QByteArray data);  //Обрабатывает данные, пришедшие от класса опреатора, в том числе проверяет принадлежность

    void selectGroupCommands(int id, CommandArea* area);
    void deleteGroupCommands();

    void addCommandToArea();
    void removeCommandFromArea();
    void updateBlockSettings();

    void updateCommandBlockArguments(QString command_name, QString argument_name, double value);

    void startSequence();
    void stopSequence();

    void settingsDevice();

};

#endif