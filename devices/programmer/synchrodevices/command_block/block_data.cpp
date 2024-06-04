#include "block_data.hpp"

BlockData::BlockData(QString name, QVector<Command*> commands, quint8 graphics_type, QObject* parent):
commands_(commands),
QObject(parent)
{   
    block_name_ = name;
    for (int i = 0; i < commands.size(); ++i)
    {
        arguments_.append(new Arguments(commands[i]->getName(), commands[i]->getArgumentNames()));
    }

    setCommandStyle(graphics_type);
}

BlockData::~BlockData()
{
    for (int i = 0; i < arguments_.size(); ++i)
    {
        delete arguments_[i];
    }  
    arguments_.clear();
}

// -------------------------------------------------------------- Методы

void BlockData::setCommandStyle(quint8 graphics_type)
{
    switch(graphics_type)
    {
        case 0:
            command_icon_ = new PulseCommand();
            break;
        case 1:
            command_icon_ = new LockCommand();
            break;
    }
}

BaseCommandStyle* BlockData::getCommandStyle()
{
    return command_icon_;
}

QVector<QString> BlockData::getCommandsName()
{
    QVector<QString> arg_names;
    for (int i = 0; i < arguments_.size(); ++i)
    {
        arg_names.append(arguments_[i]->getName());
    }
    return arg_names;
}

QVector<QString> BlockData::getArgumentsName()
{
    QVector<QString> arg_names;
    for (int i = 0; i < arguments_.size(); ++i)
    {
        arg_names.append(arguments_[i]->getArgumentsName());
    }
    return arg_names;
}

QVector<double> BlockData::getArgumentsValue()
{
    QVector<double> arg_values;
    for (int i = 0; i < arguments_.size(); ++i)
    {
        arg_values.append(arguments_[i]->getArgumentsValue());
    }
    return arg_values;
}

bool BlockData::setArgumentValue(QString command_name, QString argument_name, double value)
{
    for (int i = 0; i < arguments_.size(); ++i)
    {
        if (arguments_[i]->getName()[0] == command_name)
        {
            arguments_[i]->setArgumentValue(argument_name, value);
            return 1;
        }
    }
    return 0;
}

double BlockData::getArgumentValue(QString command_name, QString argument_name)
{
    return 0;
}

QVector<double> BlockData::getArgumentValue(QString command_name, QVector<QString> argument_names)
{
    for (int i = 0; i < arguments_.size(); ++i)
    {
        if (arguments_[i]->getName()[0] == command_name)
        {
            return arguments_[i]->getArgumentsValue(argument_names);
        }
    }
    return QVector<double>(argument_names.size());
}

QString BlockData::getName()
{
    return block_name_;
}

QByteArray BlockData::buildCommand()
{
    QByteArray command = QByteArray();
    for (int i = 0; i < commands_.size(); ++i)
    {
        command.append(commands_[i]->buildCommand(getArgumentValue(commands_[i]->getName(), commands_[i]->getArgumentNames())));
    }
    return command;
}
