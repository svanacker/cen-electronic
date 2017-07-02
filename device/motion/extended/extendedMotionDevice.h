#ifndef EXTENDED_MOTION_DEVICE_H
#define EXTENDED_MOTION_DEVICE_H

#include <stdbool.h>

#include "../../../common/eeprom/eeprom.h"

#include "../../../device/deviceDescriptor.h"
#include "../../../common/io/outputStream.h"

/**
* Returns a descriptor around extended motion (bspline).
* @param eeprom_ the eeprom to load the default speed and acceleration values
* @param loadDefaultValues if we load the default values into the eeprom (useful for pc simulation)
* @return a descriptor for motion device
*/
DeviceDescriptor* getExtendedMotionDeviceDescriptor(Eeprom* eeprom_, bool loadDefaultValues);

#endif

