#ifndef BASE_CONNECTION_SETTINGS_WIDGET_HPP
#define BASE_CONNECTION_SETTINGS_WIDGET_HPP

#include <QWidget>

class BaseConnectionSettingsWidget : public QWidget
{
Q_OBJECT
public:
    BaseConnectionSettingsWidget(QWidget * parent = nullptr);
signals:
    void parameterUpdate(int, QVariant);
};

#endif