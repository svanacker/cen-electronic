#ifndef PID_DEBUG_DEVICE_H
#define PID_DEBUG_DEVICE_H

#include "../../../common/eeprom/eeprom.h"

#include "../../../device/deviceDescriptor.h"

#include "../../../motion/pid/pidMotion.h"

/**
* Returns a descriptor on the device which manages the Debug of the PID.
* @param pidMotion the object to store parametesr
*/
DeviceDescriptor* getPidDebugDeviceDescriptor(PidMotion* pidMotion);

#endif


