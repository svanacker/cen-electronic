#ifndef STRATEGY_DEVICE_INTERFACE_H
#define STRATEGY_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

#define COMMAND_SET_OPPONENT_ROBOT_POSITION		'y'

#define COMMAND_SET_CONFIG		'Y'

/**
* Interface for Device
*/
DeviceInterface* getStrategyDeviceInterface();

#endif
