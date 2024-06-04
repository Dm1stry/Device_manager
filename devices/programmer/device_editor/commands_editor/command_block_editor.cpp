#include "command_block_editor.hpp"

CommandBlockEditor::CommandBlockEditor(int id, QString name, QWidget* parent ):QFrame(parent),id_(id),name_(name)
{
    layoutSetup();
    setConnections();

    // list_widget_ = new QListWidgetItem(list);
    // list_widget_->setFlags(list_widget_->flags() & ~Qt::ItemIsSelectable);
    // list_widget_->setSizeHint(QSize(WIDTH_FULL_BLOCK, HEIGHT_FULL_BLOCK));
    
    // list->setItemWidget(list_widget_, this);
}

CommandBlockEditor::~CommandBlockEditor()
{
    
}

void CommandBlockEditor::layoutSetup()
{
    this->setFrameStyle(QFrame::Box | QFrame::Sunken);

    commands_frame_ = new QFrame();
    commands_frame_->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    
    QVBoxLayout* main_layout = new QVBoxLayout();
    QHBoxLayout* name_layout = new QHBoxLayout();
    QHBoxLayout* hor_layout = new QHBoxLayout();
    QVBoxLayout* block_layout = new QVBoxLayout();
    QHBoxLayout* dawn_layout = new QHBoxLayout();

    QLabel* name_label = new QLabel("Название: ");
    name_line_ = new QLineEdit();
    name_line_->setText(name_);
    name_line_->setFixedWidth(100);
    name_layout->addWidget(name_label);
    name_layout->addWidget(name_line_);
    name_layout->addStretch(1);

    command_list_ = new QListWidget();

    add_new_command_button_ = new QPushButton("+");
    add_new_command_button_->setMaximumWidth(60);

    //////
    CommandLineEditor* line = new CommandLineEditor(1,command_list_);
    command_lines_.append(line);
    this->setHeigh(1);
    //////

    block_layout->addWidget(command_list_);

    dawn_layout->addWidget(add_new_command_button_);

    block_layout->addLayout(dawn_layout);

    block_layout->setContentsMargins(0,0,0,5);
    block_layout->setAlignment(Qt::AlignCenter);

    commands_frame_->setLayout(block_layout);


    graphics_type_box = new QComboBox();

    QStringList types;
    types << "Импульс" << "Уровень";
    graphics_type_box->addItems(types);
    graphics_type_box->setMaximumHeight(40);
    
    hor_layout->addWidget(commands_frame_);
    hor_layout->addWidget(graphics_type_box);

    hor_layout->setContentsMargins(1,1,1,3);
    //main_layout->setAlignment(Qt::AlignCenter);

    main_layout->addLayout(name_layout);
    main_layout->addLayout(hor_layout);
    this->setLayout(main_layout);
} 

void CommandBlockEditor::setConnections()
{
    connect(add_new_command_button_, SIGNAL(clicked()), this, SLOT(addNewCommand()));
}

// ------------------------------------------------- Методы

void CommandBlockEditor::setHeigh(int number_commands)
{
    commands_frame_->setFixedSize(WIDTH_BLOCK,HEIGHT_LINE * number_commands + HEIGHT_LINE);
    this->setFixedHeight(HEIGHT_LINE * number_commands + 2*HEIGHT_LINE + 5);
    //list_widget_->setSizeHint(QSize(WIDTH_FULL_BLOCK, HEIGHT_LINE * number_commands + HEIGHT_FULL_BLOCK));
}

// ------------------------------------------------- Слоты

void CommandBlockEditor::addNewCommand()
{
    CommandLineEditor* newline = new CommandLineEditor(command_lines_.size()+1,command_list_);
    command_lines_.append(newline);
    this->setHeigh(command_lines_.size());
    emit addNewCommandSignal();
}
