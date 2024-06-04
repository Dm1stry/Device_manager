#include "operator.hpp"
#include <QDebug>

Operator::Operator(QObject * parent)
  : QObject(parent),
    command_formatter_(nullptr),
    request_formatter_(nullptr)
{
    setCommandFormatter(new ControlByteFormatter);
    setRequestFormatter(new RequestFormatter);
    setConnection(new UDPConnection(this));

    connection_->startConnection();
    connect(connection_, SIGNAL(newData(QByteArray)), this, SLOT(sendData(QByteArray)));
}

// Устанавливает объект, для форматирования данных (если nullptr, данные будут отправляться в том же виде, в котором пришли от виртуального устройства)
void Operator::setCommandFormatter(BaseCommandFormatter * command_formatter)
{
    command_formatter_ = command_formatter;
}

// Возвращает указатель на объект форматёра команд
BaseCommandFormatter * Operator::getCommandFormatter() const
{
    return command_formatter_;
}

// Устанавливает объект для форматирования данных запросов (если nullptr, данные будут отправляться в том же виде, в котором пришли от виртуального устройства)
void Operator::setRequestFormatter(BaseCommandFormatter * request_formatter)
{
    request_formatter_ = request_formatter;
}

// Возвращает указатель на объект форматёра запросов
BaseCommandFormatter * Operator::getRequestFormatter() const
{
    return request_formatter_;
}

// Устанавливает объект, через который происходит обмен сообщениями (например через UDP)
void Operator::setConnection(BaseConnection * connection)
{
    connection_ = connection;
    connection_->setParent(this);
}

// Возвращает указатель на объект подключения
BaseConnection * Operator::getConnection() const
{
    return connection_;
}

// Возвращает вектор указателей на все добавленные ранее виртуальные устройства
QVector<BaseDeviceWidget *> Operator::getDevices() const
{
    return devices_;
}

//Добавить новое виртуальное устройство
void Operator::addDevice(BaseDeviceWidget * device)
{
    if(device)
    {
        devices_.push_back(device);
        device->setOperator(this);
        connect(this, &Operator::newData, device, &BaseDeviceWidget::processData);
        connect(this, &Operator::newBroadcast, device, &BaseDeviceWidget::processBroadcast);  // TODO: Убрать либо это, либо переизлучение сигнала (скорее всего переизлучение)
        connect(device, &BaseDeviceWidget::newCommand, this, &Operator::sendCommand);
        connect(device, &BaseDeviceWidget::newRequest, this, &Operator::sendRequest);
        connect(device,  &BaseDeviceWidget::newRawData, this,  &Operator::sendRaw);
        //connect(device, SIGNAL(newBroadcast(QString, QVector<double>)), this,  SIGNAL(newBroadcast(QString, QVector<double>)));

        emit newDevice(device);
    }
}

// Послать команду через подключение на физическое устройство
void Operator::sendCommand(QByteArray command)
{
    if(command_formatter_)
    {
        command = command_formatter_->formatCommand(command);
    }
    connection_->sendData(command);
    qDebug() << "Оператор (команда): " << QString(command.toHex());
    emit newCommand(command);
}

// Послать запрос через подключение на физическое устройство
void Operator::sendRequest(QByteArray request)
{
    if(request_formatter_)
    {
        request = request_formatter_->formatCommand(request);
    }
    connection_->sendData(request);
    qDebug() << "Оператор (запрос): " << QString(request.toHex());
    emit newRequest(request);
}

// Посылает данные без форматирования на физическое устройство
void Operator::sendRaw(QByteArray data)
{
    connection_->sendData(data);
    qDebug() << "Оператор (сырые данные): " << QString(data.toHex());
    emit newRaw(data);
}

//Передать полученные от физического устройства данные, программным устройствам
void Operator::sendData(QByteArray data)
{
    emit newData(data);
}