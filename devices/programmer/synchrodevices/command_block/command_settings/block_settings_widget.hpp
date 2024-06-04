#ifndef BLOCK_SETTINGS_WIDGET_HPP
#define BLOCK_SETTINGS_WIDGET_HPP

#include <QtWidgets>
#include "argument_settings_widget.hpp"

class BlockSettings : public QWidget
{
Q_OBJECT
public:
    BlockSettings(QString name, QWidget* parent = nullptr);
    ~BlockSettings();
    
    void setArgumentsLines(QString name, QVector<QString> commands_name, QVector<QString> arguments, QVector<double> values);

    void clearList();

private:

    QVector<ArgumentSetting*> argument_lines_;

    QString name_;
    QLabel* block_name_;
    QListWidget* arguments_settings_;

    //-----------------------------------------------------------

signals:
    void argumentChanged(QString command_name, QString name, double value);
};

#endif