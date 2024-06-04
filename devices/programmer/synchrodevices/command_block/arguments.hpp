#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include <QtWidgets>

class Arguments : public QObject
{
Q_OBJECT
public:
    Arguments(QString command_name, QVector<QString> names, QObject* parent = nullptr);
    //~Argument();

    void setName(QString command_name);
    QVector<QString> getName();

    void setArgumentsName(QVector<QString> names);
    QVector<QString> getArgumentsName();

    void setArgumentsValue(QVector<double> values);
    QVector<double> getArgumentsValue();
    QVector<double> getArgumentsValue(QVector<QString> names);

    bool setArgumentValue(QString name, double values);
    double getArgumentValue(QString name);

private:
    QVector<QString> command_name_;
    QVector<QString> names_;
    QVector<double> values_;

public slots:

};

#endif