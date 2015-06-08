#ifndef TEMPERATURE_SENSOR_DEVICE_H
#define TEMPERATURE_SENSOR_DEVICE_H

#include "../../../common/sensor/temperature/temperature.h"

#include "../../../device/deviceDescriptor.h"

/**
* Returns a descriptor on the TemperatureSensor device.
* @param temperature a wrapper on temperature device
*/
DeviceDescriptor* getTemperatureSensorDeviceDescriptor(Temperature* temperature);

#endif    

