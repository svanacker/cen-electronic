#ifndef ROBOT_KINEMATICS_DEVICE_H
#define ROBOT_KINEMATICS_DEVICE_H

#include "../../common/eeprom/eeprom.h"

#include "../../device/device.h"

#include "../../robot/config/robotConfig.h"

/**
 * Returns a descriptor on the kinematics Information.
 * @return the descriptor of the device.
 */
DeviceDescriptor* getRobotKinematicsDeviceDescriptor(Eeprom* eeprom_);

#endif
