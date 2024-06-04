#include "schedulerdevicewidget.hpp"

SchedulerDeviceWidget::SchedulerDeviceWidget(QWidget * parent /*= nullptr*/)
  : BaseDeviceWidget("Планировщик", parent),
	task_list_(new CustomListWidget),
    add_task_button_(new QPushButton("Добавить задачу"))
{
    for(int i = 0; i < TaskType::TASK_TYPE_SIZE; ++i)
    {
        task_names_.push_back("");
    }

    setTaskName(TaskType::ON_SEQUENCE_START, "При запуске последовательности");
    setTaskName(TaskType::ON_SEQUENCE_END, "При завершении последовательности");
    setTaskName(TaskType::ON_APP_START, "При запуске приложения");

    bindTaskToSignal(TaskType::ON_APP_START, "app_started");
    bindTaskToSignal(TaskType::ON_SEQUENCE_START, "sequence_started");
    bindTaskToSignal(TaskType::ON_SEQUENCE_END, "sequence_ended");
    
    layoutSetup();
    connect(add_task_button_, &QPushButton::clicked, this, &SchedulerDeviceWidget::addTask);
}

json SchedulerDeviceWidget::getStateToSave()
{
    return json();
}

bool SchedulerDeviceWidget::restoreState(json state)
{
    return true;
}

void SchedulerDeviceWidget::processBroadcast(QString command, QVector<double> arguments)
{
    auto tasks_to_execute = tasks_[task_types_[command]];
    for(auto task : tasks_to_execute)
    {
        task->execute();
    }
}

void SchedulerDeviceWidget::bindTaskToSignal(TaskType task_type, QString signal)
{
    task_types_[signal] = task_type;
}

bool SchedulerDeviceWidget::unbindSignal(QString signal)
{
    if(task_types_.contains(signal))
    {
        task_types_.remove(signal);
        return true;
    }
    return false;
}

void SchedulerDeviceWidget::setTaskName(TaskType task_type, QString task_name)
{
    task_names_[task_type] = task_name;
}
/*
Task * SchedulerDeviceWidget::createTask(int type)
{
    switch(type)
    {
        case TaskType::ON_SEQUENCE_START:
            return new Task();
            break;
        case TaskType::ON_SEQUENCE_END:
            return new Task();
            break;
        case TaskType::ON_SEQUENCE_START_WITH_TIMER:
            //return new TimerTask();
            break;
        case TaskType::ON_SEQUENCE_END_WITH_TIMER:
            //return new TimerTask();
            break;
        case TaskType::ON_APP_START:
            return new Task();
            break;
    }
}*/

void SchedulerDeviceWidget::addTask()
{
    TaskWidget * task_widget = new TaskWidget(this);
    connect(task_widget, &TaskWidget::taskRemoved, [=](TaskWidget * task_widget){
        task_list_->removeWidget(task_widget);
    });
    task_list_->addWidget(task_widget);
}

void SchedulerDeviceWidget::removeTask(TaskWidget * task)
{
    for(auto task_lst : tasks_)
    {
        auto it = std::find(task_lst.begin(), task_lst.end(), task);
        if(it != task_lst.end())
        {
            task_lst.takeAt(it - task_lst.begin());
            break;
        }
    }
    this->update();
}

void SchedulerDeviceWidget::setTask(TaskWidget * task, TaskType task_type)
{
    removeTask(task);
    tasks_[task_type].push_back(task);
}

void SchedulerDeviceWidget::layoutSetup()
{
    QVBoxLayout * main_layout = new QVBoxLayout(this);
	main_layout->addWidget(task_list_);
    main_layout->addWidget(add_task_button_);
	this->setLayout(main_layout);
}