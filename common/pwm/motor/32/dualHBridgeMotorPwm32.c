#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

#include <stdlib.h>

#include "../../../../common/error/error.h"
#include "../../../../common/setup/32/clockConstants32.h"
#include "../../../../common/io/pin.h"

#include "../../pwmPic.h"

#include "../dualHBridgeMotorPwm.h"

/** For 20 000 Hz operation. */
#define PWM_TIMER_FOR_MOTOR         0x001C

/** For 20 000 Hz operation. */
#define PWM_DUTY_CYCLE_FOR_MOTOR     255L


#define HBRIGE_1_DIRECTION_PIN    PORTDbits.RD6
#define HBRIGE_2_DIRECTION_PIN    PORTDbits.RD7

/**
 * @private
 * Method utils
 * @param pwm
 * @return 
 */
int convPwmMotor(int pwm) {
    long duty;
    duty = PWM_TIMER_FOR_MOTOR * (long) pwm;
    duty = duty / PWM_DUTY_CYCLE_FOR_MOTOR;

    return (int) duty;
}

bool initPwmForMotor(DualHBridgeMotor* dualHBridgeMotor) {
    // Port as output to control the direction of the motors
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD7 = 0;

    OpenOC1( OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
    OpenOC2( OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);

    OpenTimer2(T2_ON|T2_PS_1_64 | T2_SOURCE_INT, PWM_TIMER_FOR_MOTOR);

    OC1RS = (0x0000); // 0 % duty cycle
    OC2RS = (0x0000); // 0 % duty cycle
    
    return true;
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

void pwmDualHBridgeMotor(DualHBridgeMotor* dualHBridgeMotor, signed int hBridgeSpeed1, signed int hBridgeSpeed2) {
    if (hBridgeSpeed1 < 0) {
        HBRIGE_1_DIRECTION_PIN = 0;
        if (hBridgeSpeed1 < - DUAL_HBRIDGE_MOTOR_PWM_MAX) {
            pwmMotor1(DUAL_HBRIDGE_MOTOR_PWM_MAX);
        } else {
            pwmMotor1(-hBridgeSpeed1);
        }
    }
    else {
        HBRIGE_1_DIRECTION_PIN = 1;
        if (hBridgeSpeed1 > DUAL_HBRIDGE_MOTOR_PWM_MAX) {
            pwmMotor1(DUAL_HBRIDGE_MOTOR_PWM_MAX);
        } else {
            pwmMotor1(hBridgeSpeed1);
        }
    }
    if (hBridgeSpeed2 < 0) {
       HBRIGE_2_DIRECTION_PIN = 0;
       if (hBridgeSpeed2 < -DUAL_HBRIDGE_MOTOR_PWM_MAX) {
            pwmMotor2(DUAL_HBRIDGE_MOTOR_PWM_MAX);
        } else {
            pwmMotor2(-hBridgeSpeed2);
        }
    }
    else {
        HBRIGE_2_DIRECTION_PIN = 1;
        if (hBridgeSpeed2 > DUAL_HBRIDGE_MOTOR_PWM_MAX) {
            pwmMotor2(DUAL_HBRIDGE_MOTOR_PWM_MAX);
        } else {
            pwmMotor2(hBridgeSpeed2);
        }
    }
    dualHBridgeMotor->motorSpeed1 = hBridgeSpeed1;
    dualHBridgeMotor->motorSpeed2 = hBridgeSpeed2;
}

signed int dualHBridgeMotorReadValuePwm32(DualHBridgeMotor* dualHBridgeMotor, unsigned int motorIndex) {
    if (motorIndex == HBRIDGE_1) {
        return dualHBridgeMotor->motorSpeed1;
    }
    else if (motorIndex == HBRIDGE_2) {
        return dualHBridgeMotor->motorSpeed2;
    }
    // TODO : raise an error
    return 0;
}

/**
* DualHBridgeMotor implementation (POO)
* @private
*/
unsigned char dualHBridgeMotorGetSoftwareRevisionPwm32(DualHBridgeMotor* dualHBridgeMotor) {
    return 1;
}

void initDualHBridgeMotorPWM(DualHBridgeMotor* dualHBridgeMotor) {
    initDualHBridge(dualHBridgeMotor,
                    &initPwmForMotor,
                    &dualHBridgeMotorReadValuePwm32,
                    &pwmDualHBridgeMotor,
                    &dualHBridgeMotorGetSoftwareRevisionPwm32,
                    NULL);
}
