#ifndef ARM_2019_H
#define ARM_2019_H

#include "../../../common/pwm/servo/servoList.h"

// ARM (SMALL ROBOT)

// Small Robot : Arm Left (for Goldenium)
#define FORK_2019_LEFT_ARM_SPEED_FACTOR                                     0xFF
#define FORK_2019_LEFT_ARM_SERVO_ON                                       0x0180
#define FORK_2019_LEFT_ARM_SERVO_OFF                                      0x05DC

// Small Robot : Arm Right (for Goldenium)
#define FORK_2019_RIGHT_ARM_SPEED_FACTOR                                    0xFF
#define FORK_2019_RIGHT_ARM_SERVO_ON                                      0x0A38
#define FORK_2019_RIGHT_ARM_SERVO_OFF                                     0x05DC

/**
* @param leftRight Both Arm = 0x00, Left Arm = 0x01, Right Arm = 0x02
*/
void arm2019On(ServoList* servoList, unsigned int leftRight);

/**
* @param leftRight Both Arm = 0x00, Left Arm = 0x01, Right Arm = 0x02
*/
void arm2019Off(ServoList* servoList, unsigned int leftRight);

#endif
