#include "udpconnection.hpp"

UDPConnection::UDPConnection(QObject * parent)
  : BaseConnection(parent)
{
    socket_ = new QUdpSocket(this);

    // Загрузка параметров, сохраненных в прошлой сессии
    setParameter(Parameter::DESTINATION_PORT, settings_.value(DESTINATION_PORT_SETTING, DEFAULT_DESTINATION_PORT).toString());
    setParameter(Parameter::DESTINATION_IP, settings_.value(DESTINATION_IP_SETTING, DEFAULT_DESTINATION_IP).toString());
    setParameter(Parameter::SOURCE_PORT, settings_.value(SOURCE_PORT_SETTING, DEFAULT_SOURCE_PORT).toString());
    setParameter(Parameter::SOURCE_IP, settings_.value(SOURCE_IP_SETTING, DEFAULT_SOURCE_IP).toString());

    connect(socket_, &QUdpSocket::readyRead, this, &UDPConnection::receiveData);
}

bool UDPConnection::setDestinationPort(qint16 destination_port)
{
    connected_port_ = destination_port;
    settings_.setValue(DESTINATION_PORT_SETTING, QVariant(connected_port_));
    settings_.sync();
    qDebug() << "New dest port:" << destination_port;
    return true;  //Возможна проверка валидности порта
    
}

bool UDPConnection::setDestinationIP(quint32 destination_ip4)
{
    return this->setDestinationIP(QHostAddress(destination_ip4));
}

bool UDPConnection::setDestinationIP(QHostAddress destination_address)
{
    connected_ip4_ = destination_address;
    settings_.setValue(DESTINATION_IP_SETTING, QVariant(connected_ip4_.toString()));
    settings_.sync();
    qDebug() << "New dest ip:" << destination_address;
    return true;  //Возможна проверка валидности адреса
}

bool UDPConnection::setSourceIP(QHostAddress source_address)
{
    source_ip4_ = source_address;
    startConnection();
    settings_.setValue(SOURCE_IP_SETTING, QVariant(source_ip4_.toString()));
    settings_.sync();
    qDebug() << "New src ip:" << source_address;
    return true;
}

bool UDPConnection::setSourcePort(qint16 source_port)
{
    source_port_ = source_port;
    startConnection();
    settings_.setValue(SOURCE_PORT_SETTING, QVariant(source_port_));
    qDebug() << "New src port:" << source_port;
    return true;
}

bool UDPConnection::startConnection()
{
    //Тут стоит добавить проверку, все ли значения установлены
    socket_->close();
    socket_->abort();
    bool result = socket_->bind(source_ip4_, source_port_);
    connect(socket_, &QUdpSocket::readyRead, this, &UDPConnection::receiveData);
    return result;
}

void UDPConnection::setParameter(int id, QVariant data)
{
    switch(id)
    {
        case Parameter::SOURCE_IP:
            setSourceIP(QHostAddress(data.toString()));
            break;

        case Parameter::SOURCE_PORT:
            setSourcePort(data.value<qint16>());
            break;

        case Parameter::DESTINATION_IP:
            setDestinationIP(QHostAddress(data.toString()));
            break;

        case Parameter::DESTINATION_PORT:
            setDestinationPort(data.value<qint16>());
            break;
    }
}

void UDPConnection::setParameter(int id, QString data)
{
    switch(id)
    {
        case Parameter::SOURCE_IP:
            setSourceIP(QHostAddress(data));
            break;

        case Parameter::SOURCE_PORT:
            setSourcePort(data.toUShort());
            break;

        case Parameter::DESTINATION_IP:
            setDestinationIP(QHostAddress(data));
            break;

        case Parameter::DESTINATION_PORT:
            setDestinationPort(data.toUShort());
            break;
    }
}

QVector<QByteArray> UDPConnection::collectData()
{
    QVector<QByteArray> data = received_data_;
    received_data_.clear();
    return data;
}

void UDPConnection::receiveData()
{
    while(socket_->hasPendingDatagrams())// Есть дейтаграмма для чтения
    {
        QNetworkDatagram datagram = socket_->receiveDatagram();

        if(datagram.isValid() && datagram.senderAddress() == connected_ip4_ && datagram.senderPort())
        {
            auto data = datagram.data();
            received_data_.push_back(data);
            emit newData(data);
        }
    }
    
}

bool UDPConnection::sendData(QByteArray data)
{
    qint64 send_bytes = socket_->writeDatagram(data, connected_ip4_, connected_port_);
    if(send_bytes != data.size())
    {
        return false;
    }
    return true;
}

BaseConnection* UDPConnection::clone()
{
    UDPConnection * connection = new UDPConnection(this);
    connection->setDestinationPort(this->connected_port_);
    connection->setSourcePort(this->source_port_);
    connection->setDestinationIP(this->connected_ip4_);
    connection->setSourceIP(this->source_ip4_);
    return connection;
}