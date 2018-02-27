#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

#include "../../../../common/error/error.h"
#include "../../../../common/setup/32/clockConstants32.h"

#include "../../pwmPic.h"

/** For 20 000 Hz operation. */
#define PWM_TIMER_FOR_MOTOR         0x001C

/** For 20 000 Hz operation. */
#define PWM_DUTY_CYCLE_FOR_MOTOR     255L

int convPwmMotor(int pwm) {
    long duty;
    duty = PWM_TIMER_FOR_MOTOR * (long) pwm;
    duty = duty / PWM_DUTY_CYCLE_FOR_MOTOR;

    return (int) duty;
}







void initPwmForMotor() {
    OpenOC1( OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE , 0,0 );
    OpenOC2( OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE , 0,0 );

    OpenTimer2(T2_ON|T2_PS_1_64 | T2_SOURCE_INT, PWM_TIMER_FOR_MOTOR);

    OC1RS = (0x0000); // 0 % duty cycle
    OC2RS = (0x0000); // 0 % duty cycle
}

void pwmMotor1(int dutyms) {
    OC1RS = convPwmMotor(dutyms); //duty cycle OC2
}

void pwmMotor2(int dutyms) {
    OC2RS = convPwmMotor(dutyms); //duty cycle OC2
}

void pwmMotor3(int dutyms) {
    // Take by UART 1
    writeError(PWM_NOT_AVAILABLE);
}

void pwmMotor4(int dutyms) {
    // Take by UART 1 => We use direction with D6 and D7 !
    writeError(PWM_NOT_AVAILABLE);
}

