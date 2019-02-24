#ifndef ACCELEROMETER_DEVICE_H
#define ACCELEROMETER_DEVICE_H

#include "../../device/deviceDescriptor.h"

#include "../../common/sensor/accelerometer/accelerometer.h"

/**
* Returns a descriptor on the device for the Accelerometer.
* @return a descriptor on the device for the Accelerometer
*/
DeviceDescriptor* getAccelerometerDeviceDescriptor(Accelerometer* accelerometer);

#endif
