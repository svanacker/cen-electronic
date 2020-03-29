#include "arm2020.h"

#include <math.h>

#include "../../../common/pwm/servo/servoPwm.h"
#include "../../../common/timer/delayTimer.h"

#include "../../../client/motion/simple/clientMotion.h"

// ARM

unsigned int lateralArm2020(ServoList* servoList, unsigned char leftRightCenter) {
    Servo* servo = getServo(servoList, ARM_2020_SERVO_INDEX);
    if (leftRightCenter == 0x00) {
        return pwmServo(servo, ARM_2020_ARM_SPEED_FACTOR, ARM_2020_ARM_SERVO_MIDDLE, false);
    } else if (leftRightCenter == 0x01) {
        return pwmServo(servo, ARM_2020_ARM_SPEED_FACTOR, ARM_2020_ARM_SERVO_LEFT, false);
    } else if (leftRightCenter == 0x02) {
        return pwmServo(servo, ARM_2020_ARM_SPEED_FACTOR, ARM_2020_ARM_SERVO_RIGHT, false);
    }
    return 0;
}

// FLAG

unsigned int arm2020FlagDown(ServoList* servoList) {
    Servo* servo = getServo(servoList, ARM_2020_FLAG_SERVO_INDEX);
    return pwmServo(servo, ARM_2020_FLAG_SPEED_FACTOR, ARM_2020_FLAG_DOWN, false);
}

unsigned int arm2020FlagUp(ServoList* servoList) {
    Servo* servo = getServo(servoList, ARM_2020_FLAG_SERVO_INDEX);
    return pwmServo(servo, ARM_2020_FLAG_SPEED_FACTOR, ARM_2020_FLAG_UP, false);
}

// HOOK

unsigned int arm2020HookDown(ServoList* servoList, unsigned char hookIndex, bool wait) {
    Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
    return pwmServo(servo, ARM_2020_HOOK_DOWN_SPEED_FACTOR, ARM_2020_HOOK_DOWN, wait);
}

unsigned int arm2020HookDownAll(ServoList* servoList, bool wait) {
    unsigned int hookIndex = 0;
    unsigned int result = 0;
    for (hookIndex = 0; hookIndex < ARM_2020_HOOK_COUNT; hookIndex++) {
        Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
        unsigned int timeToReach = pwmServo(servo, ARM_2020_HOOK_DOWN_SPEED_FACTOR, ARM_2020_HOOK_DOWN, false);
        if (timeToReach > result) {
            result = timeToReach;
        }
    }
    if (wait) {
        timerDelayMilliSeconds(result);
    }
    return result;
}

unsigned int arm2020HookUp(ServoList* servoList, unsigned char hookIndex, bool wait) {
    Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
    return pwmServo(servo, ARM_2020_HOOK_UP_SPEED_FACTOR, ARM_2020_HOOK_UP, wait);
}

unsigned int arm2020HookUpAll(ServoList* servoList, bool wait) {
    unsigned int hookIndex = 0;
    unsigned int result = 0;
    for (hookIndex = 0; hookIndex < ARM_2020_HOOK_COUNT; hookIndex++) {
        Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
        unsigned timeToReach = pwmServo(servo, ARM_2020_HOOK_UP_SPEED_FACTOR, ARM_2020_HOOK_UP, false);
        if (timeToReach > result) {
            result = timeToReach;
        }
    }
    if (wait) {
        timerDelayMilliSeconds(result);
    }
    return result;
}

unsigned int arm2020HookTake(ServoList* servoList, unsigned char hookIndex, bool wait) {
    Servo* servo = getServo(servoList, ARM_2020_HOOK_TAKE_SERVO_BASE_INDEX + hookIndex);
    return pwmServo(servo, ARM_2020_HOOK_TAKE_SPEED_FACTOR, ARM_2020_HOOK_TAKE, wait);
}

unsigned int arm2020HookTakeAll(ServoList* servoList, bool wait) {
    unsigned int result = 0;
    unsigned int hookIndex = 0;
    for (hookIndex = 0; hookIndex < ARM_2020_HOOK_COUNT; hookIndex++) {
        Servo* servo = getServo(servoList, ARM_2020_HOOK_TAKE_SERVO_BASE_INDEX + hookIndex);
        unsigned int timeToReach = pwmServo(servo, ARM_2020_HOOK_TAKE_SPEED_FACTOR, ARM_2020_HOOK_TAKE, false);
        if (timeToReach > result) {
            result = timeToReach;
        }
    }
    if (wait) {
        timerDelayMilliSeconds(result);
    }
    return result;
}

unsigned int arm2020HookRelease(ServoList* servoList, unsigned char hookIndex, bool wait) {
    Servo* servo = getServo(servoList, ARM_2020_HOOK_TAKE_SERVO_BASE_INDEX + hookIndex);
    return pwmServo(servo, ARM_2020_HOOK_RELEASE_SPEED_FACTOR, ARM_2020_HOOK_RELEASE, wait);
}

unsigned int arm2020HookReleaseAll(ServoList* servoList, bool wait) {
    unsigned int result = 0;
    unsigned int hookIndex = 0;
    for (hookIndex = 0; hookIndex < ARM_2020_HOOK_COUNT; hookIndex++) {
        Servo* servo = getServo(servoList, ARM_2020_HOOK_TAKE_SERVO_BASE_INDEX + hookIndex);
        unsigned int timeToReach = pwmServo(servo, ARM_2020_HOOK_RELEASE_SPEED_FACTOR, ARM_2020_HOOK_RELEASE, false);
        if (timeToReach > result) {
            result = timeToReach;
        }
    }
    if (wait) {
        timerDelayMilliSeconds(result);
    }
    return result;
}


// HOOK - COMPLEX

unsigned int arm2020HookPrepare(ServoList* servoList, unsigned char hookIndex, bool wait) {
    unsigned int releaseTime = arm2020HookRelease(servoList, hookIndex, wait);
    unsigned int downTime = arm2020HookDown(servoList, hookIndex, wait);
    if (releaseTime > downTime) {
        return releaseTime;
    }
    return downTime;
}

unsigned int arm2020HookPrepareAll(ServoList* servoList) {
    unsigned int releaseTime = arm2020HookReleaseAll(servoList, false);
    unsigned int downTime = arm2020HookDownAll(servoList, false);
    if (releaseTime > downTime) {
        return releaseTime;
    }
    return downTime;
}

unsigned int arm2020TakeAndUp(ServoList* servoList, unsigned char hookIndex, bool wait) {
    unsigned int takeTime = arm2020HookTake(servoList, hookIndex, true);
    unsigned int upTime = arm2020HookUp(servoList, hookIndex, wait);
    if (takeTime > upTime) {
        return takeTime;
    }
    return upTime;
}

unsigned int arm2020TakeAndUpAll(ServoList* servoList) {
    unsigned int takeTime = arm2020HookTakeAll(servoList, true);
    unsigned int upTime = arm2020HookUpAll(servoList, true);
    if (takeTime > upTime) {
        return takeTime;
    }
    return upTime;
}

unsigned int arm2020DownAndRelease(ServoList* servoList, unsigned char hookIndex, bool wait) {
    unsigned int downTime = arm2020HookDown(servoList, hookIndex, true);
    unsigned int releaseTime = arm2020HookRelease(servoList, hookIndex, false);
    if (downTime > releaseTime) {
        return downTime;
    }
    return releaseTime;
}

unsigned int arm2020DownAndReleaseAll(ServoList* servoList) {
    unsigned int downTime = arm2020HookDownAll(servoList, true);
    unsigned int releaseTime = arm2020HookReleaseAll(servoList, true);
    if (downTime > releaseTime) {
        return downTime;
    }
    return releaseTime;
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

