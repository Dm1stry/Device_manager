#ifndef CONTROL_BYTE_FORMATTER_HPP
#define CONTROL_BYTE_FORMATTER_HPP

#include "basecommandformatter.hpp"

/*
Класс для форматирования данных
Добавляет перед каждым байтом четырехбайтовой команды контрольные байты

*/

class ControlByteFormatter : public BaseCommandFormatter
{
public:
    ControlByteFormatter(char placeholder = (char)0xFF, char address_byte = (char)0x00, char data_byte = (char)0x01, int package_size = 22);  // Конструктор
    QByteArray formatCommand(QByteArray data);  // Форматирует данные
private:
    char address_byte_;  // Служебный байт, дописываемый перед адресным байтом
    char data_byte_;  // Служебный байт, дописываемый перед байтом данных
    char placeholder_;  // Байт, которым сообщение дополняется до 22 байт
    int packet_size_;  // Размер пакета данных
};

#endif