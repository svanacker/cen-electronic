#ifndef CLOCK_DEVICE_H
#define CLOCK_DEVICE_H

#include "../../common/clock/clock.h"

#include "../../device/deviceDescriptor.h"

/**
 * Returns a descriptor on the CLOCK device.
 * @param clock the pointer on the clock object.
 * @return a descriptor to handle with hardware the clock object.
 */
DeviceDescriptor* getClockDeviceDescriptor(Clock* clock);

#endif

