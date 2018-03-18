#ifndef PC_DEVICE_H
#define PC_DEVICE_H

#include "../../common/io/outputStream.h"

#include "../../device/deviceDescriptor.h"

/**
 * The descriptor for the pc device (pipe ...)
 * @param outputStream the Stream in which we will write the content of the read file.
 */
DeviceDescriptor* getPcDeviceDescriptor(OutputStream* outputStream);

#endif
