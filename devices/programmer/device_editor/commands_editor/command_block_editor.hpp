#ifndef COMMAND_BLOCK_EDITOR_HPP
#define COMMAND_BLOCK_EDITOR_HPP

#include <QtWidgets>
#include "../../../base/command.hpp"
#include "command_line/command_line_editor.hpp"
#include "../editor_size.hpp"
using namespace EditorSize;

class CommandBlockEditor : public QFrame
{
Q_OBJECT
public:
    CommandBlockEditor(int id, QString name, QWidget* parent = nullptr);
    ~CommandBlockEditor();

    int getId();

private:
    void layoutSetup();
    void setConnections();

    QListWidgetItem* list_widget_;

    QFrame* commands_frame_;

    QLineEdit* name_line_;
    QListWidget* command_list_;
    QPushButton* add_new_command_button_;
    QComboBox* graphics_type_box;

    int id_;
    QString name_;

    QVector<CommandLineEditor*> command_lines_;
    int graphics_type_ = 0;

    void setHeigh(int number_commands);

public slots:
    void addNewCommand();   // Добавление новой команды
    //void setCommandName(QString name);

signals:
    void addNewCommandSignal();

};

#endif