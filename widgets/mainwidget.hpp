#ifndef MAIN_WIDGET_HPP
#define MAIN_WIDGET_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedLayout>

#include "subwidgets/horizontaltabbar.hpp"
#include "devices/base/basedevicewidget.hpp"

/*
Основной виджет приложения, отображающий виртуальные устройства в виде вкладок
*/

class MainWidget : public QTabWidget
{
Q_OBJECT
public:
    MainWidget(QWidget * parent = nullptr);
public slots:
    void addDevice(BaseDeviceWidget * device);  // Добавить виртуальное устройство
};

#endif