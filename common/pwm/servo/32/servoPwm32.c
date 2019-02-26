#include <p32xxxx.h>
#include "../servoPwm.h"

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

/** For 50 Hz operation. */
#define PWM_TIMER_FOR_SERVO 0x30D4 // = 12500 decimal

/** For 50 Hz operation. */
#define PWM_DUTY_CYCLE_FOR_SERVO 20000

#define SERVO32_PWM_COUNT          5

// PRIVATE

/**
 * @private.
 * convert a duration in microseconds into integer value which must be applied in pwm.
 * @param microSeconds value in microSeconds
 * @return the value which must be applied in pwm.
 */
int _convPwmServo(int microSeconds) {
    long duty;

    duty = PWM_TIMER_FOR_SERVO * (long) microSeconds;
    duty = duty / PWM_DUTY_CYCLE_FOR_SERVO;
    duty = PWM_TIMER_FOR_SERVO - duty;
    return (int) duty;
}

/**
 * @private.
 * Convert a duty cycle (from the OCXRS value).
 */
int _confServoToPwm(int value) {
    long result;

    result = value * PWM_DUTY_CYCLE_FOR_SERVO;
    result = value / PWM_TIMER_FOR_SERVO;

    return (int) result;
}

// INIT

void __internalInitPwmServo(int servoIndex) {
    if (servoIndex == 1) {
        OpenOC1(OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
    }
    else if (servoIndex == 2) {
        OpenOC2(OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
    }
    else if (servoIndex == 3) {
        OpenOC3(OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
    }
    else if (servoIndex == 4) {
        OpenOC4(OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
    }
    else if (servoIndex == 5) {
        OpenOC5(OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
    }
}

void __internalPwmForServoHardware(unsigned int servoEnabledMask, 
                                   int posInit) {
    if (servoEnabledMask == 0) {
        return;
    }
    unsigned int i;
    for (i = 0; i < PWM_COUNT; i++) {
        if ((1 << i) & servoEnabledMask) {
            __internalInitPwmServo(i + 1);
        }
    }

    // Launch the relating timer
    OpenTimer2(T2_ON | T2_PS_1_64 | T2_SOURCE_INT, PWM_TIMER_FOR_SERVO);

    /*
    unsigned int servoIndex;
    for (servoIndex = 1; servoIndex <= SERVO32_PWM_COUNT; servoIndex++) {
        __internalPwmServo(servoIndex, posInit);
    }
    */
}

void __internalPwmServo(Servo* servo, int dutyms) {

    switch (servo->internalServoIndex) {
        case 1:
        {
            OC1RS = _convPwmServo(dutyms);
            break;
        }
        case 2:
        {
            OC2RS = _convPwmServo(dutyms);
            break;
        }
        case 3:
        {
            OC3RS = _convPwmServo(dutyms);
            break;
        }
        case 4:
        {
            OC4RS = _convPwmServo(dutyms);
            break;
        }
        case 5:
        {
            OC5RS = _convPwmServo(dutyms);
            break;
        }
    }
}