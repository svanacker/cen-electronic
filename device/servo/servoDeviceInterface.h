#ifndef SERVO_DEVICE_INTERFACE_H
#define SERVO_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

// WRITE FUNCTIONS

// Command header for all arguments with servo index, speed, value
#define SERVO_COMMAND_WRITE                         'w'

// Command header for compact method (all servo), only value
#define SERVO_COMMAND_WRITE_COMPACT                 'c'

/** Enable a specific servo. */
#define SERVO_COMMAND_WRITE_ENABLE_DISABLE                'e'

// Command header to write the max speed under load
#define SERVO_COMMAND_WRITE_MAX_SPEED_UNDER_LOAD    'M'

// READ FUNCTIONS

// Command header to get the max speed under load
#define SERVO_COMMAND_READ_MAX_SPEED_UNDER_LOAD      'm'

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

/** Enable or disable all servos . */
#define SERVO_COMMAND_ENABLE_DISABLE_ALL            'E'

// Command header to debug the servo list
#define SERVO_COMMAND_DEBUG                         'd'

// Command header to do the test program
#define SERVO_COMMAND_TEST                          'T'

// Command to get the time in milliSeconds to reach the current position to a specified target position
#define SERVO_COMMAND_GET_TIME_TO_REACH_UNDER_LOAD  'L'

// SERVO INDEX
#define SERVO_ALL_INDEX                             0xFF

/**
 * Interface for Servo Device.
 */
DeviceInterface* getServoDeviceInterface(void);

#endif

