#ifndef NAVIGATION_DEVICE_H
#define NAVIGATION_DEVICE_H

#include "../../device/deviceDescriptor.h"

#include "../../navigation/navigation.h"

/**
* Returns a descriptor on the Navigation device.
* @return a descriptor to handle with hardware the navigation object.
*/
DeviceDescriptor* getNavigationDeviceDescriptor(Navigation* navigationParam);

#endif

