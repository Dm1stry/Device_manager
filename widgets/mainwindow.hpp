#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QApplication>

#include "sidemenuwidget.hpp"
#include "mainwidget.hpp"
#include "widgets/settingswidgets/settingswindow.hpp"
#include "base/basedevicewidget.hpp"
#include "universal/universaldevicewidget.hpp"
#include "programmer/programmerdevicewidget.hpp"
#include "rf/rfdevicewidget.hpp"
#include "samplepositioning/samplepositioningdevicewidget.hpp"
#include "adc/adcdevicewidget.hpp"
#include "operator/operator.hpp"

/*
Класс главного окна приложения
*/
class MainWindow : public QWidget
{
Q_OBJECT
public:
    MainWindow(Operator * operator_pointer, QWidget * parent = nullptr);
protected:
    void closeEvent(QCloseEvent *event);
private:
    inline void layoutSetup();  // Создает графическую структуру приложения

    SettingsWindow * settings_window_;  // Окно настроек

    SideMenuWidget * side_menu_widget_;  // Виджет бокового меню быстрых действий (запуск/остановка последовательности, натройки приложения)
    MainWidget * main_widget_;  // Основной виджет, отображает виджеты виртуальных устройств в виде вкладок

    Operator * operator_;  // Оператор
};

#endif
