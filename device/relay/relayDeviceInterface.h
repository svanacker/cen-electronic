#ifndef RELAY_DEVICE_INTERFACE_H
#define RELAY_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

#define COMMAND_SET_RELAY             'w'

/**
* Interface for Relay Device
*/
DeviceInterface* getRelayDeviceInterface();

#endif

