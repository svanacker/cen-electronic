#ifndef SERVO_PWM_32_H
#define SERVO_PWM_32_H

#include "../../../../common/pwm/servo/servoPwm.h"

/**
 * Exposed in H file just to be consumed by common/pwm/servo/32 package
 * @package
 * @param servo
 */
void _internalTypeInitPwmServo32(enum ServoType servoType, int* object);

/**
 * Exposed in H file just to be consumed by common/pwm/servo/32 package
 * @package
 * @param servo
 */
void _internalInitPwmServo32(Servo* servo);

/**
 * Exposed in H file just to be consumed by common/pwm/servo/32 package
 * @package
 * @param servo
 */
void _internalUpdateConfigServo32(Servo* servo);

/**
 * Exposed in H file just to be consumed by common/pwm/servo/32 package
 * @package
 * @param servo
 * @param dutyms
 */
void _servoInternalPwm32 (Servo* servo, unsigned int dutyms);

#endif
