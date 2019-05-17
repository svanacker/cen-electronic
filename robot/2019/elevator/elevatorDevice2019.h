#ifndef ELEVATOR_DEVICE_2019_H
#define ELEVATOR_DEVICE_2019_H

#include "../../../common/pwm/servo/servoList.h"

#include "../../../device/device.h"

/**
 * The descriptor for the Elevator 2019 device.
 */
DeviceDescriptor* getElevator2019DeviceDescriptor(ServoList* servoList);

#endif
