#ifndef ROBOT_CONFIG_REMOTE_INTERFACE_H
#define ROBOT_CONFIG_REMOTE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Command header to get the config. */
#define COMMAND_GET_CONFIG                  'r'

/** Command header to write the config (only for Windows simulation. */
#define COMMAND_SET_CONFIG                  'w'

/**
* Interface for Device "RobotConfig"
*/
DeviceInterface* getRobotConfigDeviceInterface();

#endif
