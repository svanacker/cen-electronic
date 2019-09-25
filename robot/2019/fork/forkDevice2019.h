#ifndef FORK_DEVICE_2019_H
#define FORK_DEVICE_2019_H

#include "../../../common/pwm/servo/servoList.h"

#include "../../../device/device.h"

#include "../../../drivers/tof/tofList.h"

/**
 * The descriptor for the Fork 2019 device.
 */
DeviceDescriptor* getFork2019DeviceDescriptor(ServoList* servoList,
                                              TofSensorList* tofSensorListParam);


#endif
