#include "task.hpp"

Task::Task(QWidget * parent /*= nullptr*/)
  : commands_edit_(new QPlainTextEdit)
{
    layoutSetup();
    qDebug() << "Task created";
}

void Task::execute()
{
    QStringList commands = commands_edit_->toPlainText().split('\n');
    for(const auto& command : commands)
    {
        QStringList cmd_and_args = command.split(' ');
        QString command_name = cmd_and_args[0];
        QVector<double> command_args;
        for(int i = 1; i < cmd_and_args.size(); ++i)
        {
            command_args.push_back(cmd_and_args[i].toDouble());
        }
        emit newCommand(command_name, command_args);
    }
}

void Task::layoutSetup()
{
    QVBoxLayout * main_layout = new QVBoxLayout(this);

    main_layout->addWidget(commands_edit_);

    this->setLayout(main_layout);
}