#ifndef NAVIGATION_DEVICE_INTERFACE_H
#define NAVIGATION_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

// List of NAVIGATION COMMAND HEADER

// -> LOCATIONS

/**
* Defines the header to read how many location there is.
*/
#define COMMAND_NAVIGATION_LOCATION_COUNT        'c'

/**
 * Defines the header to get information about locations.
 */
#define COMMAND_NAVIGATION_GET_LOCATION          'l'

/**
 * Defines the header to add a new location.
 */
#define COMMAND_NAVIGATION_SET_LOCATION          'L'

/**
 * Defines the header to clear all location
 */
#define COMMAND_NAVIGATION_LOCATION_CLEAR        'd'

// Function to get the specific Device Interface

/**
* Interface for Device.
*/
DeviceInterface* getNavigationDeviceInterface(void);

#endif
