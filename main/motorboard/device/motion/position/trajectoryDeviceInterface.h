#ifndef TRAJECTORY_DEVICE_REMOTE_INTERFACE_H
#define TRAJECTORY_DEVICE_REMOTE_INTERFACE_H

#include "../../../device/deviceInterface.h"

/**
* Defines the header used to ask absolute position.
*/
#define COMMAND_GET_ABSOLUTE_POSITION 'h'

/**
* Send the absolute position with debug to output.
*/
#define COMMAND_DEBUG_GET_ABSOLUTE_POSITION 'H'

/**
* Defines the header used to set the absolute position.
*/
#define COMMAND_SET_ABSOLUTE_POSITION 		'K'

/**
* Factor of transformation to change float to long
* with the less of lost.
*/
#define FLOAT_TO_LONG_FACTOR 		1000.0f

/**
* Interface for Device
*/
DeviceInterface* getTrajectoryDeviceInterface();

#endif
