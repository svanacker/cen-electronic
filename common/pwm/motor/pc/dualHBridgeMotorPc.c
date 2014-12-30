#include "../dualHBridgeMotorPwm.h"

static signed int motorSpeed1;
static signed int motorSpeed2;

void initPwmForDualHBridge(void) {
    motorSpeed1 = 0;
    motorSpeed2 = 0;
}

void pwmMotor1(signed int value1) {
    motorSpeed1 = value1;
}

void pwmMotor2(signed int value2) {
    motorSpeed2 = value2;
}

void pwmMotor3(signed int value3) {
    // DON'T DO ANYTHING    
}

void pwmMotor4(signed int value4) {
    // DON'T DO ANYTHING    
}

signed int getDualHBridgeSpeed1(void) {
    return motorSpeed1;
}

signed int getDualHBridgeSpeed2(void) {
    return motorSpeed2;
}

void pwmDualHBridgeMotor(signed int hBridgeSpeed1, signed int hBridgeSpeed2) {
    if (hBridgeSpeed1 < 0) {
        if (hBridgeSpeed1 < -MAX_PWM) {
            pwmMotor1(-MAX_PWM);
        } else {
            pwmMotor1(hBridgeSpeed1);
        }
    }
    else {
        if (hBridgeSpeed1 > MAX_PWM) {
            pwmMotor1(MAX_PWM);
        } else {
            pwmMotor1(hBridgeSpeed1);
        }
    }
    if (hBridgeSpeed2 < 0) {
       if (hBridgeSpeed2 < -MAX_PWM) {
            pwmMotor2(-MAX_PWM);
        } else {
            pwmMotor2(hBridgeSpeed2);
        }
    }
    else {
        if (hBridgeSpeed2 > MAX_PWM) {
            pwmMotor2(MAX_PWM);
        } else {
            pwmMotor2(hBridgeSpeed2);
        }
    }
}