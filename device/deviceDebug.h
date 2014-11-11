#ifndef DEVICE_DEBUG_H
#define DEVICE_DEBUG_H

#include "device.h"

#include "../common/commons.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

// DEBUG

/**
 * Print the device information.
 * @param outputStream the outputStream where we write debug information.
 * @param device the pointer on device for which we want to debug information.
 */
void printDevice(OutputStream* outputStream, const Device* device);

/**
 * Print the list of device.
 * @param outputStream the outputStream where we write debug information.
 */
void printDeviceList(OutputStream* outputStream);

#endif
