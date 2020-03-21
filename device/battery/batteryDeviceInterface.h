#ifndef BATTERY_DEVICE_INTERFACE_H
#define BATTERY_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

// List of BATTERY COMMAND HEADER

/**
 * Defines the header to read the battery.
 */
#define COMMAND_READ_BATTERY         'r'

// Function to get the specific Device Interface

/**
 * Interface for Device.
 */
DeviceInterface* getBatteryDeviceInterface();

#endif
