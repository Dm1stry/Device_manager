#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <QObject>
#include "formatter/basecommandformatter.hpp"
#include "formatter/controlbyteformatter.hpp"
#include "formatter/requestformatter.hpp"
#include "connection/udpconnection.hpp"
#include "devices/base/basedevicewidget.hpp"

/*
Оператор - ядро приложения, он контроллирует обмен данными 
между физическими и виртуальными устройствами,
а также хранит подключение и управляет сохранением и загрузкой
виртуальных асинхронных устройств
*/

class BaseDeviceWidget;

class Operator : public QObject
{
Q_OBJECT
public:
    Operator(QObject * parent = nullptr);

    // Возвращает указатель на объект форматёра команд
    BaseCommandFormatter * getCommandFormatter() const;

    // Возвращает указатель на объект форматёра запросов
    BaseCommandFormatter * getRequestFormatter() const;

    // Возвращает указатель на объект подключения
    BaseConnection * getConnection() const;

    // Возвращает вектор указателей на все добавленные ранее устройства
    QVector<BaseDeviceWidget *> getDevices() const;
public slots:
    // Добавляет новое устройство
    void addDevice(BaseDeviceWidget * device);
private slots:
    // Посылает команду через подключение на физическое устройство
    void sendCommand(QByteArray command);

    // Посылает запрос через подключение на физическое устройство
    void sendRequest(QByteArray request);

    // Посылает данные без форматирования на физическое устройство
    void sendRaw(QByteArray data);

    //Передает полученные от физического устройства данные, программным устройствам
    void sendData(QByteArray data);

    /* Устанавливает объект, для форматирования данных 
    * (если nullptr, данные будут отправляться в том же виде,
    * в котором пришли от виртуального устройства) */
    void setCommandFormatter(BaseCommandFormatter * command_formatter);

    /* Устанавливает объект для форматирования данных запросов 
    * (если nullptr, данные будут отправляться в том же виде,
    * в котором пришли от виртуального устройства) */
    void setRequestFormatter(BaseCommandFormatter * request_formatter);

    /* Устанавливает объект, через который происходит обмен сообщениями
    * с физическим устройством (например через UDP) */
    void setConnection(BaseConnection * connection);

signals:
    // Сигнал о том, что было добавлено новое устойство
    Q_SIGNAL void newDevice(BaseDeviceWidget *);
    
    // Сигнал о том, что получены новые данные, передается устройствам
    Q_SIGNAL void newData(QByteArray);

    // Сигнал о том, что получена новая команда для физического устройства
    Q_SIGNAL void newCommand(QByteArray);

    // Сигнал о том, что получен новый запрос для физического устройства
    Q_SIGNAL void newRequest(QByteArray);

    // Сигнал о том, что полученs сырые данные для физического устройства
    Q_SIGNAL void newRaw(QByteArray);

    // Сигнал о том, что получена новое широковешательное сообщение для программных устройств
    Q_SIGNAL void newBroadcast(QString, QVector<double>);

private:
    BaseConnection * connection_;  // Указатель на объект подключения (хранит сокет, порты и адрес)
    BaseCommandFormatter * command_formatter_;  // Указатель на объект форматирования команд
    BaseCommandFormatter * request_formatter_; // Указатель на объект форматирования запросов
    QVector<BaseDeviceWidget *> devices_;  //Массив указателей на устройства
};
#endif