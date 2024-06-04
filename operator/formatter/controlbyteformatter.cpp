#include "controlbyteformatter.hpp"

ControlByteFormatter::ControlByteFormatter(char placeholder /*= 0xFF*/, char address_byte /*= 0x00*/, char data_byte /*= 0x01*/, int package_size /*= 22*/)
  : address_byte_(address_byte),
    data_byte_(data_byte),
    placeholder_(placeholder),
    packet_size_(package_size)
{}

/*
Действует только на ОТПРАВЛЯЕМЫЕ команды!

Перед каждым байтом добавляет дополнительный служебный байт,
после чего сообщение дополняется до packet_size_ байтов (по умолчанию 22), заполняясь значением,
сохраненным в поле placeholder_ (по умолчанию 0xFF)
*/
QByteArray ControlByteFormatter::formatCommand(QByteArray data)
{
    QByteArray source_command = data;
    data = QByteArray(std::max(packet_size_, source_command.size()), placeholder_);
    char byte;
    for(int i = 0; i < source_command.size(); ++i)
    {
        data[2 * i + 1] = source_command[i];  // 1, 3, 5, 7, ... байт (от нуля) - байты исходных данных
        if(i == 0)  // Первый байт - всегда адрес
        {
            byte = address_byte_;
        }
        else  // Последующие - всегда аргументы
        {
            byte = data_byte_;
        }
        data[2 * i] = byte;  // 0, 2, 4, 6, ... байт - служебные байты 
    }

    return data;
}