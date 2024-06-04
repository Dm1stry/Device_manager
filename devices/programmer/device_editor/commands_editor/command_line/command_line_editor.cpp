#include "command_line_editor.hpp"

CommandLineEditor::CommandLineEditor(int number, QListWidget* list, QWidget* parrent) : number_(number),
QWidget(parrent)
{
    command_ = new Command("");

    layoutSetup();
    setConnections();

    list_widget_ = new QListWidgetItem(list);
    list_widget_->setSizeHint(QSize(WIDTH_LINE, HEIGHT_LINE));
    list_widget_->setFlags(list_widget_->flags() & ~Qt::ItemIsSelectable);

    list->setItemWidget(list_widget_, this);
}

CommandLineEditor::~CommandLineEditor()
{

}

void CommandLineEditor::layoutSetup()
{   
    QHBoxLayout* main_layout = new QHBoxLayout();

    QString str = QString::number(number_);
    QLabel* nameLabel = new QLabel(str + ") " + "Имя: ");
    name_edit_ = new QLineEdit();
    name_edit_->setMaximumWidth(85);

    QLabel* addressLabel = new QLabel("Адрес: 0x");
    address_edit_ = new QLineEdit();
    address_edit_->setInputMask("Hh");
    address_edit_->setValidator(new QIntValidator(0, 0xFF, this));
    address_edit_->setMaximumWidth(40);

    QLabel* numArgLabel = new QLabel("Кол-во аргументов: ");
    numbers_arguments_edit_ = new QLineEdit();
    numbers_arguments_edit_->setValidator(new QIntValidator(1, 24, this));
    numbers_arguments_edit_->setMaximumWidth(40);

    settings_ = new QPushButton();
    QPixmap pixmap(":/programmerdevice/devicewidget/gear-alt.svg");
    QIcon ButtonIcon(pixmap);
    settings_->setIcon(ButtonIcon);
    settings_->setIconSize(QSize(20,20));
    settings_->setMaximumSize(25,24);
    settings_->setStyleSheet("QPushButton{background: rgb(255,255,255); border-radius: 5px; border:none;}"
                          "QPushButton:hover{background: rgb(210,210,210); border-radius: 5px; border:none;}"); 

    main_layout->addWidget(nameLabel);
    main_layout->addWidget(name_edit_);
    main_layout->addSpacing(15);
    main_layout->addWidget(addressLabel);
    main_layout->addWidget(address_edit_);
    main_layout->addSpacing(15);
    main_layout->addWidget(numArgLabel);
    main_layout->addWidget(numbers_arguments_edit_);
    main_layout->addSpacing(5);
    main_layout->addWidget(settings_);

    main_layout->addStretch(1);

    this->setLayout(main_layout);
}

void CommandLineEditor::setConnections()
{
    connect(name_edit_, SIGNAL(editingFinished()), this, SLOT(setName()));
    connect(address_edit_, SIGNAL(editingFinished()), this, SLOT(setAddress()));
    connect(numbers_arguments_edit_, SIGNAL(editingFinished()), this, SLOT(setNumberArguments()));
    connect(settings_, SIGNAL(clicked()), this, SLOT(setting()));
}

// ------------------------------------------------- Слоты

void CommandLineEditor::setName()
{

}

void CommandLineEditor::setAddress()
{
    command_->setAddress(address_edit_->text().toUInt());
}

void CommandLineEditor::setArgumentsMapping(QVector<quint8> lengths)
{
    command_->setArgumentsMapping(lengths);
}

void CommandLineEditor::setTransformFunction(QVector<QString> functions)
{
    for(int i = 0; i < numbers_arguments_; ++i)
    {
        command_->setTransformFunction(i,functions[i]);
    }
}

void CommandLineEditor::setNumberArguments()
{
    numbers_arguments_ = numbers_arguments_edit_->text().toUInt();
}

void CommandLineEditor::setting()
{

}