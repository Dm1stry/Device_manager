#ifndef COMMAND_BLOCK_HPP
#define COMMAND_BLOCK_HPP

#include <QtWidgets>
#include "../../../base/command.hpp"
#include "block_data.hpp"
// #include "../../sequence_editor/items/command_items/style_headers.hpp"

class CommandBlock : public QObject
{
Q_OBJECT
public:
    CommandBlock(QString name, QVector<Command*> commands, quint8 graphics_type = 0);
    ~CommandBlock();

    BlockData* getBlockDataCopy();
    QString getName();
    
    QVector<Command*> getCommands();
    //CommandBlock* getCopy();

private:
    quint8 graphics_type_ = 0;
    QString name_ = "";
    QVector<Command*> commands_;

    BlockData* block_data_ = nullptr;

public slots:
    void addNewCommand(QString name, quint8 address, QVector<quint8> arg_lengths, QVector<QString> expressions);
    void removeLastCommand();

};

#endif