#include "arm2020.h"

#include <math.h>

#include "../../../common/pwm/servo/servoPwm.h"
#include "../../../common/timer/delayTimer.h"

#include "../../../client/motion/simple/clientMotion.h"

// ARM

unsigned int lateralArm2020(ServoList* servoList, unsigned char leftRightCenter) {
    Servo* servo = getServo(servoList, ARM_2020_SERVO_INDEX);
    if (leftRightCenter == 0x00) {
        return pwmServo(servo, ARM_2020_ARM_SPEED_FACTOR, ARM_2020_ARM_SERVO_MIDDLE, 0);
    } else if (leftRightCenter == 0x01) {
        return pwmServo(servo, ARM_2020_ARM_SPEED_FACTOR, ARM_2020_ARM_SERVO_LEFT, 0);
    } else if (leftRightCenter == 0x02) {
        return pwmServo(servo, ARM_2020_ARM_SPEED_FACTOR, ARM_2020_ARM_SERVO_RIGHT, 0);
    }
    return 0;
}

// FLAG

unsigned int arm2020FlagDown(ServoList* servoList) {
    Servo* servo = getServo(servoList, ARM_2020_FLAG_SERVO_INDEX);
    return pwmServo(servo, ARM_2020_FLAG_SPEED_FACTOR, ARM_2020_FLAG_DOWN, 0);
}

unsigned int arm2020FlagUp(ServoList* servoList) {
    Servo* servo = getServo(servoList, ARM_2020_FLAG_SERVO_INDEX);
    return pwmServo(servo, ARM_2020_FLAG_SPEED_FACTOR, ARM_2020_FLAG_UP, 0);
}

// HOOK

unsigned int arm2020HookDown(ServoList* servoList, unsigned char hookIndex) {
    Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
    return pwmServo(servo, ARM_2020_HOOK_DOWN_SPEED_FACTOR, ARM_2020_HOOK_DOWN, 0);
}

unsigned int arm2020HookDownAll(ServoList* servoList) {
    unsigned int hookIndex = 0;
    unsigned int result = 0;
    for (hookIndex = 0; hookIndex < ARM_2020_HOOK_COUNT; hookIndex++) {
        Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
        unsigned int timeToReach = pwmServo(servo, ARM_2020_HOOK_DOWN_SPEED_FACTOR, ARM_2020_HOOK_DOWN, 0);
        if (timeToReach > result) {
            result = timeToReach;
        }
    }
    return result;
}

unsigned int arm2020HookDownMiddleAll(ServoList* servoList) {
    unsigned int hookIndex = 0;
    unsigned int result = 0;
    for (hookIndex = 1; hookIndex < ARM_2020_HOOK_COUNT - 1; hookIndex++) {
        Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
        unsigned int timeToReach = pwmServo(servo, ARM_2020_HOOK_DOWN_SPEED_FACTOR, ARM_2020_HOOK_DOWN, 0);
        if (timeToReach > result) {
            result = timeToReach;
        }
    }
    return result;
}

unsigned int arm2020HookUp(ServoList* servoList, unsigned char hookIndex, unsigned int delayBeforeMoving) {
    Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
    return pwmServo(servo, ARM_2020_HOOK_UP_SPEED_FACTOR, ARM_2020_HOOK_UP, delayBeforeMoving);
}

unsigned int arm2020HookUpAll(ServoList* servoList, unsigned int delayBeforeMoving) {
    unsigned int hookIndex = 0;
    unsigned int result = 0;
    for (hookIndex = 0; hookIndex < ARM_2020_HOOK_COUNT; hookIndex++) {
        Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
        unsigned timeToReach = pwmServo(servo, ARM_2020_HOOK_UP_SPEED_FACTOR, ARM_2020_HOOK_UP, delayBeforeMoving);
        if (timeToReach > result) {
            result = timeToReach;
        }
    }
    return result;
}

unsigned int arm2020HookUpMiddleAll(ServoList* servoList, unsigned int delayBeforeMoving) {
    unsigned int hookIndex = 0;
    unsigned int result = 0;
    for (hookIndex = 1; hookIndex < ARM_2020_HOOK_COUNT - 1; hookIndex++) {
        Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
        unsigned timeToReach = pwmServo(servo, ARM_2020_HOOK_UP_SPEED_FACTOR, ARM_2020_HOOK_UP, delayBeforeMoving);
        if (timeToReach > result) {
            result = timeToReach;
        }
    }
    return result;
}

unsigned int arm2020HookPrepareFloor(ServoList* servoList, unsigned char hookIndex) {
    Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
    return pwmServo(servo, ARM_2020_HOOK_FLOOR_UP_SPEED_FACTOR, ARM_2020_HOOK_FLOOR_UP, 0);
}

unsigned int arm2020HookPrepareFloorCenterAll(ServoList* servoList) {
    unsigned int hookIndex = 0;
    unsigned int result = 0;
    // Up to prepare for 3 central hook 
    for (hookIndex = 1; hookIndex < ARM_2020_HOOK_COUNT - 1; hookIndex++) {
        Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
        unsigned timeToReach = pwmServo(servo, ARM_2020_HOOK_FLOOR_UP_SPEED_FACTOR, ARM_2020_HOOK_FLOOR_UP, 0);
        if (timeToReach > result) {
            result = timeToReach;
        }
    }
    // and up very high at the extreme leftand extreme right
    arm2020HookUp(servoList, 0, 0);
    arm2020HookUp(servoList, ARM_2020_HOOK_COUNT - 1, 0);

    return result;
}

unsigned int arm2020HookPrepareFloorAll(ServoList* servoList) {
    unsigned int hookIndex = 0;
    unsigned int result = 0;
    for (hookIndex = 0; hookIndex < ARM_2020_HOOK_COUNT; hookIndex++) {
        Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
        unsigned timeToReach = pwmServo(servo, ARM_2020_HOOK_FLOOR_UP_SPEED_FACTOR, ARM_2020_HOOK_FLOOR_UP, 0);
        if (timeToReach > result) {
            result = timeToReach;
        }
    }

    return result;
}


unsigned int arm2020HookLockFloor(ServoList* servoList, unsigned char hookIndex) {
    Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
    return pwmServo(servo, ARM_2020_HOOK_FLOOR_DOWN_SPEED_FACTOR, ARM_2020_HOOK_FLOOR_DOWN, 0);
}

unsigned int arm2020HookLockFloorAll(ServoList* servoList) {
    unsigned int hookIndex = 0;
    unsigned int result = 0;
    // We lock only the hook at the center (perimeter problem)
    for (hookIndex = 1; hookIndex < ARM_2020_HOOK_COUNT - 1; hookIndex++) {
        Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
        unsigned timeToReach = pwmServo(servo, ARM_2020_HOOK_FLOOR_DOWN_SPEED_FACTOR, ARM_2020_HOOK_FLOOR_DOWN, 0);
        if (timeToReach > result) {
            result = timeToReach;
        }
    }
    // We up the hook to the extreme left and to the extreme right
    arm2020HookUp(servoList, 0, 0);
    arm2020HookUp(servoList, ARM_2020_HOOK_COUNT - 1, 0);
    return result;
}


unsigned int arm2020HookTake(ServoList* servoList, unsigned char hookIndex) {
    Servo* servo = getServo(servoList, ARM_2020_HOOK_TAKE_SERVO_BASE_INDEX + hookIndex);
    return pwmServo(servo, ARM_2020_HOOK_TAKE_SPEED_FACTOR, ARM_2020_HOOK_TAKE, 0);
}

unsigned int arm2020HookTakeAll(ServoList* servoList) {
    unsigned int result = 0;
    unsigned int hookIndex = 0;
    for (hookIndex = 0; hookIndex < ARM_2020_HOOK_COUNT; hookIndex++) {
        Servo* servo = getServo(servoList, ARM_2020_HOOK_TAKE_SERVO_BASE_INDEX + hookIndex);
        unsigned int timeToReach = pwmServo(servo, ARM_2020_HOOK_TAKE_SPEED_FACTOR, ARM_2020_HOOK_TAKE, 0);
        if (timeToReach > result) {
            result = timeToReach;
        }
    }
    return result;
}

unsigned int arm2020HookRelease(ServoList* servoList, unsigned char hookIndex, unsigned int delayBeforeMoving) {
    Servo* servo = getServo(servoList, ARM_2020_HOOK_TAKE_SERVO_BASE_INDEX + hookIndex);
    return pwmServo(servo, ARM_2020_HOOK_RELEASE_SPEED_FACTOR, ARM_2020_HOOK_RELEASE, delayBeforeMoving);
}

unsigned int arm2020HookReleaseAll(ServoList* servoList, unsigned int delayBeforeMoving) {
    unsigned int result = 0;
    unsigned int hookIndex = 0;
    for (hookIndex = 0; hookIndex < ARM_2020_HOOK_COUNT; hookIndex++) {
        Servo* servo = getServo(servoList, ARM_2020_HOOK_TAKE_SERVO_BASE_INDEX + hookIndex);
        unsigned int timeToReach = pwmServo(servo, ARM_2020_HOOK_RELEASE_SPEED_FACTOR, ARM_2020_HOOK_RELEASE, delayBeforeMoving);
        if (timeToReach > result) {
            result = timeToReach;
        }
    }
    return result;
}


// HOOK - COMPLEX

unsigned int arm2020HookPrepare(ServoList* servoList, unsigned char hookIndex) {
    unsigned int releaseTime = arm2020HookRelease(servoList, hookIndex, 0);
    unsigned int downTime = arm2020HookDown(servoList, hookIndex);
    if (releaseTime > downTime) {
        return releaseTime;
    }
    return downTime;
}

unsigned int arm2020HookPrepareAll(ServoList* servoList) {
    unsigned int releaseTime = arm2020HookReleaseAll(servoList, 0);
    unsigned int downTime = arm2020HookDownAll(servoList);
    if (releaseTime > downTime) {
        return releaseTime;
    }
    return downTime;
}

unsigned int arm2020TakeAndUp(ServoList* servoList, unsigned char hookIndex) {
    unsigned int takeTime = arm2020HookTake(servoList, hookIndex);
    unsigned int upTime = arm2020HookUp(servoList, hookIndex, takeTime);
    return takeTime + upTime;
}

unsigned int arm2020TakeAndUpAll(ServoList* servoList) {
    unsigned int takeTime = arm2020HookTakeAll(servoList);
    unsigned int upTime = arm2020HookUpAll(servoList, takeTime);
    return (takeTime + upTime);
}

unsigned int arm2020DownAndRelease(ServoList* servoList, unsigned char hookIndex) {
    unsigned int downTime = arm2020HookDown(servoList, hookIndex);
    unsigned int releaseTime = arm2020HookRelease(servoList, hookIndex, downTime);
    return downTime + releaseTime;
}

unsigned int arm2020DownAndReleaseAll(ServoList* servoList) {
    unsigned int downTime = arm2020HookDownAll(servoList);
    unsigned int releaseTime = arm2020HookReleaseAll(servoList, downTime);
    return downTime + releaseTime;
}

// Global Sequence
void arm2020HookSequenceAll(ServoList* servoList) {
    arm2020HookPrepareAll(servoList);
    timerDelayMilliSeconds(1000);
    // motionDriverForward(50);
    timerDelayMilliSeconds(2000);

    arm2020TakeAndUpAll(servoList);
    // motionDriverBackward(150);
    timerDelayMilliSeconds(2000);

    arm2020DownAndReleaseAll(servoList);
    // motionDriverBackward(50);
}
