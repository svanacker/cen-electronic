#ifndef COLOR_DEVICE_INTERFACE_H
#define COLOR_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"


#define COMMAND_COLOR_SENSOR_READ             'r'
#define COMMAND_COLOR_SENSOR_DEBUG            'd'
#define COMMAND_COLOR_SENSOR_READ_TYPE        't'

// Only for PC !
#define COMMAND_COLOR_SENSOR_WRITE            'w'

/**
* Interface for Color Sensor Device.
*/
DeviceInterface* getColorSensorDeviceInterface(void);

#endif

