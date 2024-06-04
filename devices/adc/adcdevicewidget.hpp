#ifndef ADC_DEVICE_WIDGET_HPP
#define ADC_DEVICE_WIDGET_HPP

#include "operator/operator.hpp"
#include "devices/base/basedevicewidget.hpp"
#include "ui_adcdevicewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ADCDeviceWidget; }
QT_END_NAMESPACE

/*
*   Виджет устройства АЦП.
*/

class ADCDeviceWidget : public BaseDeviceWidget
{
Q_OBJECT
public:
    ADCDeviceWidget(QWidget * parent = nullptr);
    ~ADCDeviceWidget();
    virtual void processData(QByteArray data) {};
    
    void setOperator(Operator * op); 


    // Возвращает данные о состоянии в виде вектора состояния
    json getStateToSave();
    // Восстанавливает состояние класса из вектора состояния
    bool restoreState(json state);
    // ------------------------------------------

    void signal_imitation(); //<- delete

private slots:

    void on_plot_clicked();
    void on_clear_clicked();
    void on_start_toggled(bool checked);

private:
    BaseConnection * connection_;  //Хранит подключение (сокет, порты и адрес)
    Ui::ADCDeviceWidget *ui;
};

#endif
