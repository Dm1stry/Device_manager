#include "sidemenuwidget.hpp"

SideMenuWidget::SideMenuWidget(SettingsWindow * settings_window /*= nullptr*/, QWidget * parent /*= nullptr*/)
  : QToolBar(parent),
  	settings_window_(settings_window),
  	play_icon_(":/icons/play_button.svg"),
	pause_icon_(":/icons/pause_button.svg"),
	stop_icon_(":/icons/stop_button.svg"),
	settings_icon_(":/icons/settings_button.svg")
{
	this->setOrientation(Qt::Orientation::Vertical);
	//this->addAction(play_icon_, "Play");
	//this->addAction(pause_icon_, "Pause");
	//this->addAction(stop_icon_, "Stop");
	QWidget* empty = new QWidget();
	empty->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
	this->addWidget(empty);
	this->addSeparator();
	this->addAction(settings_icon_, "Settings", [&](){
		if(settings_window_)
		{
			settings_window_->show();
		}
	});

}

void SideMenuWidget::setSettingsWindow(SettingsWindow * settings_window)
{
	settings_window_ = settings_window;
}