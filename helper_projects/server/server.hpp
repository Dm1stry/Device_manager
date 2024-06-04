#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QUdpSocket>

class UdpServer : public QWidget
{
Q_OBJECT
public:
    UdpServer(QWidget *parent = 0);
public slots:
    void SendBtnClicked();
private:
    QLabel *TimerLabel;
    QLineEdit *TextLineEdit;
    QPushButton *SendBtn;
    QVBoxLayout *mainLayout;
    int port;
    QUdpSocket *udpSocket;
};

#endif // UDPSERVER_H