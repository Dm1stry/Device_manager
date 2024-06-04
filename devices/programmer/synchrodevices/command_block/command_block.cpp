#include "command_block.hpp"

CommandBlock::CommandBlock(QString name, QVector<Command*> commands, quint8 graphics_type):
graphics_type_(graphics_type),
name_(name),
commands_(commands)
{
    block_data_ = new BlockData(name, commands, graphics_type, this);
}

CommandBlock::~CommandBlock()
{

}

// -------------------------------------------------------------- Методы

BlockData* CommandBlock::getBlockDataCopy()
{
    return new BlockData(name_, commands_, graphics_type_, this);
}

QString CommandBlock::getName()
{
    return name_;
}

QVector<Command*> CommandBlock::getCommands()
{
    return commands_;
}

// -------------------------------------------------------------- Слоты

void CommandBlock::addNewCommand(QString name, quint8 address, QVector<quint8> arg_lengths, QVector<QString> expressions)
{
    commands_.append(new Command(name, address, arg_lengths, 4));
    for (int i = 0; i < arg_lengths.size(); ++i)
    {
        commands_.back()->setTransformFunction(i, expressions[i]);
    }
}

void CommandBlock::removeLastCommand()
{

}
