#ifndef TEST_DEVICE_H
#define TEST_DEVICE_H

#include "../../device/deviceDescriptor.h"

/**
 * The descriptor for the test device.
 * @return The descriptor for the test device
 */
DeviceDescriptor* getTestDeviceDescriptor();

/**
 * Notify a test.
 * @param outputStream the stream in which we notify
 * @param the value to notify
 */
void notifyTest(OutputStream* outputStream, unsigned char notifyArgument);

#endif
