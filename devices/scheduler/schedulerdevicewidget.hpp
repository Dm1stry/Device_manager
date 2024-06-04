#ifndef SCHEDULER_DEVICE_WIDGET
#define SCHEDULER_DEVICE_WIDGET

#include "base/basedevicewidget.hpp"
#include "widgets/subwidgets/customlistwidget.hpp"
#include "taskwidget.hpp"

#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QPushButton>
#include <algorithm>

class TaskWidget;

enum TaskType
{
        ON_SEQUENCE_START = 0,
        ON_SEQUENCE_END,
        ON_APP_START,
        TASK_TYPE_SIZE
};
/*
* Виджет виртуального устройства планировщика задач
* Позволяет создать набор задач, запускаемых при определенных условиях (по пришествии определенных ширковещательных (broadcast) сообщений)
* Задача - набор команд устройств, которые отправляются в широковещательный (broadcast) канал
*/
class SchedulerDeviceWidget : public BaseDeviceWidget
{
Q_OBJECT
public:
    SchedulerDeviceWidget(QWidget * parent = nullptr);
    // -------------------------------------------------------------------------------------------------------------
    // BaseSavable методы, позволяющие получить данные для сохранения класса и 
    // восстановить состояние класса из сохраненных данных, 
    // необходимо для функционирования DeviceLoader
    
    // Возвращает данные о состоянии в виде вектора состояния
    json getStateToSave();
    // Восстанавливает состояние класса из вектора состояния
    bool restoreState(json state);
    // ------------------------------------------
    void processBroadcast(QString command, QVector<double> arguments);
    
    void bindTaskToSignal(TaskType task_type, QString signal);
    bool unbindSignal(QString signal);

    void setTaskName(TaskType task_type, QString name);
    //static Task * createTask(int type);

private slots:
    void addTask();
    void removeTask(TaskWidget * task);
    void setTask(TaskWidget * task, TaskType task_type);

private:

    inline void layoutSetup();
    CustomListWidget* task_list_;
    QPushButton * add_task_button_;

    QMap<QString, TaskType> task_types_;
    QVector<QList<TaskWidget*>> tasks_;
    QStringList task_names_;


    //QMultiMap<int, Task*> tasks_;
    
};

#endif