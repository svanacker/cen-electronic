#ifndef RELAY_DEVICE_INTERFACE_H
#define RELAY_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"


#define COMMAND_READ_RELAY             'r'

#define COMMAND_WRITE_RELAY            'w'

#define COMMAND_RELAY_DEBUG            'd'

/**
* Interface for Relay Device
*/
DeviceInterface* getRelayDeviceInterface(void);

#endif

