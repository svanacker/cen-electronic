#ifndef TRAJECTORY_DEVICE_REMOTE_INTERFACE_H
#define TRAJECTORY_DEVICE_REMOTE_INTERFACE_H

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

/**
* Defines the header used to ask absolute position.
*/
#define COMMAND_TRAJECTORY_GET_ABSOLUTE_POSITION            'r'

/**
* Write in debug the absolute position .
*/
#define COMMAND_TRAJECTORY_DEBUG_GET_ABSOLUTE_POSITION      'd'

/**
* Write in debug coders history value.
*/
#define COMMAND_TRAJECTORY_DEBUG_CODERS					'D'

/**
* Defines the header used to set the absolute position.
*/
#define COMMAND_TRAJECTORY_SET_ABSOLUTE_POSITION            'w'

/**
* Interface for Device
*/
DeviceInterface* getTrajectoryDeviceInterface();

#endif
