#include <iostream>
#include <QApplication>
#include <QLabel>
#include <QMessageBox>
#include <QStyleFactory>
#include "widgets/mainwindow.hpp"
#include "universal/universaldevicewidget.hpp"
#include "programmer/programmerdevicewidget.hpp"
#include "rf/rfdevicewidget.hpp"
#include "samplepositioning/samplepositioningdevicewidget.hpp"
#include "adc/adcdevicewidget.hpp"
#include "scheduler/schedulerdevicewidget.hpp"
#include <QToolBar>


int main(int argc, char * argv[])
{
    QApplication  app(argc, argv);

    //настройка размера шрифта приложения (нужно проверить на разных устройствах)
    QFont font;    // получаем шрифт
    font.setPixelSize(14);   
    QApplication::setFont(font);
    app.setStyleSheet("QLabel{font-size: 14px;}");
    //

    QCoreApplication::setOrganizationName("KFMS KFU");
    QCoreApplication::setApplicationName("Reditom Manager");
    QApplication::setStyle("Fusion");

    Operator * operator_pointer = new Operator();
    MainWindow * mainwindow = new MainWindow(operator_pointer);
    UniversalDeviceWidget * universal = new UniversalDeviceWidget;
    ProgrammerDeviceWidget * programmer = new ProgrammerDeviceWidget;
    RFDeviceWidget * rf = new RFDeviceWidget;
    SPDeviceWidget * spd = new SPDeviceWidget;
    SchedulerDeviceWidget * scheduler = new SchedulerDeviceWidget;
    //ADCDeviceWidget * adc = new ADCDeviceWidget;
    operator_pointer->addDevice(universal);
    operator_pointer->addDevice(programmer);
    operator_pointer->addDevice(rf);
    operator_pointer->addDevice(spd);
    operator_pointer->addDevice(scheduler);
    //operator_pointer->addDevice(adc);
    mainwindow->setWindowState(Qt::WindowMaximized); // comment this line if u no need of FullScreen on startup
    mainwindow->show();

    app.exec();
}
