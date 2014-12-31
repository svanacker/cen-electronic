#ifndef MOTOR_PWM_H
#define MOTOR_PWM_H

/**
 * Init the pwm for 20 000 Hz operation
 * Use TIMER2
 */
void initPwmForMotor();

/**
 * Change the pwm 1 for a motor mode
 * @param pwm value between 0 and 255
 */
void pwmMotor1(unsigned int pwm);

/**
 * Change the pwm 2 for a motor mode
 * @param pwm value between 0 and 255
 */
void pwmMotor2(unsigned int pwm);

/**
 * Change the pwm 3 for a motor mode
 * @param pwm value between 0 and 255
 */
void pwmMotor3(unsigned int pwm);

/**
 * Change the pwm 4 for a motor mode
 * @param pwm value between 0 and 255
 */
void pwmMotor4(unsigned int pwm);

/**
 * Change the selected pwm for a motor mode
 * @param pwm value between 0 and 255, raises an error if < 0
 */
void pwmMotor(int pwmIndex, int pwm);

#endif
