#ifndef END_MATCH_DETECTOR_DEVICE_INTERFACE_H
#define END_MATCH_DETECTOR_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"


/**
* Defines the command send to notify the end of the match
*/
#define COMMAND_NOTIFY_MATCH_ENDED 'e'

/**
 * The interface for the device EndMatchDetectorDevice.
 */
DeviceInterface* getEndMatchDetectorDeviceInterface();

#endif
