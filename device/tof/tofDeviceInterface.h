#ifndef TOF_DEVICE_INTERFACE_H
#define TOF_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Command header to get the sonar value. */
#define COMMAND_TOF_GET_DISTANCE      'r'

/** Command header to change the address. */
#define COMMAND_TOF_CHANGE_ADDRESS    '@'

/**
* Interface for Device "Time of Flight".
*/
DeviceInterface* getTofDeviceInterface();

#endif
