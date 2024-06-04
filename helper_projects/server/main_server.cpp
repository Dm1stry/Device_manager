#include <QApplication>
#include "server.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    UdpServer * server = new UdpServer();
    server->show(); 
    app.exec();
}