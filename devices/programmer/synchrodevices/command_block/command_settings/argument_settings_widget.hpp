#ifndef ARGUMENT_SETTINGS_WIDGET_HPP
#define ARGUMENT_SETTINGS_WIDGET_HPP

#include <QtWidgets>

class ArgumentSetting : public QWidget
{
Q_OBJECT
public:
    ArgumentSetting(QString command_name_, QString name, double value, QListWidget* list, QWidget* parent = nullptr);
    ~ArgumentSetting();

    void setValue(double value);

private:

    void layoutSetup();
    void setConnections();

    QListWidgetItem* list_widget_;

    QString command_name_;
    QString name_;

    QLabel* argument_name_;
    QLineEdit* argument_edit_;

    //QListWidget* block_list_;

    //QVector<CommandBlockEditor*> blocks_;

    //-----------------------------------------------------------

public slots:

    void argumentChanged();

signals:

    void argumentChangedSignal(QString command_name, QString name, double value);

};

#endif