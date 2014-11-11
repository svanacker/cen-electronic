#ifndef ROBOT_CONFIG_REMOTE_INTERFACE_H
#define ROBOT_CONFIG_REMOTE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Command header to get the config. */
#define COMMAND_CONFIG                  'r'

/**
* Interface for Device "RobotConfig"
*/
DeviceInterface* getRobotConfigDeviceInterface();

#endif
