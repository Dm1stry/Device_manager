#include "taskwidget.hpp"

TaskWidget::TaskWidget(QWidget *parent /*= nullptr*/)
  : QFrame(parent),
    task_type_box_(new QComboBox),
    remove_button_(new QPushButton("✕")),
    timer_edit_(new QLineEdit),
    time_units_box_(new QComboBox),
    commands_edit_(new QPlainTextEdit)
{
    connect(remove_button_, &QPushButton::clicked, [=]()
    {
      TaskWidget::taskRemoved(this);
    });
    
	this->setLineWidth(1);
	this->setFrameStyle(QFrame::Box | QFrame::Plain);

    QVBoxLayout * main_layout_ = new QVBoxLayout;
    QHBoxLayout * header_layout = new QHBoxLayout;
    QHBoxLayout * timer_layout = new QHBoxLayout;

	task_type_box_->addItem("При запуске последовательности");
	task_type_box_->addItem("При завершении последовательности");
	task_type_box_->addItem("При запуске приложения");
	task_type_box_->addItem("При завершении приложения");

    header_layout->addWidget(task_type_box_);
    header_layout->addWidget(remove_button_);
    
	remove_button_->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
    task_type_box_->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    main_layout_->addLayout(header_layout);

    QLabel * timer_label = new QLabel("Через время:");
    timer_layout->addWidget(timer_label);
    timer_layout->addWidget(timer_edit_);
    time_units_box_->addItem("с");
    time_units_box_->addItem("мc");
    time_units_box_->addItem("мин");
    timer_layout->addWidget(time_units_box_);
	timer_layout->addSpacing(20);

	main_layout_->addLayout(timer_layout);
	main_layout_->addWidget(commands_edit_);
    
    setLayout(main_layout_);
}

void TaskWidget::execute()
{

}