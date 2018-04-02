#ifndef PWM_MOTOR_DEVICE_H
#define PWM_MOTOR_DEVICE_H

#include "../../common/pwm/motor/dualHBridgeMotorPwm.h"

#include "../../device/deviceDescriptor.h"

/**
* Returns a descriptor on the device for motors.
*/
DeviceDescriptor* getMotorDeviceDescriptor(DualHBridgeMotor* dualHBrideMotorParam);

#endif
