#ifndef MOTION_SIMULATION_DEVICE_INTERFACE_H
#define MOTION_SIMULATION_DEVICE_INTERFACE_H

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

// COMMANDS

#define COMMAND_MOTION_SIMULATION_GET   'r'

#define COMMAND_MOTION_SIMULATION_SET   'w'

/**
* Interface for Device
*/
DeviceInterface* getMotionSimulationDeviceInterface();

#endif
