#ifndef FORK_DEVICE_2019_H
#define FORK_DEVICE_2019_H

#include "../../common/pwm/servo/servoList.h"

#include "../../device/device.h"

// FORK SERVO INDEX
// We will use PCA8695 for all and the first
#define FORK_2019_PCA9685_START_INDEX                                              3

#define FORK_2019_ELEVATOR_SERVO_INDEX                 FORK_2019_PCA9685_START_INDEX

#define FORK_2019_LEFT_SERVO_INDEX                 FORK_2019_PCA9685_START_INDEX + 4

#define FORK_2019_RIGHT_SERVO_INDEX                FORK_2019_PCA9685_START_INDEX + 8

// Elevator Servo Value
#define FORK_2019_ELEVATOR_SPEED_FACTOR                                         0xFF
#define FORK_2019_ELEVATOR_BOTTOM_SERVO_VALUE                                    800
#define FORK_2019_ELEVATOR_DOUBLE_PUCK_SERVO_VALUE                              1200
#define FORK_2019_ELEVATOR_UP_SERVO_VALUE                                       2200

// Servo Left
#define FORK_2019_SERVO_LEFT_SPEED_FACTOR                                       0xFF
#define FORK_2019_SERVO_LEFT_RETRACTED_SERVO_VALUE                              1000
#define FORK_2019_SERVO_LEFT_SIMPLE_PUCK_SERVO_VALUE                            1500
#define FORK_2019_SERVO_LEFT_DOUBLE_PUCK_SERVO_VALUE                            2000

// Servo Left
#define FORK_2019_SERVO_RIGHT_SPEED_FACTOR                                      0xFF
#define FORK_2019_SERVO_RIGHT_RETRACTED_SERVO_VALUE                             1000
#define FORK_2019_SERVO_RIGHT_SIMPLE_PUCK_SERVO_VALUE                           1500
#define FORK_2019_SERVO_RIGHT_DOUBLE_PUCK_SERVO_VALUE                           2000

/**
 * The descriptor for the Fork 2019 device.
 */
DeviceDescriptor* getFork2019DeviceDescriptor(ServoList* servoList);

#endif
