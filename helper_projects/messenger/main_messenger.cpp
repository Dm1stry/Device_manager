#include <QApplication>
#include "messenger.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    UdpMessenger * messenger = new UdpMessenger();
    messenger->show(); 
    app.exec();
}