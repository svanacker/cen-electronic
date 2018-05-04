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
#define COMMAND_NAVIGATION_GET_LOCATION          'r'

/**
 * Defines the header to add a new location or replace an existing one (if it has the same name).
 */
#define COMMAND_NAVIGATION_SET_LOCATION          'w'

/**
 * Defines the header to clear all location
 */
#define COMMAND_NAVIGATION_LOCATION_CLEAR        'k'

 /**
 * Defines the header to list all location.
 */
#define COMMAND_NAVIGATION_LOCATION_LIST_DEBUG        'd'

/**
 * Add some test data (to avoid to fill them manually).
 */
#define COMMAND_NAVIGATION_LOCATION_ADD_TESTS_DATA       't'

// -> PATHS

/**
* Defines the header to read how many paths there are.
*/
#define COMMAND_NAVIGATION_PATH_COUNT        'C'

/**
* Defines the header to get information about a specific path.
*/
#define COMMAND_NAVIGATION_GET_PATH          'R'

/**
* Defines the header to add a new path or replace an existing one (if it has the same name).
*/
#define COMMAND_NAVIGATION_SET_PATH          'W'

/**
* Defines the header to clear all paths.
*/
#define COMMAND_NAVIGATION_PATH_CLEAR        'K'

/**
* Defines the header to list all paths.
*/
#define COMMAND_NAVIGATION_PATH_LIST_DEBUG     'D'

/**
* Add some test data (to avoid to fill them manually).
*/
#define COMMAND_NAVIGATION_PATH_LIST_ADD_TESTS_DATA       'T'

// Function to get the specific Device Interface

/**
* Interface for Device.
*/
DeviceInterface* getNavigationDeviceInterface(void);

#endif
