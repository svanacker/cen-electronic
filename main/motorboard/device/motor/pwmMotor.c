#include "../../common/pwm/motorPwm.h"

#define MAX_PWM 250

#define BACK_VALUE_FOR_PWM 255

void setMotorSpeeds(signed int leftSpeed, signed int rightSpeed) {
    // LEFT
    if (leftSpeed < 0) {
        // pwm2 => sense of left motor
        pwmMotor2(BACK_VALUE_FOR_PWM);
        if (leftSpeed < -MAX_PWM) {
            pwmMotor1(MAX_PWM);
        } else {
            pwmMotor1(-leftSpeed);
        }
    } else {
        pwmMotor2(0);
        if (leftSpeed > MAX_PWM) {
            pwmMotor1(MAX_PWM);
        } else {
            pwmMotor1(leftSpeed);
        }
    }

    // RIGHT
    if (rightSpeed < 0) {
        // pwm4 => sense of right motor
        pwmMotor4(BACK_VALUE_FOR_PWM);
        if (rightSpeed < -MAX_PWM) {
            pwmMotor3(MAX_PWM);
        } else {
            pwmMotor3(-rightSpeed);
        }
    } else {
        pwmMotor4(0);
        if (rightSpeed > MAX_PWM) {
            pwmMotor3(MAX_PWM);
        } else {
            pwmMotor3(rightSpeed);
        }
    }
}

void stopMotors(void) {
    setMotorSpeeds(0, 0);
}
