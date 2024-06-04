#include "mainwidget.hpp"

#include <QPushButton>
#include <QLabel>

MainWidget::MainWidget(QWidget * parent)
  : QTabWidget(parent)
{
    this->setTabBar(new HorizontalTabBar());
    this->setTabPosition(QTabWidget::TabPosition::West);
    this->setTabShape(QTabWidget::TabShape::Rounded);
}

void MainWidget::addDevice(BaseDeviceWidget * device)
{
    this->addTab(device, device->getName());
}