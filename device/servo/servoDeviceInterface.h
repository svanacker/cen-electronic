#ifndef SERVO_DEVICE_INTERFACE_H
#define SERVO_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

// Header for the device
#define SERVO_DEVICE_HEADER 		's'

// Command header for all arguments with servo index, speed, value
#define INDEX_COMMAND_SERVO			'i'

// Command header for compact method (all servo), only value
#define COMPACT_COMMAND_SERVO		'c'

/**
* Interface for Servo Device
*/
DeviceInterface* getServoDeviceInterface();

#endif

