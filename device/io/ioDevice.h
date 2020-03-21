#ifndef IO_DEVICE_H
#define IO_DEVICE_H

#include "../../device/deviceDescriptor.h"

#include "../../common/io/pin.h"

/**
 * The descriptor for the IO Device.
 */
DeviceDescriptor* getIODeviceDescriptor(PinList* pinList);

#endif
