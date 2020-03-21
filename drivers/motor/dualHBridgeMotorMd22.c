#include "dualHBridgeMotorMd22.h"
#include "md22.h"

#include "../../common/i2c/i2cCommon.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include <stdbool.h>

/**
 * Returns the I2cBusConnection related to the MD22 Dual HBridge Motor
 * @param dualHBridgeMotor
 * @return 
 */
I2cBusConnection* getDualHBridgeMotorMD22I2cBusConnection(DualHBridgeMotor* dualHBridgeMotor) {
    return (I2cBusConnection*) dualHBridgeMotor->object;
}

/**
 * DualHBridgeMotor function implementation.
 * @private
 * @param dualHBridgeMotor
 * @return 
 */
bool dualHBridgeMotorInitMD22(DualHBridgeMotor* dualHBridgeMotor) {
    I2cBusConnection* i2cBusConnection = getDualHBridgeMotorMD22I2cBusConnection(dualHBridgeMotor);
    initMD22(i2cBusConnection);
}

/**
 * DualHBridgeMotor function implementation.
 * @param DualHBridgeMotor
 * @param motorIndex
 * @return 
 */
signed int dualHBridgeMotorReadValueMD22(DualHBridgeMotor* dualHBridgeMotor, unsigned int motorIndex) {
    if (motorIndex == HBRIDGE_1) {
        return dualHBridgeMotor->motorSpeed1;
    } else if (motorIndex == HBRIDGE_2) {
        return dualHBridgeMotor->motorSpeed2;
    }
    // TODO : raise an error
    return 0;
}

/**
 * DualHBridgeMotor function implementation.
 * @param DualHBridgeMotor
 * @param motorIndex
 * @return 
 */
unsigned char dualHBridgeMotorGetSoftwareRevisionMD22(DualHBridgeMotor* dualHBridgeMotor) {
    I2cBusConnection* i2cBusConnection = getDualHBridgeMotorMD22I2cBusConnection(dualHBridgeMotor);
    return getMD22Version(i2cBusConnection);
}

/**
 * DualHBridgeMotor function implementation.
 * @param dualHBridgeMotor
 * @param hBridgeSpeed1
 * @param hBridgeSpeed2
 */
void dualHBridgeMotorWriteValueMD22(DualHBridgeMotor* dualHBridgeMotor, signed int hBridgeSpeed1, signed int hBridgeSpeed2) {
    I2cBusConnection* i2cBusConnection = getDualHBridgeMotorMD22I2cBusConnection(dualHBridgeMotor);
    setMD22MotorSpeeds(i2cBusConnection, hBridgeSpeed1 + MD22_OFFSET_VALUE, hBridgeSpeed2 + MD22_OFFSET_VALUE);
    dualHBridgeMotor->motorSpeed1 = hBridgeSpeed1;
    dualHBridgeMotor->motorSpeed2 = hBridgeSpeed2;
}

void initDualHBridgeMotorMD22(DualHBridgeMotor* dualHBridgeMotor, I2cBusConnection* i2cBusConnection) {
    initDualHBridge(dualHBridgeMotor,
            dualHBridgeMotorInitMD22,
            dualHBridgeMotorReadValueMD22,
            dualHBridgeMotorWriteValueMD22,
            dualHBridgeMotorGetSoftwareRevisionMD22,
            (int*) i2cBusConnection);
}
