#include "arm2020.h"

#include "../../../common/pwm/servo/servoPwm.h"

// ARM

void arm2020(ServoList* servoList, unsigned char leftRightCenter) {
    Servo* servo = getServo(servoList, ARM_2020_SERVO_INDEX);
    if (leftRightCenter == 0x00) {
        pwmServo(servo, ARM_2020_ARM_SPEED_FACTOR, ARM_2020_ARM_SERVO_MIDDLE, false);
    }
    else if (leftRightCenter == 0x01) {
        pwmServo(servo, ARM_2020_ARM_SPEED_FACTOR, ARM_2020_ARM_SERVO_LEFT, false);
    }
    else if (leftRightCenter == 0x02) {
        pwmServo(servo, ARM_2020_ARM_SPEED_FACTOR, ARM_2020_ARM_SERVO_RIGHT, false);
    }
}

// FLAG

void arm2020FlagDown(ServoList* servoList) {
    Servo* servo = getServo(servoList, ARM_2020_FLAG_SERVO_INDEX);
    pwmServo(servo, ARM_2020_FLAG_SPEED_FACTOR, ARM_2020_FLAG_DOWN, false);
}

void arm2020FlagUp(ServoList* servoList) {
    Servo* servo = getServo(servoList, ARM_2020_FLAG_SERVO_INDEX);
    pwmServo(servo, ARM_2020_FLAG_SPEED_FACTOR, ARM_2020_FLAG_UP, false);    
}

// HOOK

void arm2020HookDown(ServoList* servoList, unsigned char hookIndex, bool wait) {
    Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
    pwmServo(servo, ARM_2020_HOOK_DOWN_SPEED_FACTOR, ARM_2020_HOOK_DOWN, wait);
}

void arm2020HookDownAll(ServoList* servoList) {
    unsigned int hookIndex = 0;
    for (hookIndex = 0; hookIndex < ARM_2020_HOOK_COUNT; hookIndex++) {
        Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
        pwmServo(servo, ARM_2020_HOOK_DOWN_SPEED_FACTOR, ARM_2020_HOOK_DOWN, false);
    }
}

void arm2020HookUp(ServoList* servoList, unsigned char hookIndex, bool wait) {
    Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
    pwmServo(servo, ARM_2020_HOOK_UP_SPEED_FACTOR, ARM_2020_HOOK_UP, wait);
}

void arm2020HookUpAll(ServoList* servoList) {
    unsigned int hookIndex = 0;
    for (hookIndex = 0; hookIndex < ARM_2020_HOOK_COUNT; hookIndex++) {
        Servo* servo = getServo(servoList, ARM_2020_HOOK_VERTICAL_SERVO_BASE_INDEX + hookIndex);
        pwmServo(servo, ARM_2020_HOOK_UP_SPEED_FACTOR, ARM_2020_HOOK_UP, false);
    }
}

void arm2020HookTake(ServoList* servoList, unsigned char hookIndex, bool wait) {
    Servo* servo = getServo(servoList, ARM_2020_HOOK_TAKE_SERVO_BASE_INDEX + hookIndex);
    pwmServo(servo, ARM_2020_HOOK_TAKE_SPEED_FACTOR, ARM_2020_HOOK_TAKE, wait);
}

void arm2020HookTakeAll(ServoList* servoList) {
    unsigned int hookIndex = 0;
    for (hookIndex = 0; hookIndex < ARM_2020_HOOK_COUNT; hookIndex++) {
        Servo* servo = getServo(servoList, ARM_2020_HOOK_TAKE_SERVO_BASE_INDEX + hookIndex);
        pwmServo(servo, ARM_2020_HOOK_TAKE_SPEED_FACTOR, ARM_2020_HOOK_TAKE, false);
    }
}

void arm2020HookRelease(ServoList* servoList, unsigned char hookIndex, bool wait) {
    Servo* servo = getServo(servoList, ARM_2020_HOOK_TAKE_SERVO_BASE_INDEX + hookIndex);
    pwmServo(servo, ARM_2020_HOOK_RELEASE_SPEED_FACTOR, ARM_2020_HOOK_RELEASE, wait);
}

void arm2020HookReleaseAll(ServoList* servoList) {
    unsigned int hookIndex = 0;
    for (hookIndex = 0; hookIndex < ARM_2020_HOOK_COUNT; hookIndex++) {
        Servo* servo = getServo(servoList, ARM_2020_HOOK_TAKE_SERVO_BASE_INDEX + hookIndex);
        pwmServo(servo, ARM_2020_HOOK_RELEASE_SPEED_FACTOR, ARM_2020_HOOK_RELEASE, false);
    }
}


// HOOK - COMPLEX

void arm2020HookPrepare(ServoList* servoList, unsigned char hookIndex) {
    arm2020HookRelease(servoList, hookIndex, false);
    arm2020HookDown(servoList, hookIndex, true);
}

void arm2020HookPrepareAll(ServoList* servoList) {
    unsigned int hookIndex = 0;
    for (hookIndex = 0; hookIndex < ARM_2020_HOOK_COUNT; hookIndex++) {
        arm2020HookRelease(servoList, hookIndex, false);
        arm2020HookDown(servoList, hookIndex, false);
    }
}

void arm2020TakeAndUp(ServoList* servoList, unsigned char hookIndex) {
    arm2020HookTake(servoList, hookIndex, true);
    arm2020HookUp(servoList, hookIndex, true);
}

void arm2020TakeAndUpAll(ServoList* servoList) {
    unsigned int hookIndex = 0;
    for (hookIndex = 0; hookIndex < ARM_2020_HOOK_COUNT; hookIndex++) {
        arm2020HookTake(servoList, hookIndex, false);
        arm2020HookUp(servoList, hookIndex, false);
    }
}

void arm2020DownAndRelease(ServoList* servoList, unsigned char hookIndex) {
    arm2020HookDown(servoList, hookIndex, true);
    arm2020HookRelease(servoList, hookIndex, true);
}

void arm2020DownAndReleaseAll(ServoList* servoList) {
    unsigned int hookIndex = 0;
    for (hookIndex = 0; hookIndex < ARM_2020_HOOK_COUNT; hookIndex++) {
        arm2020HookDown(servoList, hookIndex, false);
        arm2020HookRelease(servoList, hookIndex, false);
    }
}
