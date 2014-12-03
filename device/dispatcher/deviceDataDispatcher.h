#ifndef DEVICE_DATA_DISPATCHER_H
#define DEVICE_DATA_DISPATCHER_H

#include "../device.h"

/**
 * Returns the length of the data which corresponds to the header.
 * @param header the length of the header
 * @return -1 if we don't find any corresponding header, else the header length
 */
unsigned int getWaitedDataLength(const char header);

/**
* Find the device associated with the specified data header.
* @param deviceHeader the device header (to select device)
* @param commandHeader the command header (to select command inside device)
* @param dataLength the length of the InBuffer
* @param mode DEVICE_MODE_INPUT ou DEVICE_MODE_OUTPUT, if we want to find a device
* by the INPUT (command) or OUTPUT (notification)
* @return the descriptor of the handling device, NULL if no registered device 
* can handle the data header
*/
const Device* deviceDataDispatcherFindDevice(const char deviceHeader, const char commandHeader, int dataLength, int mode);

#endif
