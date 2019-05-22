#ifndef MULTIPLEXER_DEVICE_H
#define MULTIPLEXER_DEVICE_H

#include "../../../device/deviceDescriptor.h"

#include "../../../drivers/i2c/multiplexer/multiplexer.h"
#include "../../../drivers/i2c/multiplexer/multiplexerList.h"

/**
 * The descriptor for the Multiplexer device (typical device : TCA9548A).
 */
DeviceDescriptor* getMultiplexerDeviceDescriptor(MultiplexerList* multiplexerList);

#endif
