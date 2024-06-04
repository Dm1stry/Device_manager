#include "sync_device_widget.hpp"

SyncDeviceWidget::SyncDeviceWidget(QString name, quint8 address, QFrame* parent):
name_(name),
address_(address),
QFrame(parent)
{
    this->layoutSetup();
    this->connectionSetup();
}

SyncDeviceWidget::~SyncDeviceWidget()
{

}

void SyncDeviceWidget::layoutSetup()
{
    this->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    this->setStyleSheet("background-color:rgb(240,240,240)");

    QHBoxLayout* main_layout = new QHBoxLayout;

    name_label_ = new QLabel(name_);

    check_box_ = new QCheckBox();

    settings_button_ = new QPushButton();
    QPixmap pixmap1(":/programmerdevice/devicewidget/gear-alt.svg");
    QIcon ButtonIcon1(pixmap1);
    settings_button_->setIcon(ButtonIcon1);
    settings_button_->setIconSize(QSize(20,20));
    settings_button_->setMaximumSize(25,24);
    settings_button_->setStyleSheet("QPushButton{background: rgb(240,240,240); border-radius: 5px; border:none;}"
                          "QPushButton:hover{background: rgb(210,210,210); border-radius: 5px; border:none;}"); 
    
    main_layout->addWidget(check_box_);
    main_layout->addWidget(name_label_);
    main_layout->addWidget(settings_button_);
    main_layout->setContentsMargins(5,5,5,5);

    main_layout->setStretch(0,1);
    main_layout->setStretch(1,15);
    main_layout->setStretch(2,1);

    this->setLayout(main_layout);
}

void SyncDeviceWidget::connectionSetup()
{
    connect(check_box_, SIGNAL(stateChanged(int)), this, SLOT(checkBoxClicked(int)));
    connect(settings_button_, &QPushButton::clicked, [=, this](){ emit settingDevice();});
}

void SyncDeviceWidget::checkBoxClicked(int state)
{
    if (state && !add){   // Если добавление таймлайна
        add = true;
        emit addDevice(name_, address_);

    } else if(!state) {   // Если удаление таймлайна
        QMessageBox::StandardButton reply;
        reply = QMessageBox::warning(this, "Внимание!", "Удалить таймлайн устройства?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            add = false;
            emit removeDevice(address_);

        } else {
            add = true;
            check_box_->setCheckState(Qt::Checked);

        }
    }
    
}
