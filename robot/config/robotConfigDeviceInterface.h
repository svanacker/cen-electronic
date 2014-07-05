#ifndef ROBOT_CONFIG_REMOTE_INTERFACE_H
#define ROBOT_CONFIG_REMOTE_INTERFACE_H

#include "../../device/deviceInterface.h"

/** Device header .*/
#define ROBOT_CONFIG_DEVICE_HEADER      'c'


/** Command header to get the config. */
#define COMMAND_CONFIG                  'r'

/**
* Interface for Device "RobotConfig"
*/
DeviceInterface* getRobotConfigDeviceInterface();

#endif
