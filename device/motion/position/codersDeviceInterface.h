#ifndef CODERS_DEVICE_INTERFACE_H
#define CODERS_DEVICE_INTERFACE_H

#include "../../../device/deviceInterface.h"

// COMMAND INTERFACE

// The command header to get the wheel position (left / right)
#define COMMAND_GET_WHEEL_POSITION 				'w'

// The command header to clear the coders value
#define COMMAND_CLEAR_CODERS 					'W'

// The command header to see the wheel position as debug info
#define COMMAND_DEBUG_GET_WHEEL_POSITION 		'^'

/**
* Get the coders interface
*/
DeviceInterface* getCodersDeviceInterface();

#endif
