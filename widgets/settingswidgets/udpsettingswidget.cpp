#include "udpsettingswidget.hpp"

UDPSettingsWidget::UDPSettingsWidget(QWidget * parent /*= nullptr*/)
  : BaseConnectionSettingsWidget(parent),
    source_ip_edit_(new QLineEdit),
    source_port_edit_(new QLineEdit),
    destination_ip_edit_(new QLineEdit),
    destination_port_edit_(new QLineEdit)
{
    layoutSetup();

    constexpr int port_max_value = 65535;
    IPValidator * ip_validator = new IPValidator(this);
    QIntValidator * port_validator = new QIntValidator(0, port_max_value, this);

    source_port_edit_->setValidator(port_validator);
    destination_port_edit_->setValidator(port_validator);
    source_ip_edit_->setValidator(ip_validator);
    destination_ip_edit_->setValidator(ip_validator);

    QSettings settings;

    source_ip_edit_->setText(settings.value(SOURCE_IP_SETTING, DEFAULT_SOURCE_IP).toString());
    source_port_edit_->setText(settings.value(SOURCE_PORT_SETTING, DEFAULT_SOURCE_PORT).toString());
    destination_ip_edit_->setText(settings.value(DESTINATION_IP_SETTING, DEFAULT_DESTINATION_IP).toString());
    destination_port_edit_->setText(settings.value(DESTINATION_PORT_SETTING, DEFAULT_DESTINATION_PORT).toString());

    connect(source_ip_edit_, &QLineEdit::editingFinished, [&](){
        emit parameterUpdate(UDPConnection::Parameter::SOURCE_IP, source_ip_edit_->text());
    });
    connect(source_port_edit_, &QLineEdit::editingFinished, [&](){
        emit parameterUpdate(UDPConnection::Parameter::SOURCE_PORT, QVariant(source_port_edit_->text().toUShort()));
    });
    connect(destination_ip_edit_, &QLineEdit::editingFinished, [&](){
        emit parameterUpdate(UDPConnection::Parameter::DESTINATION_IP, destination_ip_edit_->text());
    });
    connect(destination_port_edit_, &QLineEdit::editingFinished, [&](){
        emit parameterUpdate(UDPConnection::Parameter::DESTINATION_PORT, QVariant(destination_port_edit_->text().toUShort()));
    });
}

inline void UDPSettingsWidget::layoutSetup()
{
    QFormLayout * main_layout = new QFormLayout;

    main_layout->addRow("IP компьютера", source_ip_edit_);
    main_layout->addRow("Порт компьютера", source_port_edit_);
    main_layout->addRow("IP устройства", destination_ip_edit_);
    main_layout->addRow("Порт устройства", destination_port_edit_);

    this->setLayout(main_layout);
}