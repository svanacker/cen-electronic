#ifndef BEACON_RECEIVER_DEVICE_H
#define BEACON_RECEIVER_DEVICE_H

#include "../../device/deviceDescriptor.h"

unsigned char getNetworkStatus();

void setNetworkStatus(unsigned char aNetworkStatus);

/**
 * The descriptor for the beacon receiver device.
 */
DeviceDescriptor* getBeaconReceiverDeviceDescriptor();

#endif
