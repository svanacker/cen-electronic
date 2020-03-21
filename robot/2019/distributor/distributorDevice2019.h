#ifndef DISTRIBUTOR_DEVICE_2019_H
#define DISTRIBUTOR_DEVICE_2019_H

#include "../../../common/pwm/servo/servoList.h"

#include "../../../device/device.h"

#include "../../../drivers/tof/tofList.h"

/**
 * The descriptor for the Distributor 2019 device.
 */
DeviceDescriptor* getDistributor2019DeviceDescriptor(ServoList* servoList,
        TofSensorList* tofSensorListParam);


#endif
