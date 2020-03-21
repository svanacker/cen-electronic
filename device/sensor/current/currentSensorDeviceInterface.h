#ifndef CURRENT_SENSOR_DEVICE_INTERFACE_H
#define CURRENT_SENSOR_DEVICE_INTERFACE_H

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

// List of CURRENT SENSOR COMMAND HEADER

/**
 * Defines the header to read the temperature sensor
 */

#define COMMAND_READ_CURRENT_SENSOR         'r'

/**
 * Defines the header to set the temperature sensor Alert 
 */
#define COMMAND_SET_CURRENT_SENSOR_ALERT    'w'

/**
 * Interface for Device.
 */
DeviceInterface* getCurrentSensorDeviceInterface(void);

#endif    

