#ifndef UDP_SETTINGS_WIDGET_HPP
#define UDP_SETTINGS_WIDGET_HPP

#include <QFormLayout>
#include <QLineEdit>
#include <QIntValidator>
#include <QSettings>

#include "baseconnectionsettingswidget.hpp"
#include "operator/connection/udpconnection.hpp"
#include "helpers/ipvalidator.hpp"

class UDPSettingsWidget : public BaseConnectionSettingsWidget
{
Q_OBJECT
public:
    UDPSettingsWidget(QWidget * parent = nullptr);
private:
    inline void layoutSetup();

    QLineEdit * source_ip_edit_;
    QLineEdit * source_port_edit_;
    QLineEdit * destination_ip_edit_;
    QLineEdit * destination_port_edit_;
};

#endif