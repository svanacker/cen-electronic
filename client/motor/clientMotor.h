#ifndef CLIENT_MOTOR_H
#define CLIENT_MOTOR_H

#include <stdbool.h>

#include "../../common/motor/dualHBridgePin.h"
#include "../../device/motor/pwmMotorDeviceInterface.h"

/**
 * Client Stub to send instruction to move motor
 */
bool clientMotorWrite(signed int motorValue1, signed int motorValue2);

/**
 * Client stub to send instruction to stop the motor.
 * @return 
 */
bool clientMotorStop(void);

/**
 * Client stub to specify the pin and the stop usage of pin
 */
bool clientMotorSetPinUsage(enum DualHBridgePinUsageType pinUsageType1, 
                            enum DualHBridgePinUsageType pinUsageType2,
                            enum DualHBridgePinStopEventType pinStopEventType1,
                            enum DualHBridgePinStopEventType pinStopEventType2);


#endif
