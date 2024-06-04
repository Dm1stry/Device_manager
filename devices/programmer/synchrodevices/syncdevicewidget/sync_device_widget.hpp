#ifndef SYNC_DEVICE_WIDGET_HPP
#define SYNC_DEVICE_WIDGET_HPP

#include <QWidget>
#include <QtWidgets>

/*
Класс виджета, отображаемого в программаторе, для управления синхронным устройством. 
*/
class SyncDeviceWidget : public QFrame
{
Q_OBJECT
public:
    SyncDeviceWidget(QString name, quint8 address, QFrame* parent = nullptr);
    ~SyncDeviceWidget();

    void layoutSetup();         // Создание внешнего вида
    void connectionSetup();     // Настройка connect-ов

private:
    QString name_ = "Undefined";    // Название устройства
    quint8 address_ = 0x00;         // Адрес устройства

    QLabel* name_label_;
    QCheckBox* check_box_;
    //QPushButton* main_button_;
    QPushButton* settings_button_;

    bool add = false;    // Добавлен ли таймлайн

private slots:
    void checkBoxClicked(int);   // Отправление сигнала о добавлении и удалении таймлайна

signals:
    Q_SIGNAL void addDevice(QString, quint8);    // Сигнал добавления таймлайна устройства
    Q_SIGNAL void removeDevice(quint8); // Сигнал удаления таймлайна устройства
    Q_SIGNAL void settingDevice();      // Сигнал настройки устройства

protected:

};

#endif