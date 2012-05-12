#ifndef DEVICE_DEBUG_H
#define DEVICE_DEBUG_H

#include "device.h"

#include "../common/commons.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

// DEBUG

/**
 * Print the device information.
 */
void printDevice(OutputStream* outputStream, const Device* device);

#endif
