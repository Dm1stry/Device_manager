#include "command.hpp"
#include <QDebug>

Command::Command(QString name, quint8 address /*= 0*/, QVector<quint8> arg_lengths /*= {}*/, quint8 command_length /*= 4*/, QObject * parent /*= nullptr*/)
  : QObject(parent),
    name_(name),
    address_(address),
    command_length_((command_length - 1) * 8),
    lengths_(arg_lengths),
    sign_encodings_(arg_lengths.size(), SignEncodingType::UNSIGNED),
    saved_arguments_(arg_lengths.size()),
    arg_names_(arg_lengths.size()),
    symbol_tables_(arg_lengths.size()),
    expressions_(arg_lengths.size()),
    str_expressions_(arg_lengths.size()),
    total_arguments_length_(0)
{


    total_arguments_length_ = std::accumulate(arg_lengths.begin(), arg_lengths.end(), total_arguments_length_);
    
    for(int i = 0; i < arg_lengths.size(); ++i)
    {
        symbol_tables_[i].add_constants();
        expressions_[i].register_symbol_table(symbol_tables_[i]);

        arg_names_[i] = "arg" + std::to_string(i);
        symbol_tables_[i].add_variable(arg_names_[i], saved_arguments_[i]);
    }

    if(total_arguments_length_ > command_length_)
    {
        throw;
    }
}

json Command::getStateToSave()
{
    json state;
    state["address"] = address_;
    for(int i = 0; i < lengths_.size(); ++i)
    {
        state["arguments"][std::to_string(i)] = lengths_[i];
    }
    return state;
}

bool Command::restoreState(json state)
{
    if(state.find("address") == state.end() || state.find("arguments") == state.end())
    {
        return false;
    }
    address_ = state["address"];

    lengths_.clear();
    lengths_.resize(state["arguments"].size());
    for(int i = 0; i <  lengths_.size(); ++i)
    {
        lengths_[i] = state["arguments"][std::to_string(i)].get<quint8>();
    }

    return true;
}

QString Command::getName() const
{
    return name_;
}

// Возвращает значение адресного байта команды
quint8 Command::getAddress() const
{
    return address_;
}


// Возвращает блины аргументов в битах
QVector<quint8> Command::getArgumentsLengths() const
{
    return lengths_;
}


// Возвращает полную суммарную длину аргументов в битах
quint8 Command::getTotalArgumentsLength() const
{
    return total_arguments_length_;
}

// Получает вектор имен аргументов
QVector<QString> Command::getArgumentNames() const
{
    QVector<QString> argument_names(arg_names_.size());
    for(int i = 0; i < arg_names_.size(); ++i)
    {
        argument_names[i] = QString::fromStdString(arg_names_[i]);
    }
    return argument_names;
    //return QVector<QString>(arg_names_.begin(), arg_names_.end());
}

// Получает имя аргумента по индексу
QString Command::getArgumentName(quint8 arg_index) const
{
    return QString::fromStdString(arg_names_[arg_index]);
}

// Находит индекс аргумента с заданными именем. Если аргумента с таким именем не существует, вернет -1
int Command::findArgument(QString arg_name) const
{
    auto found = std::find(arg_names_.begin(), arg_names_.end(), arg_name.toStdString());
    if(found != arg_names_.end())
    {
        return -1;
    }
    return found - arg_names_.begin();
}

// Получает общее количество аргументов
quint8 Command::getArgumentCount() const
{
    return lengths_.size();
}

// Устанавливает значение байта адреса команды
void Command::setAddress(quint8 address)
{
    address_ = address;
}

// Устанавливает новое имя команды. Высылает сигнал nameChanged
void Command::setName(QString name)
{
    emit nameChanged(name_, name);
    name_ = name;
}


// Устанавливает длины адргументов в битах
bool Command::setArgumentsMapping(QVector<quint8> arg_lengths)
{
    quint8 total_length = std::accumulate(arg_lengths.begin(), arg_lengths.end(), 0);

    if(total_length > command_length_)
    {
        return false;
    }
    else
    {
        lengths_ = arg_lengths;
        total_arguments_length_ = total_length;

        /* TODO:
        * Привязать символы в выражении к элементам вектора сохраненных аргументов arg0, arg1, ... (формулы по которым мы преобразуем аргументы в финальное значение)
        * 
        * компиляция выражения происходит при установке формулы, после этого всего выражение само отслеживает изменения переменных и ему плевать
        */

        const int arg_amount = lengths_.size();

        str_expressions_.clear();
        str_expressions_.resize(arg_amount);
        expressions_.clear();
        expressions_.resize(arg_amount);
        symbol_tables_.clear();
        symbol_tables_.resize(arg_amount);
        saved_arguments_.clear();
        saved_arguments_.resize(arg_amount);

        auto arg_iterator = saved_arguments_.begin();

        for(int i = 0; i < arg_amount; ++i, ++arg_iterator)
        {
            symbol_tables_[i].add_variable(arg_names_[i], *arg_iterator);
            expressions_[i].register_symbol_table(symbol_tables_[i]);
        }
        return true;
    }
}

// Устанавливает имя аргумента по индексу. По умолчанию имена arg0, arg1, ...
bool Command::setArgumentName(quint8 arg_index, QString arg_name)
{
    if(arg_index >= lengths_.size())
    {
        return false;
    }
    symbol_tables_[arg_index].remove_variable(arg_names_[arg_index]);
    arg_names_[arg_index] = arg_name.toStdString();
    symbol_tables_[arg_index].add_variable(arg_names_[arg_index], saved_arguments_[arg_index]);
    return true;
}

// Устанавливает имена всех аргументов за раз. По умолчанию имена arg0, arg1,
bool Command::setArgumentNames(QVector<QString> argument_names)
{
    if(argument_names.size() != lengths_.size())
    {
        return false;
    }
    for(int arg_index = 0; arg_index < argument_names.size(); ++arg_index)
    {
        symbol_tables_[arg_index].remove_variable(arg_names_[arg_index]);
        arg_names_[arg_index] = argument_names[arg_index].toStdString();
        symbol_tables_[arg_index].add_variable(arg_names_[arg_index], saved_arguments_[arg_index]);
    }
    return true;
}

// Переименовывет существующий аргумент 
bool Command::setArgumentName(QString old_name, QString new_name)
{
    auto found = std::find(arg_names_.begin(), arg_names_.end(), old_name.toStdString());  // Получаем итератор на элемент, совпадающий с заданным именем
    if(found == arg_names_.end())  // Если элемент с таким именем не найден, возвращаем false
    {
        return false;
    }
    int arg_index = found - arg_names_.begin();  // Через арифметику итераторов получаем индекс
    symbol_tables_[arg_index].remove_variable(*found);
    *found = new_name.toStdString();
    symbol_tables_[arg_index].add_variable(*found, saved_arguments_[arg_index]);
    return true;
}

// Устанавливает кодировку знака для каждого аргумента
bool Command::setArgumentsSignEncoding(QVector<SignEncodingType> encoding_for_each)
{
    if(encoding_for_each.size() != lengths_.size())
    {
        return false;
    }
    sign_encodings_ = encoding_for_each;
    return true;
}

// Устанавливает кодировку знака для всех аргументов
bool Command::setArgumentsSignEncoding(SignEncodingType encoding_for_all)
{
    return setArgumentsSignEncoding(QVector<SignEncodingType>(lengths_.size(), encoding_for_all));
}

// Устанавливает кодировку знака для аргумента с индексом agr_index
bool Command::setArgumentsSignEncoding(quint8 agr_index, SignEncodingType encoding)
{
    if(agr_index >= lengths_.size())
    {
        return false;
    }
    sign_encodings_[agr_index] = encoding;
    return true;
}

// Задает значение сохраненных аргументов
bool Command::setArguments(QVector<double> arguments)
{
    if(arguments.size() != lengths_.size())
    {
        return false;
    }
    for (int i = 0; i < arguments.size(); ++i)
    {
        saved_arguments_[i] = arguments[i];
    }

    return true;
}

// Задает формулу, по которой исходные значения преобразуются в аргументы, зашиваемые в команду
bool Command::setTransformFunction(quint8 argument_index, QString expression)
{
    if(argument_index >= lengths_.size())
    {
        return false;
    }
    if(!expression.isEmpty())
    {
        str_expressions_[argument_index] = expression.toStdString();
        getParser().compile(str_expressions_[argument_index], expressions_[argument_index]);
    }
    return true;
}

// Устанавливает функции преобразования для всех аргументов
bool Command::setTransformFunction(QStringList expressions_for_each)
{
    if(expressions_for_each.size() != lengths_.size())
    {
        return false;
    }
    for(int i = 0; i < lengths_.size(); ++i)
    {
        if(expressions_for_each[i].isEmpty())
        {
            str_expressions_[i] = expressions_for_each[i].toStdString();
        getParser().compile(str_expressions_[i], expressions_[i]);
        }
    }
    return true;
}

// Устанавливает функции преобразования для всех аргументов
bool Command::setTransformFunction(QVector<QString> expressions_for_each)
{
    if(expressions_for_each.size() != lengths_.size())
    {
        return false;
    }
    for(int i = 0; i < lengths_.size(); ++i)
    {
        if(expressions_for_each[i].isEmpty())
        {
            str_expressions_[i] = expressions_for_each[i].toStdString();
        getParser().compile(str_expressions_[i], expressions_[i]);
        }
    }
    return true;
}

// Создает и возвращает байт-код команды с сохраненными аргументами
QByteArray Command::buildCommand() const
{
    quint32 result = 0;
    for(int argument_index = 0; argument_index < saved_arguments_.size(); ++argument_index)
    {
        quint32 mask = 0x1;
        for(int i = 1; i < lengths_[argument_index]; ++i)
        {
            mask = (mask << 1) | 0x1;
        }
        /* 
        * Если до этого, была задана формула, будет рассчитано значение по формуле
        * если же нет, то будет использовано исходное значение
        */
        long expression_result = 0;
        if(str_expressions_[argument_index].empty())
        {
            expression_result = lround(saved_arguments_[argument_index]);  // Математически округляем до знакового целого
        }
        else
        {
            expression_result = lround(expressions_[argument_index].value());  // Математически округляем до знакового целого
        }
        quint32 resulting_argument = 0;
        qint32 max_possible_abs = 1 << (lengths_[argument_index] - 1);
        switch (sign_encodings_[argument_index])
        {
            case SignEncodingType::UNSIGNED:
                resulting_argument = (expression_result <= mask) ? expression_result : mask;  // Если полученное число не умещается в под битовой маской, оно будет уменьшено до максимально-возможного
                resulting_argument = (resulting_argument > 0) ? (quint32)(resulting_argument) : 0;  // Если полученное число положительно, оно преобразуется в беззнаковое целое, иначе, занулится
                break;

            case SignEncodingType::COMPLEMENT:
                // Если полученное число больше максимального положительного для доп кода, оно уменьшется до максимального положительного (1, 3, 7, 15, 31, 127...)
                expression_result = (expression_result < max_possible_abs) ? expression_result : (max_possible_abs - 1);
                // Если полученное число меньше минимального отрицательного для доп кода, оно увеличится до минимального отрицательного (-2, -4, -8, -16, -32, -128...)
                expression_result = (expression_result >= -max_possible_abs) ? expression_result : -max_possible_abs;

                resulting_argument = (quint32)((expression_result > 0) ? expression_result : (~abs(expression_result)) + 1);
                break;
            
            case SignEncodingType::OFFSET:
                // Если полученное число больше максимального положительного для кода со смещением, оно уменьшется до максимального положительного (1, 3, 7, 15, 31, 127...)
                expression_result = (expression_result < max_possible_abs) ? expression_result : (max_possible_abs - 1);
                // Если полученное число меньше минимального отрицательного для кода со смещением, оно увеличится до минимального отрицательного (-2, -4, -8, -16, -32, -128...)
                expression_result = (expression_result >= -max_possible_abs) ? expression_result : -max_possible_abs;

                resulting_argument = (quint32)(expression_result + max_possible_abs);
                break;

            case SignEncodingType::SIGN_BIT:
                --max_possible_abs;  // Максимальный модуль числа
                // Если полученное число больше максимального положительного для кода со смещением, оно уменьшется до максимального положительного (1, 3, 7, 15, 31, 127...)
                expression_result = (expression_result < max_possible_abs) ? expression_result : max_possible_abs;
                // Если полученное число меньше минимального отрицательного для кода со смещением, оно увеличится до минимального отрицательного (-2, -4, -8, -16, -32, -128...)
                expression_result = (expression_result >= -max_possible_abs) ? expression_result : -max_possible_abs;

                resulting_argument = (quint32)((expression_result > 0) ? expression_result : (abs(expression_result) | 1 << lengths_[argument_index]));
                break;
        }
        result = (result << lengths_[argument_index]) | (mask & resulting_argument); 
    }
    result = result << (command_length_ - total_arguments_length_);
    result |= address_ << command_length_;


    QByteArray command((command_length_ / 8) + 1, 0);
    QDataStream stream(&command, QIODevice::WriteOnly);
    stream << result;
    return command;
}

// Создает и возвращает байт-код команды с заданными аргументами
QByteArray Command::buildCommand(QVector<double> arguments)
{
    if(!setArguments(arguments))  // Пытаемся выставить аргументы, если что-то не так, выбрасываем исключение
    {
        throw;
    }
    return buildCommand();
}

exprtk::parser<double>& Command::getParser() const
{
    /*
    * Суть в том, что статические переменные в методе
    * общие для всех экземпляров класса (объектов)
    * А объект парсера весит 1748 байт, что довольно тяжело
    * Поэтому ограничимся одним парсером, особенно учитывая, что многопоточность не планируется
    * 
    * АЛЕРТ! Если в приложение будет завезена многопоточность, ретёрн нужно будет оградить мьютексами или прочими
    * средствами синхронизации!
    */

    static exprtk::parser<double> parser;  // Создается один раз при первом вызове и живет всё время жизни программы
    return parser;
}
