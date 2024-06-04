#include "mainwindow.hpp"

MainWindow::MainWindow(Operator * operator_pointer, QWidget * parent)
  : QWidget(parent),
    settings_window_(new SettingsWindow),
    side_menu_widget_(new SideMenuWidget(settings_window_)),
    main_widget_(new MainWidget),
	operator_(operator_pointer)
{
    operator_pointer->setParent(this);  // Назначаем виджет родителем оператора, чтобы при закрытии окна, оператор автоматически удалялся
    // Добавляем отображение всех добавленных прежде устройств в виджет для отображения
    for(auto device : operator_pointer->getDevices())  
    {
        main_widget_->addDevice(device);
    }

    layoutSetup();

    connect(settings_window_, SIGNAL(connectionParameterUpdated(int, QVariant)), operator_->getConnection(), SLOT(setParameter(int, QVariant)));  // TODO. Это тоже надо бы как-нибудь поправить
    connect(operator_, &Operator::newDevice, main_widget_,  &MainWidget::addDevice);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    settings_window_->close();  // При закрытии главного окна, также закроется и окно настроек
    Q_UNUSED(event);
}

inline void MainWindow::layoutSetup()
{
	QHBoxLayout * main_layout = new QHBoxLayout;
    main_layout->addWidget(side_menu_widget_);
    main_layout->addWidget(main_widget_);  
    //main_layout->setStretchFactor(side_menu_widget_, 1);  //Выставляем соотношение размеров бокового меню
    //main_layout->setStretchFactor(main_widget_, 20); // и главного виджета 1 к 20
    main_layout->setSpacing(0);  //Выставляем нулевой отступ между элементов
    main_layout->setContentsMargins(0, 0, 0, 0); //Выставляем нулевые внешние отступы
    this->setLayout(main_layout);
}