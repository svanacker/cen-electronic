#ifndef DUAL_H_BRIDGE_MOTOR_PWM
#define DUAL_H_BRIDGE_MOTOR_PWM

#define HBRIDGE_1        1
#define HBRIDGE_2        2

/**
 * Init the pwm for 20 000 Hz operation.
 */
void initPwmForDualHBridge(void);

#define MAX_PWM 250

/**
 * For a dual HBridge, manage 4 pwms (either 4 pwms in 30F, or 2 pwms and 2 pin directions on PIC32).
 * @param hBridgeSpeed1 between -255 and + 255
 * @param hBridgeSpeed2 between -255 and + 255
 */
void pwmDualHBridgeMotor(signed int hBridgeSpeed1, signed int hBridgeSpeed2);

/**
 * Returns the speed for the first motor of the bridge.
 * @return the speed for the first motor of the bridge. 
 */
signed int getDualHBridgeSpeed1(void);

/**
* Returns the speed for the second motor of the bridge.
* @return the speed for the second motor of the bridge.
*/
signed int getDualHBridgeSpeed2(void);

#endif
