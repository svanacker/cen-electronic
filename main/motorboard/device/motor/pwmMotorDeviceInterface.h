#ifndef PWM_MOTOR_DEVICE_INTERFACE_H
#define PWM_MOTOR_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

/**
* Defines the header to move the motor.
*/
#define COMMAND_MOVE_MOTOR 'm'

/**
* Defines the header to stop the motors.
*/
#define COMMAND_STOP_MOTOR 'n'

/**
* Interface for Device
*/
DeviceInterface* getMotorDeviceInterface();

#endif
