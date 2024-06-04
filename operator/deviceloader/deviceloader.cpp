#include "deviceloader.hpp"

void DeviceLoader::setOperator(Operator * operator_pointer)
{
    operator_ = operator_pointer;
}

bool DeviceLoader::saveDevices()
{
    qDebug() << "DeviceLoader::saveDevices() called";
    return true;
}

bool DeviceLoader::loadDevices()
{
    qDebug() << " DeviceLoader::loadDevices() called";
    return true;
}