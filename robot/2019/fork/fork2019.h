#ifndef FORK_2019_H
#define FORK_2019_H

#include <stdbool.h>

#include "../../../common/pwm/servo/servoList.h"

#include "../../../drivers/tof/tofList.h"

// GLOBAL

// Used to move the both Fork
#define FORK_2019_LEFT_AND_RIGHT_INDEX            0x0

// Used to move the left Fork only
#define FORK_2019_LEFT_INDEX                      0x1

// Used to move the right Fork only
#define FORK_2019_RIGHT_INDEX                     0x2



// FORK SERVO INDEX

#define FORK_2019_LEFT_ARM_SERVO_INDEX                                         0
#define FORK_2019_RIGHT_ARM_SERVO_INDEX                                        1

// The servo to scan (Elevator Left / Right))
#define FORK_2019_SCAN_SERVO_INDEX                                             2

// We will use PCA9685 for all and the first
#define FORK_2019_PCA9685_START_INDEX                                          3

#define FORK_2019_ELEVATOR_SERVO_INDEX         FORK_2019_PCA9685_START_INDEX + 0

// Fork Index
#define FORK_2019_RIGHT_SERVO_FORK_INDEX       FORK_2019_PCA9685_START_INDEX + 1
#define FORK_2019_LEFT_SERVO_FORK_INDEX       FORK_2019_PCA9685_START_INDEX +  7

// Push Index
#define FORK_2019_RIGHT_SERVO_PUSH_INDEX       FORK_2019_PCA9685_START_INDEX + 3
#define FORK_2019_LEFT_SERVO_PUSH_INDEX       FORK_2019_PCA9685_START_INDEX + 12

// Elevator Servo Value
#define FORK_2019_ELEVATOR_SPEED_FACTOR                                     0xFF
#define FORK_2019_ELEVATOR_DISTRIBUTOR_SCAN_SERVO_VALUE                   0x0800
#define FORK_2019_ELEVATOR_BOTTOM_SERVO_VALUE                             0x09F0
#define FORK_2019_ELEVATOR_INIT_POSITION_SERVO_VALUE                      0x05DC
#define FORK_2019_ELEVATOR_GOLDENIUM_SERVO_VALUE                          0x0440
#define FORK_2019_ELEVATOR_GOLDENIUM_SCAN_SERVO_VALUE                     0x0400
#define FORK_2019_ELEVATOR_SECOND_DROP_SERVO_VALUE                        0x04E0
#define FORK_2019_ELEVATOR_UP_SERVO_VALUE                                 0x0280

// Servo Fork Left
#define FORK_2019_SERVO_LEFT_SPEED_FACTOR                                   0xFF
#define FORK_2019_SERVO_LEFT_RETRACTED_SERVO_VALUE                        0x0900
#define FORK_2019_SERVO_LEFT_SIMPLE_PUCK_SERVO_VALUE                      0x05DC
#define FORK_2019_SERVO_LEFT_DOUBLE_PUCK_SERVO_VALUE                      0x0400

// Servo Push Left
#define FORK_2019_SERVO_PUSH_LEFT_SPEED_FACTOR                            0xFF
#define FORK_2019_SERVO_PUSH_LEFT_OFF_SERVO_VALUE                         0x05DC
#define FORK_2019_SERVO_PUSH_LEFT_ON_SERVO_VALUE                          0x0A00

// Servo Left
#define FORK_2019_SERVO_RIGHT_SPEED_FACTOR                                  0xFF
#define FORK_2019_SERVO_RIGHT_RETRACTED_SERVO_VALUE                       0x0300
#define FORK_2019_SERVO_RIGHT_SIMPLE_PUCK_SERVO_VALUE                     0x05DC
#define FORK_2019_SERVO_RIGHT_DOUBLE_PUCK_SERVO_VALUE                     0x0800

// Servo Push Right
#define FORK_2019_SERVO_PUSH_RIGHT_SPEED_FACTOR                             0xFF
#define FORK_2019_SERVO_PUSH_RIGHT_OFF_SERVO_VALUE                        0x05DC
#define FORK_2019_SERVO_PUSH_RIGHT_ON_SERVO_VALUE                         0x0300

// SPEED VALUE
#define FORK_2019_ELEVATOR_MAX_SPEED_UNDER_LOAD              MAX_SPEED_UNDER_LOAD__1_SECOND_60_DEG
#define FORK_2019_ELEVATOR_SCAN_MAX_SPEED_UNDER_LOAD         MAX_SPEED_UNDER_LOAD__500_MS_60_DEG
#define FORK_2019_ELEVATOR_FORK_MAX_SPEED_UNDER_LOAD         MAX_SPEED_UNDER_LOAD__500_MS_60_DEG
#define FORK_2019_ELEVATOR_FORK_PUSH_MAX_SPEED_UNDER_LOAD    MAX_SPEED_UNDER_LOAD__500_MS_60_DEG

// BASE FUNCTIONS

void fork2019MoveServo(ServoList* servoList,
        unsigned int leftRight,
        unsigned int leftServoIndex,
        unsigned int rightServoIndex,
        unsigned int leftSpeed,
        unsigned int rightSpeed,
        unsigned int leftPosition,
        unsigned rightPosition,
        bool wait);

// FORK

void moveForkBack(ServoList* servoList, unsigned int leftRight, bool wait);

void moveForkSimplePuck(ServoList* servoList, unsigned int leftRight, bool wait);

void moveForkDoublePuck(ServoList* servoList, unsigned int leftRight, bool wait);

void moveForkBackAllWithoutWait(ServoList* servoList);

// FORK PUSH (small device under the Fork to facilitate the release)

void moveForkPushOff(ServoList* servoList, unsigned int leftRight, bool wait);

void moveForkPushOn(ServoList* servoList, unsigned int leftRight, bool wait);

void moveForkPushOffAllWithoutWait(ServoList* servoList);

// COMPLEX OPERATIONS

/**
 * The initialisation of the fork before the Robot Start !
 * @param servoList
 */
void fork2019Init(ServoList* servoList);

/**
 * All actions to take a Simple Puck.
 * @param servoList
 */
bool fork2019TakeSimplePuck(ServoList* servoList, TofSensorList* tofSensorList);

// SERVO NAME

/**
 * Update the servo List so that we could easily know to change the value
 * without reading the code
 * @param servoList
 */
void updateServoProperties2019(ServoList* servoList);

#endif
