#ifndef ROBOT_CONFIG_DEVICE_H
#define ROBOT_CONFIG_DEVICE_H

#include "robotConfig.h"
#include "../../device/device.h"

/**
* Returns a descriptor on the config.
* @return the descriptor of the device.
*/
DeviceDescriptor* getRobotConfigDeviceDescriptor(RobotConfig* robotConfigParam);

/**
* Returns the strategy which must be used by the robot.
*/
unsigned char getStrategy();

#endif
