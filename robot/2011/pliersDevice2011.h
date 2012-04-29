#ifndef PLIERS_DEVICE_2011_H
#define PLIERS_DEVICE_2011_H

#include "../../device/device.h"

void stopPlier(int index);

/**
 * The descriptor for the servo device.
 */
DeviceDescriptor* getPliers2011DeviceDescriptor();

#endif
