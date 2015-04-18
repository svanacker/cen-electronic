#ifndef DEVICE_USAGE_H
#define DEVICE_USAGE_H

#include "../device/device.h"
#include "../common/io/outputStream.h"

/**
 * Print the usage for a specific Device.
 * @param outputStream the output stream (normally a debug console) to write the content of usage
 */
void printDeviceUsage(OutputStream* outputStream, Device* device);

/**
* Print the usage of all devices usage.
* @param outputStream the output stream (normally a debug console) to write the content of usage
*/
void printDeviceListUsage(OutputStream* outputStream);

/**
* Print the usage of all notifications usage.
* @param outputStream the output stream (normally a debug console) to write the content of all notifications.
*/
void printDeviceListNotification(OutputStream* outputStream);

#endif
