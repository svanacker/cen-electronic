#ifndef AIR_CONDITIONING_DEVICE_INTERFACE_H
#define AIR_CONDITIONING_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

#define AIR_CONDITIONING_DEVICE_HEADER 		'g'

#define AIR_CONDITIONING_COMMAND_WRITE  	'w'

#define AIR_CONDITIONING_COMMAND_ON  		'o'

#define AIR_CONDITIONING_COMMAND_OFF  		'f'

/**
* Interface for Air Conditioning Device.
*/
DeviceInterface* getAirConditioningDeviceInterface();

#endif

