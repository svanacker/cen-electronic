#ifndef TOF_DEVICE_H
#define TOF_DEVICE_H

#include "../../common/i2c/i2cBusConnectionList.h"

#include "../../device/deviceDescriptor.h"

/**
* Returns the deviceDescriptor of the Time of Flight (TOF) Detector.
*/
DeviceDescriptor* getTofDeviceDescriptor(I2cBusConnection* i2cBusConnection);

#endif


