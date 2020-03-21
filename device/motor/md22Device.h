#ifndef MD22_DEVICE_H
#define MD22_DEVICE_H

#include "../../common/motor/dualHBridgeMotor.h"

#include "../../device/deviceDescriptor.h"

/**
 * Returns a descriptor on the device for MD22.
 */
DeviceDescriptor* getMD22DeviceDescriptor(DualHBridgeMotor* dualHBrideMotorParam);

#endif
