#ifndef SERVO_DEVICE_H
#define SERVO_DEVICE_H

#include "../../common/pwm/servo/servoList.h"

#include "../../device/deviceDescriptor.h"

/**
 * The descriptor for the servo device.
 * @param servoList the list of servo to control
 */
DeviceDescriptor* getServoDeviceDescriptor(ServoList* servoList);

#endif
