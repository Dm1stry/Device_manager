#include <QNetworkDatagram>
#include <QUdpSocket>

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include <QMessageBox>
#include <QApplication>


class UdpMessenger : public QWidget
{
Q_OBJECT
public:
    UdpMessenger(QWidget * parent = nullptr);
private slots:
    void sendBtnClicked();
    void messageArrived();
    void listenPortUpdated();
    void writePortUpdated();
    void ipSelfUpdated();
    void ipTargetUpdated();
private:
    QVBoxLayout * main_layout_;
    QGridLayout * ip_layout_;
    QLabel * ip_self_label_;
    QLineEdit * ip_self_edit_;
    QLabel * ip_target_label_;
    QLineEdit * ip_target_edit_;
    QGridLayout * port_layout_;
    QLabel * listen_port_label_;
    QLineEdit * listen_port_edit_;
    QLabel * write_port_label_;
    QLineEdit * write_port_edit_;
    QLabel * chat_label_;
    QPlainTextEdit * chat_edit_;
    QGridLayout * message_layout_;
    QLabel * message_label_;
    QLineEdit * message_edit_;
    QPushButton * send_message_button_;

    int listen_port_;
    int write_port_;
    QHostAddress self_ip_;
    QHostAddress target_ip_;
    QUdpSocket *udpSocket_;
};