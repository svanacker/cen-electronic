#ifndef END_MATCH_DETECTOR_DEVICE_INTERFACE_H
#define END_MATCH_DETECTOR_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

// Commands

/**
 * Defines the command send to debug the End Match Detector Device
 */
#define COMMAND_END_MATCH_DETECTOR_DEBUG        'd'


/**
 * Defines the command send to notify the end of the match
 */
#define COMMAND_SHOW_MATCH_ENDED                'm'

/**
 * Define the command sent to read how much time there still is.
 */
#define COMMAND_GET_TIME_LEFT                   't'

/**
 * Define the command used to change the remaining time (used for test to avoid to wait for the end of the match).
 */
#define COMMAND_SET_CURRENT_TIME_IN_SECOND      'S'

/**
 * Define the command used to set the new match duration
 */
#define COMMAND_SET_MATCH_DURATION              'M'

// Notifications

#define COMMAND_NOTIFY_MATCH_ENDED              'e'


/**
 * The interface for the device EndMatchDetectorDevice.
 */
DeviceInterface* getEndMatchDetectorDeviceInterface();

#endif
