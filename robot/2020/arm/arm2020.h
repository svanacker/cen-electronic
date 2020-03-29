#ifndef ARM_2020_H
#define ARM_2020_H

#include "../../../common/pwm/servo/servoList.h"

// LATERAL ARM
#define ARM_2020_SERVO_INDEX                                          0x00

// LATERAL VALUES
#define ARM_2020_ARM_SPEED_FACTOR                                     0xFF
#define ARM_2020_ARM_SERVO_MIDDLE                                     0x05DC
#define ARM_2020_ARM_SERVO_LEFT                                       0x0780
#define ARM_2020_ARM_SERVO_RIGHT                                      0x03C0

// FLAG
#define ARM_2020_FLAG_SERVO_INDEX                                     0x01
#define ARM_2020_FLAG_SPEED_FACTOR                                    0x20
#define ARM_2020_FLAG_DOWN                                            0x05DC
#define ARM_2020_FLAG_UP                                              0x09D0

#define ARM_2020_HOOK_COUNT                                           5

// HOOK - VERTICAL SERVO
#define ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX                       0x03
#define ARM_2020_HOOK_DOWN_SPEED_FACTOR                               0x10
#define ARM_2020_HOOK_DOWN                                            0x06C0
#define ARM_2020_HOOK_UP                                              0x0460
#define ARM_2020_HOOK_UP_SPEED_FACTOR                                 0x10

// HOOK - TAKE SERVO
#define ARM_2020_HOOK_TAKE_SERVO_BASE_INDEX                           0x0D
#define ARM_2020_HOOK_TAKE_SPEED_FACTOR                               0x20
#define ARM_2020_HOOK_TAKE                                            0x0700
#define ARM_2020_HOOK_RELEASE_SPEED_FACTOR                            0x10
#define ARM_2020_HOOK_RELEASE                                         0x0200

// ARM

/**
 * @param leftRightCenter Center = 0x00, Left = 0x01, Right = 0x02
 */
unsigned int lateralArm2020(ServoList* servoList, unsigned char leftRightCenter);

// FLAG

/**
 * flagDown
 */
unsigned int arm2020FlagDown(ServoList* servoList);

/**
 * FlagUp
 */
unsigned int arm2020FlagUp(ServoList* servoList);

// HOOK

unsigned int arm2020HookDown(ServoList* servoList, unsigned char hookIndex, bool wait);
unsigned int arm2020HookDownAll(ServoList* servoList, bool wait);

unsigned int arm2020HookUp(ServoList* servoList, unsigned char hookIndex, bool wait);
unsigned int arm2020HookUpAll(ServoList* servoList, bool wait);

unsigned int arm2020HookTake(ServoList* servoList, unsigned char hookIndex, bool wait);
unsigned int arm2020HookTakeAll(ServoList* servoList, bool wait);

unsigned int arm2020HookRelease(ServoList* servoList, unsigned char hookIndex, bool wait);
unsigned int arm2020HookReleaseAll(ServoList* servoList, bool wait);

// HOOK - COMPLEX

unsigned int arm2020HookPrepare(ServoList* servoList, unsigned char hookIndex, bool wait);
unsigned int arm2020HookPrepareAll(ServoList* servoList);

unsigned int arm2020TakeAndUp(ServoList* servoList, unsigned char hookIndex, bool wait);
unsigned int arm2020TakeAndUpAll(ServoList* servoList);

unsigned int arm2020DownAndRelease(ServoList* servoList, unsigned char hookIndex, bool wait);
unsigned int arm2020DownAndReleaseAll(ServoList* servoList);

// HOOK - SEQUENCE
void arm2020HookSequenceAll(ServoList* servoList);


#endif
