#ifndef FORK_DEVICE_2019_H
#define FORK_DEVICE_2019_H

#include "../../common/pwm/servo/servoList.h"

#include "../../device/device.h"

#include "../../drivers/tof/tofList.h"

// The servo to scan 
#define FORK_2019_SCAN_SERVO_INDEX                                             0

// FORK SERVO INDEX
// We will use PCA8695 for all and the first
#define FORK_2019_PCA9685_START_INDEX                                          3

#define FORK_2019_ELEVATOR_SERVO_INDEX         FORK_2019_PCA9685_START_INDEX + 0

// Fork Index
#define FORK_2019_RIGHT_SERVO_INDEX            FORK_2019_PCA9685_START_INDEX + 1
#define FORK_2019_LEFT_SERVO_INDEX            FORK_2019_PCA9685_START_INDEX + 15

// Push Index
#define FORK_2019_RIGHT_SERVO_PUSH_INDEX       FORK_2019_PCA9685_START_INDEX + 3
#define FORK_2019_LEFT_SERVO_PUSH_INDEX       FORK_2019_PCA9685_START_INDEX + 12

// Scan Servo Value
#define FORK_2019_SCAN_SPEED_FACTOR                                         0xFF
#define FORK_2019_SCAN_LEFT_SERVO_VALUE                                   0x0700
#define FORK_2019_SCAN_RIGHT_SERVO_VALUE                                  0x0300

// Elevator Servo Value
#define FORK_2019_ELEVATOR_SPEED_FACTOR                                     0xFF
#define FORK_2019_ELEVATOR_BOTTOM_SERVO_VALUE                             0x0B00
#define FORK_2019_ELEVATOR_INIT_POSITION_SERVO_VALUE                      0x05DC
#define FORK_2019_ELEVATOR_DOUBLE_PUCK_SERVO_VALUE                        0x0500
#define FORK_2019_ELEVATOR_UP_SERVO_VALUE                                 0x0200

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
#define FORK_2019_LEFT_ARM_SERVO_INDEX                                         0
#define FORK_2019_LEFT_ARM_SERVO_ON                                       0x0180
#define FORK_2019_LEFT_ARM_SERVO_OFF                                      0x05DC

// Small Robot : Arm Right (for Goldenium)
#define FORK_2019_RIGHT_ARM_SPEED_FACTOR                                    0xFF
#define FORK_2019_RIGHT_ARM_SERVO_INDEX                                        1
#define FORK_2019_RIGHT_ARM_SERVO_ON                                      0x0A38
#define FORK_2019_RIGHT_ARM_SERVO_OFF                                     0x05DC

/**
 * The descriptor for the Fork 2019 device.
 */
DeviceDescriptor* getFork2019DeviceDescriptor(ServoList* servoList,
                                              TofSensorList* tofSensorListParam);

// ELEVATOR

void moveElevatorBottom(void);

void moveElevatorUp(void);

void moveElevatorDoublePuck(void);

// FORK

void moveForkBack(unsigned int leftRight);

void moveForkSimplePuck(unsigned int leftRight);

void moveForkDoublePuck(unsigned int leftRight);

void moveForkPushOff(unsigned int leftRight);

void moveForkPushOn(unsigned int leftRight);

// FORK SCAN

void forkScanFromLeftToRight(void);

void forkScanFromRightToLeft(void);

// ARM (SMALL ROBOT)

/**
* @param leftRight Both Arm = 0x00, Left Arm = 0x01, Right Arm = 0x02
*/
void arm2019On(unsigned int leftRight);

/**
* @param leftRight Both Arm = 0x00, Left Arm = 0x01, Right Arm = 0x02
*/
void arm2019Off(unsigned int leftRight);

#endif
