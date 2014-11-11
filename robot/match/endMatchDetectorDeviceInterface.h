#ifndef END_MATCH_DETECTOR_DEVICE_INTERFACE_H
#define END_MATCH_DETECTOR_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

#define END_MATCH_DETECTOR_DEVICE_HEADER        'e'

/**
* Defines the command send to notify the end of the match
*/
#define COMMAND_NOTIFY_MATCH_ENDED              'n'

/**
 * The interface for the device EndMatchDetectorDevice.
 */
DeviceInterface* getEndMatchDetectorDeviceInterface();

#endif
