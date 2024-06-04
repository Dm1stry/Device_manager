#include "block_settings_widget.hpp"

BlockSettings::BlockSettings(QString name, QWidget* parrent):
name_(name),
QWidget(parrent)
{
    QVBoxLayout* main_layout = new QVBoxLayout();

    block_name_ = new QLabel(name_);

    arguments_settings_ = new QListWidget();

    main_layout->addWidget(block_name_);
    main_layout->addWidget(arguments_settings_);
    this->setLayout(main_layout);
}

BlockSettings::~BlockSettings()
{

}

void BlockSettings::setArgumentsLines(QString name, QVector<QString> commands_name, QVector<QString> arguments, QVector<double> values)
{   
    clearList();
    name_ = name;
    block_name_->setText(name);
    for (int i = 0; i < arguments.size(); ++i)
    {
        argument_lines_.append(new ArgumentSetting(commands_name[i], arguments[i], values[i], arguments_settings_));
        connect(argument_lines_.back(), SIGNAL(argumentChangedSignal(QString, QString, double)), this, SIGNAL(argumentChanged(QString, QString, double)));
    }
}

void BlockSettings::clearList()
{
    arguments_settings_->clear();
    for (int i = 0; i < argument_lines_.size(); ++i)
    {
        if (argument_lines_[i] != nullptr)
        {
            delete argument_lines_[i];
            argument_lines_[i] = nullptr;
        }
    }
    argument_lines_.clear();
    name_ = "";
    block_name_->setText("");
}

// ------------------------------------------------- Слоты

