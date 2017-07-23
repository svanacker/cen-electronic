#ifndef PWM_MOTOR_DEVICE_INTERFACE_H
#define PWM_MOTOR_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/**
* Defines the header to move the motor.
*/
#define COMMAND_MOVE_MOTOR         'w'

/**
* Defines the header to move the motor.
*/
#define COMMAND_READ_MOTOR_VALUE   'r'

/**
* Defines the header to stop the motors.
*/
#define COMMAND_STOP_MOTOR         'c'

/**
 * Defines the header to test both motors but very quicly.
 */
#define COMMAND_SMALL_TEST_MOTOR    't'

/**
 * Defines the header to test both motors but in every sense.
 */
#define COMMAND_NORMAL_TEST_MOTOR    'T'

/**
* Interface for Device.
*/
DeviceInterface* getMotorDeviceInterface();

#endif
