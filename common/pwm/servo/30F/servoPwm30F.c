#include <p30Fxxxx.h>

#include "../servoPwm.h"

/** For 50 Hz operation. */
#define PWM_TIMER_FOR_SERVO 9215

/** For 50 Hz operation. */
#define PWM_DUTY_CYCLE_FOR_SERVO 20000

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

void __internalPwmForServoHardware(int posInit) {
    // PR2 = [  period / ( Tosc * 4 * prediv) ] -1
    // period = 20ms
    // Tosc = 1 / frequency
    pwmInit();
    PR2 = PWM_TIMER_FOR_SERVO; // period TIMER2
    OC1RS = _convPwmServo(posInit); // duty cycle OC1
    OC2RS = _convPwmServo(posInit); // duty cycle OC2
    OC3RS = _convPwmServo(posInit); // duty cycle OC3
    OC4RS = _convPwmServo(posInit); // duty cycle OC4
    T2CONbits.TCKPS = 0b10; // predivisor TIMER2 (64)
    T2CONbits.TON = 1; // activate Timer2
}

// IMPLEMENTATION

void __internalPwmServo(int pwmIndex, int dutyms) {
    // Update the current Position of the servo
    switch (pwmIndex) {
        case 1:
        {
            OC1RS = _convPwmServo(dutyms); //duty cycle OC1
            break;
        }
        case 2:
        {
            OC2RS = _convPwmServo(dutyms); //duty cycle OC2
            break;
        }
        case 3:
        {
            OC3RS = _convPwmServo(dutyms); //duty cycle OC3
            break;
        }
        case 4:
        {
            OC4RS = _convPwmServo(dutyms); //duty cycle OC4
            break;
        }
    }
}
