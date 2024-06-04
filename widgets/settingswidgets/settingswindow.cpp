#include "settingswindow.hpp"

SettingsWindow::SettingsWindow(QWidget * parent)
  : QTabWidget(parent),
  	connection_settings_widget_(new UDPSettingsWidget)
{
    this->setTabBar(new HorizontalTabBar(this));
	this->setTabPosition(QTabWidget::TabPosition::West);
    this->setTabShape(QTabWidget::TabShape::Rounded);
	this->addTab(connection_settings_widget_, "Подключение");
	connect(connection_settings_widget_, SIGNAL(parameterUpdate(int, QVariant)), this, SIGNAL(connectionParameterUpdated(int, QVariant)));
}