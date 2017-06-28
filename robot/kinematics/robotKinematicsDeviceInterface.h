#ifndef ROBOT_KINEMATICS_INTERFACE_H
#define ROBOT_KINEMATICS_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

#define COMMAND_KINEMATICS_LOAD_DEFAULT_VALUES            'd'
#define COMMAND_KINEMATICS_DEBUG						  'D'

#define COMMAND_GET_WHEELS_AVERAGE_FOR_ONE_PULSE_LENGTH 'l'
#define COMMAND_SET_WHEELS_AVERAGE_FOR_ONE_PULSE_LENGTH 'L'

#define COMMAND_GET_ROTATION_BY_SECONDS_AT_FULL_SPEED   'r'
#define COMMAND_SET_ROTATION_BY_SECONDS_AT_FULL_SPEED   'R'

#define COMMAND_GET_PULSE_BY_ROTATION                   'p'
#define COMMAND_SET_PULSE_BY_ROTATION                   'P'

#define COMMAND_GET_WHEEL_DELTA_FOR_ONE_PULSE_LENGTH    'w'
#define COMMAND_SET_WHEEL_DELTA_FOR_ONE_PULSE_LENGTH    'W'

#define COMMAND_GET_WHEELS_DISTANCE                     'h'
#define COMMAND_SET_WHEELS_DISTANCE                     'H'

/**
* Interface for Device "RobotKinematics"
*/
DeviceInterface* getRobotKinematicsDeviceInterface();

#endif
