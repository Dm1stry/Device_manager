#include "universaldevicewidget.hpp"
#include <QDebug>

UniversalDeviceWidget::UniversalDeviceWidget(QWidget * parent)
  : BaseDeviceWidget("Коммуникатор", parent),
    main_widget_(new QTabWidget),
    phys_address_edit_(new QLineEdit),
    commanding_history_edit_(new QPlainTextEdit),
    commanding_message_edit_(new QLineEdit),
    commanding_message_prefix_(new QLabel("0x00")),
    send_command_button_(new QPushButton("Отправить команду")),
    send_request_button_(new QPushButton("Отправить запрос")),
    send_raw_button_(new QPushButton("Отправить без обработки")),
    broadcast_history_edit_(new QPlainTextEdit),
    broadcast_message_edit_(new QLineEdit),
    send_broadcast_button_(new QPushButton("Отправить"))
{
    layoutSetup();  // Установка визуальной структуры

    address_ = 0;
    commanding_history_edit_->setReadOnly(true);  // Устанавливаем поле истории сообщений в режим только для чтения
    broadcast_history_edit_->setReadOnly(true); 
    phys_address_edit_->setText(QString::number(address_));
    phys_address_edit_->setInputMask("Hh");

    connect(phys_address_edit_, &QLineEdit::editingFinished, 
    [&](){
        address_ = (quint8(QByteArray::fromHex(phys_address_edit_->text().toUtf8()).front()));
        commanding_message_prefix_->setText("0x" + phys_address_edit_->text());
        });  // При изменении значения в поле ввода, меняет значение поля класса
    connect(send_command_button_, &QPushButton::clicked, [&](){sendCommand(commanding_message_edit_->text());});  // По нажатию на кнопку отправляет данные
    connect(send_request_button_, &QPushButton::clicked, this, &UniversalDeviceWidget::sendRequest);  // По нажатию на кнопку отправляет данные
    connect(send_raw_button_, &QPushButton::clicked, [&](){sendRaw(commanding_message_edit_->text());});  // По нажатию на кнопку отправляет данные
    connect(send_broadcast_button_, &QPushButton::clicked,  [&](){sendBroadcast(broadcast_message_edit_->text());});
    connect(broadcast_message_edit_, &QLineEdit::returnPressed, [&](){sendBroadcast(broadcast_message_edit_->text());});  // По нажатию на Enter отправляет сообщение
}

// Все пришедшие данные пописывает в конец истории сообщений, отображает
void UniversalDeviceWidget::processData(QByteArray data)
{
    commanding_history_edit_->appendPlainText("устройство: 0x" + QString(data.toHex()).toUpper());
}

void UniversalDeviceWidget::processBroadcast(QString command, QVector<double> arguments)
{
    QString args_string = " ";
    for(int i = 0; i < arguments.size(); ++i)
    {
        args_string.append(QString::number(arguments[i]) + " ");
    }
    broadcast_history_edit_->appendPlainText("Широковещательное сообщение: " + command + args_string);
}

// Возвращает данные о состоянии в виде вектора состояния
json UniversalDeviceWidget::getStateToSave()
{
    return json();  // Placeholder. TODO add normal realization
}

// Восстанавливает состояние класса из вектора состояния
bool UniversalDeviceWidget::restoreState(json state)
{
    return true;  // Placeholder. TODO add normal realization
}

// Новое сообщение дописывает в конец истории сообщений и отправляет сигнал, несущий это сообщение
void UniversalDeviceWidget::sendCommand(QString message)
{
    QByteArray encoded_message;
    encoded_message.push_back(address_);  // Добавляет в начало сообщения адрес устройства
    encoded_message.push_back(QByteArray::fromHex(message.toUtf8()));  // Преобразуем строку message из строки байт к байтам, например "7E613C" -> {0x7E, 0x61, 0x3C}, в виде символов char это будет, соотетственно {'~', 'a', '<'}
    commanding_history_edit_->appendPlainText("Пользователь (команда): 0x" + QString(encoded_message.toHex()).toUpper());  //Выводим отправленную строку в поле истории команд
    emit newCommand(encoded_message);  // Отправляет данные оператору (т.к. только оператор слушает эти сообщения)
}

void UniversalDeviceWidget::sendRequest()
{
    QByteArray encoded_message;
    encoded_message.push_back(address_);  // Добавляет в начало сообщения адрес устройства
    commanding_history_edit_->appendPlainText("Пользователь (запрос): 0x" + QString(encoded_message.toHex()).toUpper());  //Выводим отправленную строку в поле истории команд
    emit newRequest(encoded_message);  // Отправляет данные оператору (т.к. только оператор слушает эти сообщения)
}

void UniversalDeviceWidget::sendRaw(QString message)
{
    if(message.isEmpty())
        return;
    QByteArray encoded_message;
    encoded_message.push_back(QByteArray::fromHex(message.toUtf8()));  // Преобразуем строку message из строки байт к байтам, например "7E613C" -> {0x7E, 0x61, 0x3C}, в виде символов char это будет, соотетственно {'~', 'a', '<'}
    commanding_history_edit_->appendPlainText("Пользователь (данные): 0x"  + QString(encoded_message.toHex()).toUpper());
    emit newRawData(encoded_message);
}

void UniversalDeviceWidget::sendBroadcast(QString message)
{
    broadcast_history_edit_->appendPlainText("Пользователь: " + message);
    QStringList message_and_args = message.split(" ");
    message = message_and_args[0];
    QVector<double> args;
    args.reserve(message_and_args.size() - 1);
    for(auto arg = message_and_args.begin() + 1; arg < message_and_args.end();  ++arg)
    {
        args.push_back(arg->toDouble());
    }
    emit newBroadcast(message, args);
}


inline void UniversalDeviceWidget::layoutSetup()
{
    QVBoxLayout * main_layout  = new QVBoxLayout;

    QWidget * device_commanding_widget = new QWidget;

    main_widget_->addTab(device_commanding_widget, "Устройство");

    QVBoxLayout * main_device_commanding_widget_layout = new QVBoxLayout;

    // Далее добавляется срока найтройки физического адреса устройства
    QHBoxLayout * phys_adderss_layout = new QHBoxLayout;  //Располагаем также в линию
    QLabel * phys_adderss_label = new QLabel("Адрес физического\nустройства:");
    phys_adderss_layout->addWidget(phys_adderss_label);
    phys_adderss_layout->addWidget(new QLabel("0x"));
    phys_adderss_layout->addWidget(phys_address_edit_);
    main_device_commanding_widget_layout->addLayout(phys_adderss_layout);

    // Затем идет условный "Чат" - история сообщений, поле для ввода нового сообщения и кнопка для его отправки
    QVBoxLayout * chat_layout = new QVBoxLayout;
    QLabel * history_label = new QLabel("История:");
    QLabel * message_label = new QLabel("Сообщение:");
    QHBoxLayout * message_layout = new QHBoxLayout;
    QHBoxLayout * sending_buttons_layout  = new QHBoxLayout;
    chat_layout->addWidget(history_label);
    chat_layout->addWidget(commanding_history_edit_);
    chat_layout->addWidget(message_label);

    message_layout->addWidget(commanding_message_prefix_);
    message_layout->addWidget(commanding_message_edit_);
    chat_layout->addLayout(message_layout);
    //chat_layout->addWidget(send_command_button_);

    sending_buttons_layout->addWidget(send_command_button_);
    sending_buttons_layout->addWidget(send_request_button_);
    sending_buttons_layout->addWidget(send_raw_button_);
    chat_layout->addLayout(sending_buttons_layout);

    main_device_commanding_widget_layout->addLayout(chat_layout);

    device_commanding_widget->setLayout(main_device_commanding_widget_layout);

    QWidget * broadcast_widget = new QWidget;

    main_widget_->addTab(broadcast_widget,  "Широковещатель");

    QVBoxLayout * broadcast_chat_layout = new QVBoxLayout;
    QLabel * broadcast_history_label = new QLabel("История:");
    QLabel * broadcast_message_label = new QLabel("Сообщение:");
    QHBoxLayout * broadcast_message_layout = new QHBoxLayout;
    broadcast_chat_layout->addWidget(broadcast_history_label);
    broadcast_chat_layout->addWidget(broadcast_history_edit_);
    broadcast_chat_layout->addWidget(broadcast_message_label);
    broadcast_chat_layout->addWidget(broadcast_message_edit_);
    broadcast_chat_layout->addWidget(send_broadcast_button_);

    broadcast_widget->setLayout(broadcast_chat_layout);

    main_layout->addWidget(main_widget_);

    this->setLayout(main_layout);
}

//void UniversalDeviceWidget::updateHistory(QByteArray data)
//{}