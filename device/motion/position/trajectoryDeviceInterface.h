#ifndef TRAJECTORY_DEVICE_REMOTE_INTERFACE_H
#define TRAJECTORY_DEVICE_REMOTE_INTERFACE_H

#include "../../../device/deviceInterface.h"

/**
 * Header char of Trajectory device : 'n' for 'navigation.
 */
#define TRAJECTORY_DEVICE_HEADER		'n'

/**
* Defines the header used to ask absolute position.
*/
#define COMMAND_GET_ABSOLUTE_POSITION 	'r'

/**
* Send the absolute position with debug to output.
*/
#define COMMAND_DEBUG_GET_ABSOLUTE_POSITION 'd'

/**
* Defines the header used to set the absolute position.
*/
#define COMMAND_SET_ABSOLUTE_POSITION 		'w'

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
