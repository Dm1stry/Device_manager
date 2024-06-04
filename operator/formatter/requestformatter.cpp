#include "requestformatter.hpp"

RequestFormatter::RequestFormatter(char placeholder /*= (char)0xFF*/, char address_byte /*= (char)0x02*/, int package_size /*= 22*/)  // Конструктор
  : address_byte_(address_byte),
    placeholder_(placeholder),
    packet_size_(package_size)
{}

// Форматирует данные
QByteArray RequestFormatter::formatCommand(QByteArray data)
{
    char source_command = data[0];
    data = QByteArray(packet_size_, placeholder_);
    data[0] = address_byte_;
    data[1] = source_command;

    return data;
}