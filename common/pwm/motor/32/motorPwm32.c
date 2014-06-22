#include <p32xxxx.h>
#include <plib.h>

#include "../../../../common/commons.h"
#include "../../../../common/error/error.h"
#include "../../../../common/setup/32/clockConstants32.h"

#include "../../pwmPic.h"

/** For 20 000 Hz operation. */
#define PWM_TIMER_FOR_MOTOR 		0x0FBF

/** For 20 000 Hz operation. */
#define PWM_DUTY_CYCLE_FOR_MOTOR 	255L

int convPwmMotor(int pwm) {
    long duty;
    duty = PWM_TIMER_FOR_MOTOR * (long) pwm;
    duty = duty / PWM_DUTY_CYCLE_FOR_MOTOR;

    return (int) duty;
}

void initPwmForMotor() {
    // T = 1 / motor powser hash frequency (microsec)
    int PR20 = 50 * (FOSC / 2000000);  // pour 20khz => PR20 = 7D0
    OpenOC1( OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
    OpenOC2( OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);

    OpenTimer2( T2_ON | T2_PS_1_1 | T2_SOURCE_INT , PR20);
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

