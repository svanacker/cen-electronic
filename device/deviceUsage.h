#ifndef DEVICE_USAGE_H
#define DEVICE_USAGE_H

#include "../device/device.h"
#include "../common/io/outputStream.h"

/**
 * Print the usage for a specific Device.
 * @param outputStream the output stream (normally a debug console) to write the content of usage
 * @param showOnlyProblem show only problem to fix it easily !
 */
void printDeviceUsage(OutputStream* outputStream, Device* device, bool showOnlyProblem);

/**
 * Print the usage of all devices usage.
 * @param outputStream the output stream (normally a debug console) to write the content of usage
 * @param showOnlyProblem show only problem to fix it easily !
 */
void printDeviceListUsage(OutputStream* outputStream, bool showOnlyProblem);

/**
 * Print the usage of all notifications usage.
 * @param outputStream the output stream (normally a debug console) to write the content of all notifications.
 * @param showOnlyProblem show only problem to fix it easily !
 */
void printDeviceListNotification(OutputStream* outputStream, bool showOnlyProblem);

#endif
