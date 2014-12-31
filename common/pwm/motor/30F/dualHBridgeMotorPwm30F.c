#include "../../../../common/error/error.h"

#include "../../pwmPic.h"

#include "../dualHBridgeMotorPwm.h"
#include "../motorPwm.h"

#define BACK_VALUE_FOR_PWM 255

static signed int motorSpeed1;
static signed int motorSpeed2;

void initPwmForDualHBridge() {
    initPwmForMotor();
}

signed int getDualHBridgeSpeed1(void) {
    return motorSpeed1;
}

signed int getDualHBridgeSpeed2(void) {
    return motorSpeed2;
}

void pwmDualHBridgeMotor(signed int hBridgeSpeed1, signed int hBridgeSpeed2) {
    if (hBridgeSpeed1 < 0) {
        // pwm2 => sense of left motor
        pwmMotor2(BACK_VALUE_FOR_PWM);
        if (hBridgeSpeed1 < -MAX_PWM) {
            pwmMotor1(MAX_PWM);
        } else {
            pwmMotor1(-hBridgeSpeed1);
        }
    } else {
        pwmMotor2(0);
        if (hBridgeSpeed1 > MAX_PWM) {
            pwmMotor1(MAX_PWM);
        } else {
            pwmMotor1(hBridgeSpeed1);
        }
    }
    if (hBridgeSpeed2 < 0) {
        // pwm4 => sense of right motor
        pwmMotor4(BACK_VALUE_FOR_PWM);
        if (hBridgeSpeed2 < -MAX_PWM) {
            pwmMotor3(MAX_PWM);
        } else {
            pwmMotor3(-hBridgeSpeed2);
        }
    } else {
        pwmMotor4(0);
        if (hBridgeSpeed2 > MAX_PWM) {
            pwmMotor3(MAX_PWM);
        } else {
            pwmMotor3(hBridgeSpeed2);
        }
    }
    // TODO : Improve it
    motorSpeed1 = hBridgeSpeed1;
    motorSpeed2 = hBridgeSpeed2;
}
