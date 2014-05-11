#ifndef PWM_MOTOR_DEVICE_INTERFACE_H
#define PWM_MOTOR_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

/**
 * Defines the header char used to identify the motor Device.
 */
#define MOTOR_DEVICE_HEADER 	'm'

/**
* Defines the header to move the motor.
*/
#define COMMAND_MOVE_MOTOR 		'w'

/**
* Defines the header to stop the motors.
*/
#define COMMAND_STOP_MOTOR 		'c'

/**
* Interface for Device.
*/
DeviceInterface* getMotorDeviceInterface();

#endif
