#ifndef IO_EXPANDER_DEVICE_H
#define IO_EXPANDER_DEVICE_H

#include "../../device/deviceDescriptor.h"

#include "../../drivers/ioExpander/ioExpander.h"
#include "../../drivers/ioExpander/ioExpanderList.h"

/**
 * The descriptor for the IO Expander device (typical device : PCF8574).
 */
DeviceDescriptor* getIOExpanderDeviceDescriptor(IOExpanderList* ioExpanderList);

#endif
