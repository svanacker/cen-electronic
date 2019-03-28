#ifndef CURRENT_SENSOR_DEVICE_H
#define CURRENT_SENSOR_DEVICE_H

#include "../../../common/sensor/current/current.h"

#include "../../../device/deviceDescriptor.h"

/**
* Returns a descriptor on the CurrentSensor device.
* @param current a wrapper on current device
*/
DeviceDescriptor* getCurrentSensorDeviceDescriptor(Current* current);

#endif    

