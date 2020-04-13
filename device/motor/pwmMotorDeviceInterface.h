#ifndef PWM_MOTOR_DEVICE_INTERFACE_H
#define PWM_MOTOR_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/**
* Print debug inforamation about MOTOR
*/
#define COMMAND_DEBUG_MOTOR          'd'

/**
 * Defines the header to move the motor.
 */
#define COMMAND_MOVE_MOTOR         'w'

/**
 * Defines the header to move only the first motor (Left).
 * @return 
 */
#define COMMAND_MOVE_MOTOR_LEFT     'L'

/**
 * Defines the header to move only the second motor (Right).
 * @return 
 */
#define COMMAND_MOVE_MOTOR_RIGHT    'R'

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
 * Set the usage of each pin. 
 */
#define COMMAND_SET_PIN_USAGE_MOTOR  'p'

// NOTIFICATION

/**
 * Notification when a change was detected on PIN.
 */
#define NOTIFY_PIN_CHANGED           'n'

/**
 * Interface for Device.
 */
DeviceInterface* getMotorDeviceInterface();

#endif
