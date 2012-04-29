#ifndef RELAY_DEVICE_INTERFACE_H
#define RELAY_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

#define COMMAND_RELAY 'R'

/**
* Interface for Relay Device
*/
DeviceInterface* getRelayDeviceInterface();

#endif

