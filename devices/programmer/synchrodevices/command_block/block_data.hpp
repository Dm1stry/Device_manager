#ifndef BLOCK_DATA_HPP
#define BLOCK_DATA_HPP

#include <QtWidgets>
#include "arguments.hpp"
#include "../../../base/command.hpp"
#include "../../sequence_editor/items/command_items/style_headers.hpp"

class BlockData : public QObject
{
Q_OBJECT
public:
    BlockData(QString name, QVector<Command*> commands, quint8 graphics_type = 0, QObject* parent = nullptr);
    ~BlockData();

    void setCommandStyle(quint8 graphics_type = 0);
    BaseCommandStyle* getCommandStyle();

    //void setArgumentsNames(QVector<Command*> commands);
    QVector<QString> getCommandsName();
    QVector<QString> getArgumentsName();
    QVector<double> getArgumentsValue();

    bool setArgumentValue(QString command_name, QString argument_name, double value);
    double getArgumentValue(QString command_name, QString argument_name);
    QVector<double> getArgumentValue(QString command_name, QVector<QString> argument_names);

    QString getName();

    QByteArray buildCommand();

private:

    QVector<Command*> commands_;

    QString block_name_;

    QVector<Arguments*> arguments_; 

    BaseCommandStyle* command_icon_ = nullptr;

public slots:

};

#endif