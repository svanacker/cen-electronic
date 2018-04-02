#ifndef IO_EXPANDER_DEVICE_H
#define IO_EXPANDER_DEVICE_H

#include "../../device/deviceDescriptor.h"

#include "../../drivers/ioExpander/ioExpander.h"

/**
 * The descriptor for the IO Expander device (typical device : PCF8574).
 */
DeviceDescriptor* getIOExpanderDeviceDescriptor(IOExpander* ioExpanderParam);

#endif
