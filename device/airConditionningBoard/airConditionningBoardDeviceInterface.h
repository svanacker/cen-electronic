#ifndef AIR_CONDITIONNING_BOARD_DEVICE_INTERFACE_H
#define AIR_CONDITIONNING_BOARD_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

#define COMMAND_AIR_CONDITIONNING 'w'

/**
* Interface for Device
*/
DeviceInterface* getAirConditioningDeviceInterface();

#endif

