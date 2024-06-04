#ifndef TASK_HPP
#define TASK_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QLabel>
#include <QDebug>
//#include "schedulerdevicewidget.hpp"


class Task : public QWidget
{
Q_OBJECT
public:
    Task(QWidget * parent = nullptr);
    virtual void execute();
signals:
    Q_SIGNAL void newCommand(QString name, QVector<double> args);
protected:
    virtual void layoutSetup();
    QPlainTextEdit * commands_edit_;
};

#endif