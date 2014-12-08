#ifndef EEPROM_DEVICE_H
#define	EEPROM_DEVICE_H

#include "../../device/deviceDescriptor.h"
#include "../../common/eeprom/eeprom.h"

/**
* Returns a descriptor on the EEPROM device.
* @param eeprom_ the pointer on the eeprom device that we want to handle
* @return a pointer on the deviceDescriptor (which does the job hardwarely)
*/
DeviceDescriptor* getEepromDeviceDescriptor(Eeprom* eeprom_);

#endif