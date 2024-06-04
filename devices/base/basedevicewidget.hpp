#ifndef BASE_DEVICE_WIDGET_HPP
#define BASE_DEVICE_WIDGET_HPP

#include <QWidget>
#include <QByteArray>
#include <QMap>
#include "command.hpp"
#include "operator/deviceloader/basesavable.hpp"
#include "operator/operator.hpp"

/*
Базовый абстрактный виджет всех виртуальных устройств,
предполагается наследование от него, и реализация метода обработки данных, 
пришедших от физического устройства 
*/
class Operator;

class BaseDeviceWidget : public QWidget, public BaseSavable
{
Q_OBJECT
public:
    BaseDeviceWidget(QWidget * parent = nullptr);
    BaseDeviceWidget(QString name, QWidget * parent = nullptr);
    virtual ~BaseDeviceWidget();

    // Возвращает имя устройства
    QString getName() const;

    // Конструирует набор битов команды, но не отсылает её
    QByteArray getCommand(QString command, QVector<double> arguments) const;

    enum Status
    {
        BUSY,
        IDLE
    };

    virtual void setOperator(Operator * op); 


public slots:
    // Устанавливает отображаемое имя устройства
    virtual void setName(QString name);

    // Обрабатывает данные, пришедшие от класса опреатора, в том числе проверяет принадлежность
    virtual void processData(QByteArray data);

    // Обрабатывает широковещательные сообщения, высылаемые устройствами
    virtual void processBroadcast(QString command, QVector<double> arguments);

    // Создает команду с соответствующим именем, адресом и аргументами. Если команда с таким именем уже существует, заменит её
    virtual void setCommand(QString name, quint8 address, QVector<quint8> arg_lengths, quint8 command_length = 4);
    
    // Создает запрос с соответствующим именем и адресом. Если запрос с таким именем уже существует, заменит его
    virtual void setRequest(QString name, quint8 address);

    // Изменяет имя существующей команды
    virtual void renameCommand(QString old_name, QString new_name);

    // Удаляет команду с заданными именем
    virtual void removeCommand(QString name);

    // Отправляет байт код команды с закодированными аргументами физическому устройству
    virtual bool executeCommand(QString command, QVector<double> arguments);

    // Позволяет исполнить команду заданную в текстовом формате. Нужно для работы планировщика задач
    virtual bool executeCommand(QString command_line);
    
    // Позволяет отправить запрос заданнуому устройству
    virtual bool sendRequest(QString request);
    
private slots:
    // Если у команды сменилось имя, обновит сохраненное у себя имя
    virtual void updateCommandName(QString old_name, QString new_name);

signals:

    //Сигнал, несущий команду, которую мы хотим послать физическому устройству
    Q_SIGNAL void newCommand(QByteArray);

    // Сигнал, несущий команду - запрос на получение данных
    Q_SIGNAL void newRequest(QByteArray);

    // Сигнал, несущий сырые данные, которые мы хотим переслать физическому устройству
    Q_SIGNAL void newRawData(QByteArray);

    // Сигнал, несщий широковещательное сообщение
    Q_SIGNAL void newBroadcast(QString, QVector<double>);

protected:
    QMap<QString, Command*> commands_;  //Хэш-таблица пары имя команды - команда
    QMap<QString, Command*> requests_;  // Хэш-таблица пары имя запроса - запрос

    QString name_;  // Имя, которое будет отображаться в меню
    Status status_;  // Поле статуса
    Operator * operator_ptr_; // Указатель на оператор
};

#endif
