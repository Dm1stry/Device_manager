#ifndef SIDE_MENU_WIDGET_HPP
#define SIDE_MENU_WIDGET_HPP

#include <QToolBar>
#include <QIcon>
#include "widgets/settingswidgets/settingswindow.hpp"

/*
Виджет бокового меню быстрых действий
*/

class SideMenuWidget : public QToolBar
{
Q_OBJECT
public:
    SideMenuWidget(SettingsWindow * settings_window = nullptr, QWidget * parent = nullptr);
    void setSettingsWindow(SettingsWindow * settings_window);
private:
    SettingsWindow * settings_window_;

    QIcon play_icon_;  // Иконка кнопки запуска последовательности
    QIcon pause_icon_;  // Иконка кнопки паузы 
    QIcon stop_icon_;  // Иконка кнопки остановки последовательности
    QIcon settings_icon_;  // Иконка настроек оператора
};

#endif