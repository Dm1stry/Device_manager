#include "messenger.hpp"
#include <QDebug>

UdpMessenger::UdpMessenger(QWidget * parent)
  : QWidget(parent),
    main_layout_(new QVBoxLayout),
	ip_layout_(new QGridLayout),
	ip_self_label_(new QLabel("self IP:")),
	ip_self_edit_(new QLineEdit),
	ip_target_label_(new QLabel("target IP:")),
	ip_target_edit_(new QLineEdit),
    port_layout_(new QGridLayout),
    listen_port_label_(new QLabel("Слушать порт:")),
    listen_port_edit_(new QLineEdit),
	write_port_label_(new QLabel("Посылать в порт:")),
	write_port_edit_(new QLineEdit),
    chat_label_(new QLabel("Чат:")),
    chat_edit_(new QPlainTextEdit),
	message_layout_(new QGridLayout),
    message_label_(new QLabel("Сообщение:")),
    message_edit_(new QLineEdit),
	listen_port_(7575),
	write_port_(7576),
	self_ip_(QHostAddress("127.0.0.1")),
	target_ip_(QHostAddress("127.0.0.1")),
    send_message_button_(new QPushButton("Отправить")),
	udpSocket_(new QUdpSocket(this))
{
    //connect(send_message_button_, SIGNAL(clicked()), this, SLOT(sendBtnClicked()));
    chat_edit_->setReadOnly(true);

	ip_layout_->addWidget(ip_self_label_, 0, 0);
	ip_layout_->addWidget(ip_self_edit_, 0, 1);
	ip_layout_->addWidget(ip_target_label_, 1, 0);
	ip_layout_->addWidget(ip_target_edit_, 1, 1);
	main_layout_->addLayout(ip_layout_);

	port_layout_->addWidget(listen_port_label_, 0, 0);
	listen_port_edit_->setText(QString::number(listen_port_));
	port_layout_->addWidget(listen_port_edit_, 0, 1);
	port_layout_->addWidget(write_port_label_, 1, 0);
	write_port_edit_->setText(QString::number(write_port_));
	port_layout_->addWidget(write_port_edit_, 1, 1);

	main_layout_->addLayout(port_layout_);

	main_layout_->addWidget(chat_label_);
	main_layout_->addWidget(chat_edit_);

	message_layout_->addWidget(message_label_, 0, 0, 1, 3);
	message_layout_->addWidget(message_edit_, 1, 0, 1, 3);
	message_layout_->addWidget(send_message_button_, 2, 2, 1, 1);
	main_layout_->addLayout(message_layout_);

	this->setLayout(main_layout_);

	listenPortUpdated();
	writePortUpdated();

	connect(listen_port_edit_, &QLineEdit::editingFinished, this, &UdpMessenger::listenPortUpdated);
	connect(write_port_edit_, &QLineEdit::editingFinished, this, &UdpMessenger::writePortUpdated);
	connect(send_message_button_, &QPushButton::clicked, this, &UdpMessenger::sendBtnClicked);
	connect(message_edit_, &QLineEdit::returnPressed, this, &UdpMessenger::sendBtnClicked);
	connect(ip_self_edit_, &QLineEdit::editingFinished, this, &UdpMessenger::ipSelfUpdated);
	connect(ip_target_edit_, &QLineEdit::editingFinished, this, &UdpMessenger::ipTargetUpdated);
	connect(udpSocket_, SIGNAL(readyRead()), this, SLOT(messageArrived()));
}

void UdpMessenger::sendBtnClicked()
{
	QString msg = message_edit_->text();
	message_edit_->clear();
	if(!msg.isEmpty())
	{
		chat_edit_->insertPlainText("Вы: " + msg + "\n");
		udpSocket_->writeDatagram(msg.toLatin1(), msg.length(), target_ip_, write_port_);
	}
}

void UdpMessenger::messageArrived()
{

	while (udpSocket_->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket_->receiveDatagram();
	
		if(datagram.isValid())
        {
            QString msg= "сообщение: " + QString(datagram.data().toHex()).toUpper() + ", порт: " + QString::number(datagram.senderPort()) + "\n";
			//qDebug() << msg;
			chat_edit_->insertPlainText(msg);
        }
    }
}

void UdpMessenger::listenPortUpdated()
{
	listen_port_ = listen_port_edit_->text().toInt();
	udpSocket_->close();
	udpSocket_->abort();
	bool result = udpSocket_->bind(self_ip_, listen_port_);
	if(!result)
    {
        QMessageBox::information(this,"error","udp socket create error!");
    }
}

void UdpMessenger::writePortUpdated()
{
	write_port_ = (write_port_edit_->text()).toInt();
}

void UdpMessenger::ipSelfUpdated()
{
	self_ip_ = QHostAddress(ip_self_edit_->text());
	listenPortUpdated();
}

void UdpMessenger::ipTargetUpdated()
{
	target_ip_ = QHostAddress(ip_target_edit_->text());
}