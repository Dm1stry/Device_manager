#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <QObject>
#include <QBitArray>
#include <QDataStream>
#include <QVector>
#include <string>
#include <cmath>  // lround, abs - для округления результата математических выражений
#include <algorithm>  // std::find in renameArgument
#include "operator/deviceloader/basesavable.hpp"
#include <exprtk.hpp>  // Парсер математических выражений


/*
Класс Команды - инструмента для преобразования аргументов из численного представления в байт-код
*/
class Command : public QObject, public BaseSavable
{
Q_OBJECT
public:
    /*
        name - имя команды, важно для обращения к команде через braodcast интерфейс
        address - адрес команды, записываемый в первый байт команды
        arg_lengths - длины аргументов, в том порядке, в каком они должны быть расположены в команде
        command_length - длина команды в байтах, вместе с адресом

    */
    explicit Command(QString name, quint8 address = 0, QVector<quint8> arg_lengths = {}, quint8 command_length = 4, QObject * parent = nullptr);

// -------------------------------------------------------------------------------------------------------------
    // BaseSavable методы, позволяющие получить данные для сохранения класса и 
    // восстановить состояние класса из сохраненных данных, 
    // необходимо для функционирования DeviceLoader
    
    // Возвращает данные о состоянии в виде вектора состояния
    json getStateToSave();

    // Восстанавливает состояние класса из вектора состояния
    bool restoreState(json state);

    // Метод изинтерфейса BaseSavable, возвращающий имя команды, которое будет ключом в json строке
    QString getName() const;  
//-----------------------------------------------------------------------------------------------------------------------------

    enum SignEncodingType
    {   
        UNSIGNED,  // Баззнаковое
        COMPLEMENT, // Дополнительный код
        OFFSET,  // Кодировка со смещением
        SIGN_BIT  // Кодировка знака отдельным битом
    };

    // Возвращает значение адресного байта команды
    quint8 getAddress() const;

    // Возвращает длины аргументов в битах
    QVector<quint8> getArgumentsLengths() const;

    // Возвращает полную суммарную длину аргументов в битах
    quint8 getTotalArgumentsLength() const;

    // Получает вектор имен аргументов
    QVector<QString> getArgumentNames() const;

    // Получает имя аргумента по индексу
    QString getArgumentName(quint8 arg_index) const;

    // Находит индекс аргумента с заданными именем. Если аргумента с таким именем не существует, вернет -1
    int findArgument(QString arg_name) const;

    // Получает общее количество аргументов
    quint8 getArgumentCount() const;

public slots:
    // Устанавливает значение байта адреса команды
    void setAddress(quint8 address);

    // Устанавливает новое имя команды. Высылает сигнал nameChanged
    void setName(QString name);

    // Устанавливает длины адргументов в битах
    bool setArgumentsMapping(QVector<quint8> arg_lengths);

    // Устанавливает имя аргумента по индексу. По умолчанию имена arg0, arg1, ...
    bool setArgumentName(quint8 arg_index, QString arg_name);

    // Устанавливает имена всех аргументов за раз. По умолчанию имена arg0, arg1,
    bool setArgumentNames(QVector<QString> arg_names);

    // Переименовывет существующий аргумент 
    bool setArgumentName(QString old_name, QString new_name);

    // Устанавливает кодировку знака для каждого аргумента
    bool setArgumentsSignEncoding(QVector<SignEncodingType> encoding_for_each);

    // Устанавливает кодировку знака для всех аргументов
    bool setArgumentsSignEncoding(SignEncodingType encoding_for_all);

    // Устанавливает кодировку знака для аргумента с индексом agr_index
    bool setArgumentsSignEncoding(quint8 agr_index, SignEncodingType encoding);

    // Устанавливает значения аргументов, которые будут использованы в buildCommand()
    bool setArguments(QVector<double> arguments);

    // Устанавливает функцию преобразования для аргумента c заданным индексом
    bool setTransformFunction(quint8 argument_index, QString expression);

    // Устанавливает функции преобразования для всех аргументов
    bool setTransformFunction(QStringList expressions_for_each);

    // Устанавливает функции преобразования для всех аргументов
    bool setTransformFunction(QVector<QString> expressions_for_each);    

    // Создает и возвращает байт-код команды с сохраненными прежде аргументами аргументами
    QByteArray buildCommand() const;

    // Создает и возвращает байт-код команды с заданными аргументами
    QByteArray buildCommand(QVector<double> arguments);
signals:
    Q_SIGNAL void nameChanged(QString old_name, QString new_name);
private:
    QString name_;  // Название команды
    quint8 address_;  // Байт адреса команды
    quint8 command_length_;  // Максимальная суммарная длина аргументов команды (чтобы уместилось в команде) в битах. TODO изменить имя на что-то более понятное
    QVector<quint8> lengths_;  // Длины аргументов в битах
    QVector<SignEncodingType> sign_encodings_;  // Способ кодировать знак аргументах, по умолчанию беззнаковое
    QVector<double> saved_arguments_;  // Сохраненные значения аргументов, которые будут использованы в buildCommand()
    quint8 total_arguments_length_;  // Полная суммарная длина аргументов в битах (нужна чтобы знать насколько сместить полученное значение)
    QVector<std::string> arg_names_;

    exprtk::parser<double>& getParser() const; // Возвращает ссылку на объект парсера // Парсера достаточно и одного, и занимает он 1748 байт, чтобы использовать лишь один, используется статическая переменная в методе
    QVector<exprtk::symbol_table<double>> symbol_tables_;  // Таблицы соответствия символ в строке - ссылка на переменную (на элемент вектора тоже можно)
    QVector<exprtk::expression<double>> expressions_;  // Закодированные скомпилированные выражения, к которым привязываются ссылки на переменные, и которые, в конечном итоге используются для вычисления финальных значений
    QVector<std::string> str_expressions_;  // Выражения в виде строк
};

#endif
