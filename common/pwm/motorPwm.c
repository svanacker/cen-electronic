#include "../../common/commons.h"

#include "pwmPic.h"
#include "motorPwm.h"

void pwmMotor(int pwmIndex, int pwmValue) {
    switch (pwmIndex) {
        case 1: {
            pwmMotor1(pwmValue);
            break;
        }
        case 2: {
           pwmMotor2(pwmValue);
            break;
        }
        case 3: {
            pwmMotor3(pwmValue);
            break;
        }
        case 4: {
            pwmMotor4(pwmValue);
            break;
        }
    }
}


void pwmMotor1(int dutyms) {
// TODO    OC1RS = convPwmMotor(dutyms); //duty cycle OC2
}

void pwmMotor2(int dutyms) {
// TODO    OC2RS = convPwmMotor(dutyms); //duty cycle OC2
}

void pwmMotor3(int dutyms) {
// TODO    OC3RS = convPwmMotor(dutyms); //duty cycle OC3
}

void pwmMotor4(int dutyms) {
// TODO    OC4RS = convPwmMotor(dutyms); //duty cycle OC4
}
