#ifndef COMMON_BEACON_DEVICE_H
#define COMMON_BEACON_DEVICE_H

#include "../../device/deviceDescriptor.h"

/**
 * Descriptor arround beacon common device (used by receiver and master).
 */
DeviceDescriptor* getCommonBeaconDeviceDescriptor();

/**
 * Returns if the command which are sent from the DEBUG serial port must be sent to
 * the internal devices (via the classical mechanism of one letter + hexadecimal argument)
 * or if we send directly command to the JENNIC
 */
BOOL isCommandRedirectToDevices();

/**
 * Redirects command to the Devices.
 */
void setCommandRedirectToDevices();

#endif
