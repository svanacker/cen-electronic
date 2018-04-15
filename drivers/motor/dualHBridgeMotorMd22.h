#ifndef DUAL_HBRIDGE_MOTOR_MD22_H
#define DUAL_HBRIDGE_MOTOR_MD22_H

// Value in MD22 is at 0x00 at full reverse speed, 0x80 is stopping value, 0xFF is full forward speed
#define MD22_OFFSET_VALUE       0x80

/**
 * Implementation of DualHBridgeMotor "Interface" for MD22.
 */
#include "../../common/motor/dualHBridgeMotor.h"
#include "../../common/i2c/i2cBusConnectionList.h"

I2cBusConnection* getDualHBridgeMotorMD22I2cBusConnection(DualHBridgeMotor* dualHBridgeMotor);

/**
 * Init the MD22 according to DualHBridgeMotor interface
 */
void initDualHBridgeMotorMD22(DualHBridgeMotor* dualHBridgeMotor, I2cBusConnection* i2cBusConnection);

#endif
