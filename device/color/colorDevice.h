#ifndef COLOR_SENSOR_DEVICE_H
#define COLOR_SENSOR_DEVICE_H

#include "../../device/deviceDescriptor.h"

#include "../../drivers/colorSensor/colorSensor.h"

/**
 * The descriptor for the Color Sensor device.
 */
DeviceDescriptor* getColorSensorDeviceDescriptor(ColorSensor* colorSensor);

#endif
