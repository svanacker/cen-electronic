#ifndef SERVO_DEVICE_INTERFACE_H
#define SERVO_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

// Header for the device
#define SERVO_DEVICE_HEADER 					's'

// WRITE FUNCTIONS

// Command header for all arguments with servo index, speed, value
#define SERVO_COMMAND_WRITE						'w'

// Command header for compact method (all servo), only value
#define SERVO_COMMAND_WRITE_COMPACT				'c'

// READ FUNCTIONS

// Command header to read the speed of a servo with the specified index
#define SERVO_COMMAND_READ_SPEED				's'

// Command header to read the current Position of a servo with the specified index
#define SERVO_COMMAND_READ_CURRENT_POSITION		'p'

// Command header to read the target Position of a servo with the specified index
#define SERVO_COMMAND_READ_TARGET_POSITION		'r'

// DEBUG FUNCTIONS

// Command header to debug the servo list
#define SERVO_COMMAND_DEBUG						'd'

// Command header to do the test program
#define SERVO_COMMAND_TEST						't'

/**
* Interface for Servo Device.
*/
DeviceInterface* getServoDeviceInterface();

#endif

