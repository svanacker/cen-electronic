#include <p32xxxx.h>
#include "servoPwm32.h"
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

// FIRST INIT (for all pwm)

void _internalTypeInitPwmServo32(enum ServoType servoType, int* object) {
    OpenTimer2(T2_ON | T2_PS_1_64 | T2_SOURCE_INT, PWM_TIMER_FOR_SERVO);
}

// INIT (for each pwm)

void _internalInitPwmServo32(Servo* servo) {
    // Nothing to do
}

void _internalUpdateConfigServo32(Servo* servo) {
    unsigned int internalServoIndex = servo->internalServoIndex;
    unsigned int enabled = servo->enabled;
    if (internalServoIndex == 1) {
        if (enabled) {
            OpenOC1(OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
        }
        else {
            CloseOC1();
        }
    }
    else if (internalServoIndex == 2) {
        if (enabled) {
            OpenOC2(OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
        }
        else {
            CloseOC2();
        }
    }
    else if (internalServoIndex == 3) {
        if (enabled) {
            OpenOC3(OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
        }
        else {
            CloseOC3();
        }
    }
    else if (internalServoIndex == 4) {
        if (enabled) {
            OpenOC4(OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
        }
        else {
            CloseOC4();
        }
    }
    else if (internalServoIndex == 5) {
        if (enabled) {
            OpenOC5(OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
        }
        else {
            CloseOC5();
        }
    } 
}

/**
 * @private
 * Implementation of ServoInternalPwmFunction
 * @param servo
 * @param dutyms
 */
void _servoInternalPwm32 (Servo* servo, unsigned int dutyms) {
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
