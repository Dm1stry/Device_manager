#include "client.hpp"
#include <QUdpSocket>
#include <QMessageBox>
#include <QHostAddress>
#include <QNetworkDatagram>

UdpClient::UdpClient(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("UDP Client"));		// Устанавливаем заголовок формы
    ReceiveTextEdit = new QTextEdit(this);
    CloseBtn = new QPushButton(tr("Закрыть"),this);
    mainLayout=new QVBoxLayout(this);
    mainLayout->addWidget(ReceiveTextEdit);
    mainLayout->addWidget(CloseBtn);
    connect(CloseBtn,SIGNAL(clicked()),this,SLOT(CloseBtnClicked()));
    port = 7575;                             // Устанавливаем параметр номера порта UDP, указываем для мониторинга данных по этому порту
    udpSocket = new QUdpSocket(this);		// Создаем QUdpSocket
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    bool result=udpSocket->bind(port);// Привязать порт
    if(!result)
    {
        QMessageBox::information(this,"error","udp socket create error!");
        return;
    }
}

UdpClient::~UdpClient()
{

}

void UdpClient::CloseBtnClicked()
{
    close();
}

void UdpClient::dataReceived()
{
    while(udpSocket->hasPendingDatagrams())// Есть дейтаграмма для чтения
    {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();

        if(datagram.isValid())
        {
            QString msg= "Сообщение: " + QString(datagram.data()) + ", порт: " + QString::number(datagram.senderPort()) + "\n";
            ReceiveTextEdit->insertPlainText(msg);
        }
        
        
    }
}