#ifndef FORK_2019_H
#define FORK_2019_H

#include <stdbool.h>

#include "../../common/pwm/servo/servoList.h"

#include "../../drivers/tof/tofList.h"

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
#define FORK_2019_LEFT_SERVO_FORK_INDEX       FORK_2019_PCA9685_START_INDEX + 15

// Push Index
#define FORK_2019_RIGHT_SERVO_PUSH_INDEX       FORK_2019_PCA9685_START_INDEX + 3
#define FORK_2019_LEFT_SERVO_PUSH_INDEX       FORK_2019_PCA9685_START_INDEX + 12

// Scan Servo Value
#define FORK_2019_SCAN_SPEED_FACTOR                                         0xFF
#define FORK_2019_SCAN_LEFT_SERVO_VALUE                                   0x0700
#define FORK_2019_SCAN_RIGHT_SERVO_VALUE                                  0x0300

// Elevator Servo Value
#define FORK_2019_ELEVATOR_SPEED_FACTOR                                     0xFF
#define FORK_2019_ELEVATOR_BOTTOM_SERVO_VALUE                             0x09A0
#define FORK_2019_ELEVATOR_INIT_POSITION_SERVO_VALUE                      0x05DC
#define FORK_2019_ELEVATOR_GOLDENIUM_SERVO_VALUE                          0x0460
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

// Small Robot : Arm Left (for Goldenium)
#define FORK_2019_LEFT_ARM_SPEED_FACTOR                                     0xFF
#define FORK_2019_LEFT_ARM_SERVO_ON                                       0x0180
#define FORK_2019_LEFT_ARM_SERVO_OFF                                      0x05DC

// Small Robot : Arm Right (for Goldenium)
#define FORK_2019_RIGHT_ARM_SPEED_FACTOR                                    0xFF
#define FORK_2019_RIGHT_ARM_SERVO_ON                                      0x0A38
#define FORK_2019_RIGHT_ARM_SERVO_OFF                                     0x05DC

// TOF INDEX
#define FORK_2019_LEFT_TOF_INDEX                                               6
#define FORK_2019_RIGHT_TOF_INDEX                                              7

// TOF THRESHOLD
#define FORK_2019_LEFT_THRESHOLD                                              16
#define FORK_2019_RIGHT_THRESHOLD                                             16



// ELEVATOR

void moveElevatorAtValue(ServoList* servoList, unsigned int value);

void moveElevatorBottom(ServoList* servoList);

void moveElevatorUp(ServoList* servoList);

void moveElevatorInitPosition(ServoList* servoList);

void moveElevatorGoldenium(ServoList* servoList);

void moveElevatorLeft(ServoList* servoList);

void moveElevatorRight(ServoList* servoList);

// FORK

void moveForkBack(ServoList* servoList, unsigned int leftRight);

void moveForkSimplePuck(ServoList* servoList, unsigned int leftRight);

void moveForkDoublePuck(ServoList* servoList, unsigned int leftRight);

// FORK PUSH (small device under the Fork to facilitate the release)

void moveForkPushOff(ServoList* servoList, unsigned int leftRight);

void moveForkPushOn(ServoList* servoList, unsigned int leftRight);

// FORK SCAN

void setForkTofListNameAndThreshold(TofSensorList* tofSensorList);

void forkScanFromLeftToRight(ServoList* servoList, TofSensorList* tofSensorList);

void forkScanFromRightToLeft(ServoList* servoList, TofSensorList* tofSensorList);

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
bool fork2019TakeSimplePuck(ServoList* servoList);

/**
 * All actions to take a Goldenium.
 * @param servoList
 */
bool fork2019TakeGoldenium(ServoList* servoList, unsigned int leftRight);

/**
 * All actions to release a Goldenium.
 */
bool fork2019DropGoldenium(ServoList* servoList, unsigned int leftRight);

/**
 * The actions to to release the Puck in Accelerator
 * @param servoList
 */
bool fork2019AcceleratorDrop(ServoList* servoList);


// ARM (SMALL ROBOT)

/**
* @param leftRight Both Arm = 0x00, Left Arm = 0x01, Right Arm = 0x02
*/
void arm2019On(ServoList* servoList, unsigned int leftRight);

/**
* @param leftRight Both Arm = 0x00, Left Arm = 0x01, Right Arm = 0x02
*/
void arm2019Off(ServoList* servoList, unsigned int leftRight);

// SERVO NAME

/**
 * Update the servo List so that we could easily know to change the value
 * without reading the code
 * @param servoList
 */
void updateServoListName2019(ServoList* servoList);

#endif
