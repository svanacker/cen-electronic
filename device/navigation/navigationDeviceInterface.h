#ifndef NAVIGATION_DEVICE_INTERFACE_H
#define NAVIGATION_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

// List of NAVIGATION COMMAND HEADER

// -> LOCATIONS

/**
* Defines the header to read how many locations there are.
*/
#define COMMAND_NAVIGATION_LOCATION_COUNT        'c'

/**
 * Defines the header to get information about a specific location.
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

// -> PATHS

/**
* Defines the header to read how many paths there are.
*/
#define COMMAND_NAVIGATION_PATH_COUNT        'C'

/**
* Defines the header to get information about a specific path.
*/
#define COMMAND_NAVIGATION_GET_PATH          'p'

/**
* Defines the header to add a new path.
*/
#define COMMAND_NAVIGATION_SET_PATH          'P'

/**
* Defines the header to clear all paths.
*/
#define COMMAND_NAVIGATION_PATH_CLEAR        '_'

// Function to get the specific Device Interface

/**
* Interface for Device.
*/
DeviceInterface* getNavigationDeviceInterface(void);

#endif
