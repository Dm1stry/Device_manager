#ifndef UDP_CONNECTION_HPP
#define UDP_CONNECTION_HPP

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QVector>
#include <QSettings>
#include <memory>
#include "baseconnection.hpp"


const quint16 DEFAULT_DESTINATION_PORT = 8080;
const quint16 DEFAULT_SOURCE_PORT = 8080;
const QString DEFAULT_DESTINATION_IP = "192.168.0.2";
const QString DEFAULT_SOURCE_IP = "192.168.0.3";

// Расположение переменных в файле настроек
const QString DESTINATION_PORT_SETTING = "udpconnection/destination_port";
const QString SOURCE_PORT_SETTING = "udpconnection/source_port";
const QString DESTINATION_IP_SETTING = "udpconnection/destination_ip";
const QString SOURCE_IP_SETTING = "udpconnection/source_ip";


class UDPConnection : public BaseConnection
{
Q_OBJECT
public:
    UDPConnection(QObject * parent = nullptr);  //Создает сокет, но не биндит его
    bool setDestinationPort(qint16 destination_port);
    bool setDestinationIP(quint32 destination_ip4);
    bool setDestinationIP(QHostAddress destination_address);
    bool setSourceIP(QHostAddress source_address);
    bool setSourcePort(qint16 source_port);
    bool startConnection() override final;  //Начать подключение
    virtual void setParameter(int id, QVariant data) override final;  // Вместо id подставить значения enum Parameter
    virtual void setParameter(int id, QString data) override final;  // Вместо id подставить значения enum Parameter
    virtual QVector<QByteArray> collectData() override final;  // Получает всё, что успело придти через соединение
    virtual bool sendData(QByteArray data) override final;  //Посылает данные через соединение
    virtual BaseConnection* clone() override final;
    
    enum Parameter
    {
        SOURCE_IP = 0,
        SOURCE_PORT,
        DESTINATION_IP,
        DESTINATION_PORT,
        size  // Размер перечисления
    };

private slots:  
    void receiveData();  // Слот, чтобы копировать всё что приходило на сокет и сохранять в буффере
    
private:
    QUdpSocket * socket_;  //Сокет
    QHostAddress source_ip4_;  //IPv4 компьютера, на котором работает программа
    QHostAddress connected_ip4_;  //IPv4 устройства, куда мы отправляем
    quint16 connected_port_;  //Порт на устройстве, куда мы отправляем
    quint16 source_port_;  //Порт на котором мы слушаем

    QSettings settings_;
/* Реализовано в предке:
signals:
    void newData(QByteArray);  //Сигнал о том, что появились новые данные
protected:
    QVector<QByteArray> received_data_;  //Буффер полученных данных
*/
};
#endif