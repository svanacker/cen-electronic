#ifndef DUAL_HBRIDGE_MOTOR_MD22_H
#define DUAL_HBRIDGE_MOTOR_MD22_H

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
