#ifndef ROBOT_KINEMATICS_INTERFACE_H
#define ROBOT_KINEMATICS_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

// GLOBAL COMMAND
#define COMMAND_KINEMATICS_LOAD_DEFAULT_VALUES                     'D'
#define COMMAND_KINEMATICS_LIST_DEBUG					           'L'

#define COMMAND_KINEMATICS_READ_ALL                                'G'
#define COMMAND_KINEMATICS_SAVE                                    'S'

// CODER COMMAND
#define COMMAND_SET_CODER_WHEEL_AVERAGE_DIAMETER_MM                'w'
#define COMMAND_SET_CODER_WHEEL_AVERAGE_DELTA_DIAMETER_MM          'd'
#define COMMAND_SET_CODER_DISTANCE_BETWEEN_WHEELS_MM               'h'
#define COMMAND_SET_CODER_WHEEL_PULSE_BY_ROTATION                  'p'

// MOTOR COMMAND
#define COMMAND_SET_MOTOR_WHEEL_AVERAGE_DIAMETER_MM                'M'
#define COMMAND_SET_MOTOR_DISTANCE_BETWEEN_WHEELS_MM               'H'
#define COMMAND_SET_MOTOR_WHEEL_ROTATION_BY_SECONDS_AT_FULL_SPEED  'R'

#define COMMAND_SET_ROBOT_TYPE                                     'T'

/**
 * Interface for Device "RobotKinematics"
 */
DeviceInterface* getRobotKinematicsDeviceInterface();

#endif
