#ifndef LED_DEVICE_H
#define LED_DEVICE_H

#include "../../device/deviceDescriptor.h"

#include "../../drivers/led/led.h"

/**
 * The descriptor for the Led device.
 */
DeviceDescriptor* getLedDeviceDescriptor(LedArray* ledArray);

#endif
