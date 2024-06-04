#ifndef REQUEST_FORMATTER_HPP
#define REQUEST_FORMATTER_HPP

#include "basecommandformatter.hpp"
#include <algorithm>

class RequestFormatter : public BaseCommandFormatter
{
public:
    RequestFormatter(char placeholder = (char)0xFF, char address_byte = (char)0x02, int package_size = 22);
    QByteArray formatCommand(QByteArray data);
private:
    char address_byte_;  // Служебный байт, дописываемый перед адресным байтом
    char placeholder_;  // Байт, которым сообщение дополняется до 22 байт
    int packet_size_;  // Размер пакета данных
};

#endif

