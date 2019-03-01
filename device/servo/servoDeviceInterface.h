#ifndef SERVO_DEVICE_INTERFACE_H
#define SERVO_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

// WRITE FUNCTIONS

// Command header for all arguments with servo index, speed, value
#define SERVO_COMMAND_WRITE                         'w'

// Command header for compact method (all servo), only value
#define SERVO_COMMAND_WRITE_COMPACT                 'c'

// READ FUNCTIONS

// Command header to know the amount of Servo drivers
#define SERVO_COMMAND_GET_COUNT                     'n'

// Command header to read the speed, current Position, targetPosition of a servo with the specified index
#define SERVO_COMMAND_READ                          'r'

// Command header to read the speed of a servo with the specified index
#define SERVO_COMMAND_READ_SPEED                    's'

// Command header to read the current Position of a servo with the specified index
#define SERVO_COMMAND_READ_CURRENT_POSITION         'p'

// Command header to read the target Position of a servo with the specified index
#define SERVO_COMMAND_READ_TARGET_POSITION          't'

// DEBUG FUNCTIONS

/** Enable a specific servo. */
#define SERVO_COMMAND_ENABLE_DISABLE                'e'

/** Enable or disable all servos . */
#define SERVO_COMMAND_ENABLE_DISABLE_ALL            'E'

// Command header to debug the servo list
#define SERVO_COMMAND_DEBUG                         'd'

// Command header to do the test program
#define SERVO_COMMAND_TEST                          'T'

// SERVO INDEX
#define SERVO_ALL_INDEX                             0xFF

/**
* Interface for Servo Device.
*/
DeviceInterface* getServoDeviceInterface(void);

#endif

