#include <plib.h>
#include <peripheral/ports.h>

#include "../../../../common/error/error.h"

#include "../../pwmPic.h"
#include "../motorPwm.h"

#include "../dualHBridgeMotorPwm.h"

#define HBRIGE_1_DIRECTION_PIN    PORTDbits.RD6
#define HBRIGE_2_DIRECTION_PIN    PORTDbits.RD7

static signed int motorSpeed1;
static signed int motorSpeed2;

signed int getDualHBridgeSpeed1(void) {
    return motorSpeed1;
}

signed int getDualHBridgeSpeed2(void) {
    return motorSpeed2;
}

void initPwmForDualHBridge() {
    // Port as output to control the direction of the motors
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD7 = 0;

    // Init pwm as usual
    initPwmForMotor();
}

void pwmDualHBridgeMotor(signed int hBridgeSpeed1, signed int hBridgeSpeed2) {
    if (hBridgeSpeed1 < 0) {
        HBRIGE_1_DIRECTION_PIN = 0;
        if (hBridgeSpeed1 < -MAX_PWM) {
            pwmMotor1(MAX_PWM);
        } else {
            pwmMotor1(-hBridgeSpeed1);
        }
    }
    else {
        HBRIGE_1_DIRECTION_PIN = 1;
        if (hBridgeSpeed1 > MAX_PWM) {
            pwmMotor1(MAX_PWM);
        } else {
            pwmMotor1(hBridgeSpeed1);
        }
    }
    if (hBridgeSpeed2 < 0) {
       HBRIGE_2_DIRECTION_PIN = 0;
       if (hBridgeSpeed2 < -MAX_PWM) {
            pwmMotor2(MAX_PWM);
        } else {
            pwmMotor2(-hBridgeSpeed2);
        }
    }
    else {
        HBRIGE_2_DIRECTION_PIN = 1;
        if (hBridgeSpeed2 > MAX_PWM) {
            pwmMotor2(MAX_PWM);
        } else {
            pwmMotor2(hBridgeSpeed2);
        }
    }
    // TODO : Improve it
    motorSpeed1 = hBridgeSpeed1;
    motorSpeed2 = hBridgeSpeed2;
}