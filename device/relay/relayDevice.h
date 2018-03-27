#ifndef RELAY_DEVICE_H
#define RELAY_DEVICE_H

#include "../../device/deviceDescriptor.h"

#include "../../drivers/relay/relay.h"

/**
 * The descriptor for the relay device.
 */
DeviceDescriptor* getRelayDeviceDescriptor(Relay* relay);

#endif
