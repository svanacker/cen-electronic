#ifndef TOF_DEVICE_H
#define TOF_DEVICE_H

#include "../../drivers/tof/tofList.h"

#include "../../device/deviceDescriptor.h"

/**
* Returns the deviceDescriptor on a list of Time of Flight (TOF) Sensors.
*/
DeviceDescriptor* getTofDeviceDescriptor(TofSensorList* tofSensorList);

#endif


