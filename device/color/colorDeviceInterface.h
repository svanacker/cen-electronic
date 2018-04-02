#ifndef COLOR_DEVICE_INTERFACE_H
#define COLOR_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"


#define COMMAND_COLOR_SENSOR_READ             'r'
#define COMMAND_COLOR_SENSOR_DEBUG            'd'

/**
* Interface for Color Sensor Device.
*/
DeviceInterface* getColorSensorDeviceInterface(void);

#endif

