#ifndef TEMPERATURE_SENSOR_DEVICE_INTERFACE_H
#define	TEMPERATURE_SENSOR_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

// The TEMPERATURE SENSOR DEVICE HEADER

#define TEMPERATURE_SENSOR_DEVICE_HEADER     'T'

// List of TEMPERATURE SENSOR COMMAND HEADER

/**
* Defines the header to read the temperature sensor
*/

#define COMMAND_READ_TEMPERATURE_SENSOR         'r'

/**
* Defines the header to set the temperature sensor Alert 
*/

#define COMMAND_SET_TEMPERATURE_SENSOR_ALERT         'a'

/**
* Interface for Device.
*/
DeviceInterface* getTemperatureSensorDeviceInterface();

#endif	

