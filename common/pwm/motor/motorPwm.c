#include "../../../common/error/error.h"

#include "../pwmPic.h"

#include "motorPwm.h"

void pwmMotor(int pwmIndex, int pwmValue) {
    if (pwmValue < 0) {
        writeError(PWM_VALUE_MUST_BE_POSITIVE);
    }
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
