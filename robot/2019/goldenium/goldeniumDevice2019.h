#ifndef GOLDENIUM_DEVICE_2019_H
#define GOLDENIUM_DEVICE_2019_H

#include "../../../common/pwm/servo/servoList.h"

#include "../../../device/device.h"

#include "../../../drivers/tof/tofList.h"

/**
 * The descriptor for the Goldenium 2019 device.
 */
DeviceDescriptor* getGoldenium2019DeviceDescriptor(ServoList* servoList,
        TofSensorList* tofSensorListParam);


#endif
