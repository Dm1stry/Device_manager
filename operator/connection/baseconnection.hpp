#ifndef BASE_CONNECTION_HPP
#define BASE_CONNECTION_HPP

#include <QObject>
#include <QVariant>
#include <QMap>

/*
*   Базовый абстрактный класс подключения,
*   обеспечивающий заменяемость способа подключения без изменения остального кода.
*
*   Все классы, отвечающие за отправку и получение данных через какое-либо физическое подключение
*   должны быть унаследованы от BaseConnection.
*/

class BaseConnection : public QObject
{
Q_OBJECT
public:
    BaseConnection(QObject * parent = nullptr);
    virtual bool sendData(QByteArray data) = 0;  // Посылает данные через соединение
    virtual QVector<QByteArray> collectData() = 0;  // Получает всё, что успело придти через соединение
    virtual bool startConnection() = 0;  // Инициирует подключение
    virtual BaseConnection* clone() = 0;  // Клонирует объект подключения, после клонирования новый объект необходимо запустить, используя startConnection()
public slots:
    virtual void setParameter(int id, QVariant data) = 0;  // Устанавливает значение параметра с сообветствующим id (лучше реализовать enum, чтобы при использовании класса было ясно, какие параметры можно установить).id - от нуля
    virtual void setParameter(int id, QString data) = 0;
signals:
    void newData(QByteArray);  // Сигнал о том, что появились новые данные
protected:
    QVector<QByteArray> received_data_;  // Буффер полученных данных
};

#endif