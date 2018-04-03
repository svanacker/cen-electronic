#include "dualHBridgeMotorPc.h"

#include <stdlib.h>

#include "../dualHBridgeMotor.h"

/**
* DualHBridgeMotor implementation (POO)
* @private
*/
signed int dualHBridgeMotorReadValuePc(DualHBridgeMotor* dualHBridgeMotor, unsigned int motorIndex) {
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
void dualHBridgeMotorWriteValuePc(DualHBridgeMotor* dualHBridgeMotor, signed int hBridgeSpeed1, signed int hBridgeSpeed2) {
    dualHBridgeMotor->motorSpeed1 = hBridgeSpeed1;
    dualHBridgeMotor->motorSpeed2 = hBridgeSpeed2;
}

/**
* DualHBridgeMotor implementation (POO)
* @private
*/
unsigned char dualHBridgeMotorGetSoftwareRevisionPc(DualHBridgeMotor* dualHBridgeMotor) {
    return 1;
}

/**
* DualHBridgeMotor implementation (POO)
* @private
*/
bool dualHBridgeMotorInitPc(DualHBridgeMotor* dualHBridgeMotor) {
    dualHBridgeMotorWriteValuePc(dualHBridgeMotor, 0, 0);
    return true;
}

void initDualHBridgeMotorPc(DualHBridgeMotor* dualHBridgeMotor) {
    initDualHBridge(dualHBridgeMotor,
                    &dualHBridgeMotorInitPc,
                    &dualHBridgeMotorReadValuePc,
                    &dualHBridgeMotorWriteValuePc,
                    &dualHBridgeMotorGetSoftwareRevisionPc,
                    NULL);
}