#ifndef ROBOT_CONFIG_REMOTE_INTERFACE_H
#define ROBOT_CONFIG_REMOTE_INTERFACE_H

#include "../../device/deviceInterface.h"

/** Command header to get the config. */
#define COMMAND_CONFIG 'c'

/**
* Interface for Device "RobotConfig"
*/
DeviceInterface* getRobotConfigDeviceInterface();

#endif
