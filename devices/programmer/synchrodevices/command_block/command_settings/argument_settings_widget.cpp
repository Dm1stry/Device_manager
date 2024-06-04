#include "argument_settings_widget.hpp"

ArgumentSetting::ArgumentSetting(QString command_name, QString name, double value, QListWidget* list, QWidget* parrent):
command_name_(command_name),
name_(name),
QWidget(parrent)
{

    layoutSetup();
    setConnections();
    setValue(value);

    list_widget_ = new QListWidgetItem(list);
    list_widget_->setSizeHint(QSize(150, 40));
    list_widget_->setFlags(list_widget_->flags() & ~Qt::ItemIsSelectable);

    list->setItemWidget(list_widget_, this);
}

ArgumentSetting::~ArgumentSetting()
{

}

void ArgumentSetting::layoutSetup()
{   
    QHBoxLayout* main_layout = new QHBoxLayout();

    argument_name_ = new QLabel(name_);

    argument_edit_ = new QLineEdit();
    //argument_edit_->setValidator(new QDoubleValidator(-32768, 32767, 2, this));

    main_layout->addWidget(argument_name_);
    main_layout->addWidget(argument_edit_);
    this->setLayout(main_layout);
}

void ArgumentSetting::setConnections()
{
    connect(argument_edit_, SIGNAL(editingFinished()), this, SLOT(argumentChanged()));
}

void ArgumentSetting::setValue(double value)
{
    argument_edit_->setText(QString::number(value));
}

// ------------------------------------------------- Слоты

void ArgumentSetting::argumentChanged()
{
    emit argumentChangedSignal(command_name_, name_, argument_edit_->text().toDouble());
}


