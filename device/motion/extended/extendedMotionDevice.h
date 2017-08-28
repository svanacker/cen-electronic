#ifndef EXTENDED_MOTION_DEVICE_H
#define EXTENDED_MOTION_DEVICE_H

#include <stdbool.h>

#include "../../../common/io/outputStream.h"

#include "../../../device/deviceDescriptor.h"

#include "../../../motion/pid/pidMotion.h"

/**
* Returns a descriptor around extended motion (bspline).
* @param eeprom_ the eeprom to load the default speed and acceleration values
* @return a descriptor for motion device
*/
DeviceDescriptor* getExtendedMotionDeviceDescriptor(PidMotion* pidMotion);

#endif

