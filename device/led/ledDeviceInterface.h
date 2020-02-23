#ifndef LED_DEVICE_INTERFACE_H
#define LED_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"


#define COMMAND_LED_WRITE             'w'

/**
* Interface for Led Device.
*/
DeviceInterface* getLedDeviceInterface(void);

#endif

