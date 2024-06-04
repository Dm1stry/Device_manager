#include "server.hpp"
#include <QHostAddress>
#include <QUdpSocket>
#include <QDebug>

UdpServer::UdpServer(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("UDP Server"));
    /* Инициализируем каждый элемент управления */
    TimerLabel = new QLabel(tr("Сообщение:"));
    TextLineEdit = new QLineEdit();
    SendBtn = new QPushButton(tr("Отправить"));
    /* Устанавливаем макет */
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(TimerLabel);
    mainLayout->addWidget(TextLineEdit);
    mainLayout->addWidget(SendBtn);
    connect(SendBtn,SIGNAL(clicked()),this,SLOT(SendBtnClicked()));
    port = 7575;		// Устанавливаем параметр номера порта UDP
    udpSocket=new QUdpSocket;// Создаем QUdpSocket
}

void UdpServer::SendBtnClicked()
{
    QString msg =TextLineEdit->text();
    udpSocket->writeDatagram(msg.toLatin1(),msg.length(),QHostAddress::Broadcast,port);
}