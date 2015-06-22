#ifndef BATTERY_DEVICE_H
#define BATTERY_DEVICE_H

#include "../../drivers/battery/battery.h"

#include "../../device/deviceDescriptor.h"

/**
* Returns a descriptor on the Battery device.
* @param Battery the pointer on the battery object.
* @return a descriptor to handle with hardware the battery object.
*/
DeviceDescriptor* getBatteryDeviceDescriptor(Battery* battery);

#endif

