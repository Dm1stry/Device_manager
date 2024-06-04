#ifndef DEVICE_LOADER_HPP
#define DEVICE_LOADER_HPP

#include "operator/operator.hpp"

class DeviceLoader
{
public:
    void setOperator(Operator * operator_pointer);
    virtual bool saveDevices();
    virtual bool loadDevices();
private:
    Operator * operator_;
};

#endif