#ifndef DUAL_H_BRIDGE_MOTOR_PWM
#define DUAL_H_BRIDGE_MOTOR_PWM

#include <stdbool.h>

#include "../../../common/motor/dualHBridgeMotor.h"

/** Define the max value for the PWM applied to the motors */
#define DUAL_HBRIDGE_MOTOR_PWM_MAX        250

/**
 * Init the pwm (try 20 000 Hz operation to avoid noise).
 */
void initDualHBridgeMotorPWM(DualHBridgeMotor* dualHBridgeMotor);

#endif
