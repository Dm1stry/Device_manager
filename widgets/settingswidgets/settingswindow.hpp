#ifndef SETTINGS_WINDOW_HPP
#define SETTINGS_WINDOW_HPP

#include <QTabWidget>
#include "subwidgets/horizontaltabbar.hpp"
#include "baseconnectionsettingswidget.hpp"
#include "udpsettingswidget.hpp"

class SettingsWindow : public QTabWidget
{
Q_OBJECT
public:
    SettingsWindow(QWidget * parent = nullptr);

signals:
    void connectionParameterUpdated(int, QVariant);

private:
    BaseConnectionSettingsWidget * connection_settings_widget_;

};

#endif