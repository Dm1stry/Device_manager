#ifndef RF_DEVICE_WIDGET_HPP
#define RF_DEVICE_WIDGET_HPP

#include "devices/base/basedevicewidget.hpp"
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QPlainTextEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <cmath>
#include <cstring>
#include <stdint.h>

class RFDeviceWidget : public BaseDeviceWidget
{
Q_OBJECT
public:
    RFDeviceWidget(QWidget * parent = nullptr);
    
    // ---------------------------------------------------
    // Реализация метода, обрабатывающего пришедшие данные
    void processData(QByteArray data);
    // -------------------------------

    // -------------------------------------------------------------------------------------------------------------
    // BaseSavable методы, позволяющие получить данные для сохранения класса и 
    // восстановить состояние класса из сохраненных данных, 
    // необходимо для функционирования DeviceLoader
    
    // Возвращает данные о состоянии в виде вектора состояния
    json getStateToSave();
    // Восстанавливает состояние класса из вектора состояния
    bool restoreState(json state);
    // ------------------------------------------

private slots:
    void setFreq();
    void setChannel(int n);
    void setPulseChannel();
    void setDuration();
    void setPhase();
    void startPulse();
private:
    inline void layoutSetup();

    
    QSpinBox ch_spnbox[4];
    QLineEdit setfreq_ln[4];

    QSpinBox pls_channel_;

    QPushButton * setfreq_btn_;

    QLineEdit * rfp_dur_ln_;
    QLineEdit * rfp_ph_ln_;
    QPushButton * rfp_btn_;


    QPlainTextEdit * rf_chat_;

    double channel_;
    double freq_;
    double duration_;
    double phase_;
};

#endif
