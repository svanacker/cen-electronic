#ifndef PID_DEVICE_H
#define PID_DEVICE_H

#include "../../../common/eeprom/eeprom.h"

#include "../../../device/deviceDescriptor.h"

/**
* Returns a descriptor on the device which manages the PID.
* @param pidPersistenceEeprom the object to store parametesr
* @param loadDefaultValues if we load into the eeprom the default Values (useful for pc simulation).
*/
DeviceDescriptor* getPIDDeviceDescriptor(Eeprom* pidPersistenceEeprom, bool loadDefaultValues);

#endif


