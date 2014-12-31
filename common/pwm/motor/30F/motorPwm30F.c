#include "../../../../common/pwm/pwmPic.h"

#include <p30Fxxxx.h>

/** For 20 000 Hz operation. */
#define PWM_TIMER_FOR_MOTOR 255

/** For 20 000 Hz operation. */
#define PWM_DUTY_CYCLE_FOR_MOTOR 255

int convPwmMotor(int pwm) {
    long duty;
    duty = PWM_TIMER_FOR_MOTOR * (long) pwm;
    duty = duty / PWM_DUTY_CYCLE_FOR_MOTOR;

    return (int) duty;
}

void initPwmForMotor() {
    // PR2 = [  period / ( Tosc * 4 * prediv) ] -1
    //    period = 20ms
    //    Tosc = 1 / frequency
    pwmInit();
    PR2 = PWM_TIMER_FOR_MOTOR; //periode TIMER2
    OC1RS = convPwmMotor(0); //duty cycle OC1
    OC2RS = convPwmMotor(0); //duty cycle OC2
    OC3RS = convPwmMotor(0); //duty cycle OC3
    OC4RS = convPwmMotor(0); //duty cycle OC4
    T2CONbits.TCKPS = 0b01; //prediviseur TIMER2 (0b10 => 64, 0b01 => 8)
    T2CONbits.TON = 1; //activation du TIMER2
}

void pwmMotor1(int dutyms) {
    OC1RS = convPwmMotor(dutyms); //duty cycle OC2
}

void pwmMotor2(int dutyms) {
    OC2RS = convPwmMotor(dutyms); //duty cycle OC2
}

void pwmMotor3(int dutyms) {
    OC3RS = convPwmMotor(dutyms); //duty cycle OC3
}

void pwmMotor4(int dutyms) {
    OC4RS = convPwmMotor(dutyms); //duty cycle OC4
}

