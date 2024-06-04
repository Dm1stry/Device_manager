#ifndef TASK_WIDGET_HPP
#define TASK_WIDGET_HPP

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include "schedulerdevicewidget.hpp"

class SchedulerDeviceWidget;

class TaskWidget : public QFrame
{
Q_OBJECT

friend class SchedulerDeviceWidget;

public:
    TaskWidget(QWidget *parent = nullptr);
    void execute();
signals:
    void taskRemoved(TaskWidget *);
private:
    //inline void layoutSetup();

    //SchedulerDeviceWidget::TaskType task_type_;

    QComboBox * task_type_box_;
    QPushButton * remove_button_;
    QLineEdit * timer_edit_;
    QComboBox * time_units_box_;
    QPlainTextEdit * commands_edit_;
    
};

#endif