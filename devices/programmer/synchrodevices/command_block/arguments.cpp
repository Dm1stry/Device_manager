#include "arguments.hpp"

Arguments::Arguments(QString command_name, QVector<QString> names, QObject* parent):
names_(names),
QObject(parent)
{
    for (int i = 0; i < names.size(); ++i)
    {
        command_name_.append(command_name);
        values_.append(0);
    }
}

// -------------------------------------------------------------- Методы

void Arguments::setName(QString command_name)
{
    for (int i = 0; i < command_name_.size(); ++i)
    {
        command_name_[i] = command_name;
    }
}

QVector<QString> Arguments::getName()
{
    return command_name_;
}

void Arguments::setArgumentsName(QVector<QString> names)
{
    names_ = names;
}

QVector<QString> Arguments::getArgumentsName()
{
    return names_;
}

void Arguments::setArgumentsValue(QVector<double> values)
{
    values_ = values;
}

QVector<double> Arguments::getArgumentsValue()
{
    return values_;
}

QVector<double> Arguments::getArgumentsValue(QVector<QString> names)
{
    QVector<double> value;
    for (int i = 0; i < names.size(); ++i)
    {
        for (int j = 0; j < names_.size(); ++j)
        {
            if (names_[j] == names[i])
            {
                value.append(values_[j]);
            }
        }
    }
    if (value.size() == names.size())
    {
        return value;
    }
    else
    {
        return QVector<double>();
    }
}


bool Arguments::setArgumentValue(QString name, double value)
{
    qDebug() << "Arg begin";
    for (int i = 0; i < names_.size(); ++i)
    {
        if (names_[i] == name)
        {
            values_[i] = value;
            return 1;
        }
    }
    qDebug() << "Arg end";
    return 0;
}

double Arguments::getArgumentValue(QString name)
{
    return 0;
}