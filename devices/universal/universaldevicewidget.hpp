#ifndef UNIVERSALDEVICEWIDGET_HPP
#define UNIVERSALDEVICEWIDGET_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTabWidget>

#include "devices/base/basedevicewidget.hpp"

/*
Виджет Универсального виртуального устройства.
Позволяет отправлять любые команды любым устройствам и получать ответы 
от всех физических асинхронных устройств
*/

class UniversalDeviceWidget : public BaseDeviceWidget
{
Q_OBJECT
public:
    UniversalDeviceWidget(QWidget * parent = nullptr);
    
    // ---------------------------------------------------
    // Реализация метода, обрабатывающего пришедшие данные
    void processData(QByteArray data) override final;
    void processBroadcast(QString command, QVector<double> arguments) override final;
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

private slots:
    //void updateHistory(QByteArray data);
    void sendCommand(QString message);
    void sendRequest();
    void sendRaw(QString message);
    void sendBroadcast(QString message);
    
private:
    //----------------- Внешний вид -----------------------------

    //Для удобства вся настройка графического интерфейса вынесена
    // в отдельный метод, раскрывающийся при компиляции
    inline void layoutSetup();
    
    quint8 address_;

    QLineEdit * phys_address_edit_;  // Поле изменения физического адреса устройства, которому будет адресована команда

    QPlainTextEdit * commanding_history_edit_;  // Поле, отображающее все исходящие и входящие сообщения
    QLineEdit * commanding_message_edit_;  // Поле ввода команды
    QLabel * commanding_message_prefix_;

    QPushButton * send_command_button_;  // Конопка отправки команды физическому устройству
    QPushButton * send_request_button_;
    QPushButton * send_raw_button_;

    QPlainTextEdit * broadcast_history_edit_;  // Поле, отображающее все исходящие и входящие сообщения
    QLineEdit * broadcast_message_edit_;  // Поле ввода широковещательного сообщения
 
    QPushButton  * send_broadcast_button_;

    QTabWidget * main_widget_;
    //----------------------------------------------------------
};

#endif