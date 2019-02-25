#ifndef SERVO_DEVICE_H
#define SERVO_DEVICE_H

#include "../../device/deviceDescriptor.h"

#include "../../common/pwm/servo/servoList.h"

/**
 * The descriptor for the servo device.
 */
DeviceDescriptor* getServoDeviceDescriptor(ServoList* servoList);

#endif
