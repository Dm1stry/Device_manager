#ifndef COMMAND_LINE_EDITOR_HPP
#define COMMAND_LINE_EDITOR_HPP

#include <QtWidgets>
#include "../../editor_size.hpp"
#include "../../../../base/command.hpp"
using namespace EditorSize;

class CommandLineEditor : public QWidget
{
Q_OBJECT
public:
    CommandLineEditor(int number, QListWidget* list, QWidget* parent = nullptr);
    ~CommandLineEditor();

private:
    void layoutSetup();
    void setConnections();

    QListWidgetItem* list_widget_;

    int number_;
    quint8 numbers_arguments_;
    Command* command_;

    QLineEdit* name_edit_;
    QLineEdit* address_edit_;
    QLineEdit* numbers_arguments_edit_;
    QPushButton* settings_;

private slots:
    void setName();
    void setAddress();
    void setArgumentsMapping(QVector<quint8> lengths); // временно
    void setTransformFunction(QVector<QString> functions);// временно
    
    void setNumberArguments();
    void setting();

signals:

};

#endif