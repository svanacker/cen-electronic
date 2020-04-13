#ifndef PWM_MOTOR_DEVICE_H
#define PWM_MOTOR_DEVICE_H

#include "../../common/pwm/motor/dualHBridgeMotorPwm.h"

#include "../../device/deviceDescriptor.h"

/**
 * Returns a descriptor on the device for motors.
 */
DeviceDescriptor* getMotorDeviceDescriptor(DualHBridgeMotor* dualHBrideMotorParam);

/**
 * Method which must be called when the pin state change.
 * @param notificationOutputStream the outputStream to notify
 * @return true if we have notify
 */
bool motorDevicePinChangeNotify(OutputStream* notificationOutputStream);

#endif
