#include "dualHBridgeMotor.h"


void initDualHBridge(DualHBridgeMotor* dualHBridgeMotor,
    dualHBridgeMotorInitFunction* dualHBridgeMotorInit,
    dualHBridgeMotorReadValueFunction* dualHBridgeMotorReadValue,
    dualHBridgeMotorWriteValueFunction* dualHBridgeMotorWriteValue,
    int* object) {
    dualHBridgeMotor->dualHBridgeMotorInit = dualHBridgeMotorInit;
    dualHBridgeMotor->dualHBridgeMotorReadValue = dualHBridgeMotorReadValue;
    dualHBridgeMotor->dualHBridgeMotorWriteValue = dualHBridgeMotorWriteValue;
    dualHBridgeMotor->object = object;
}

void stopMotors(DualHBridgeMotor* dualHBridgeMotor) {
    dualHBridgeMotor->dualHBridgeMotorWriteValue(dualHBridgeMotor, 0, 0);
}

void setMotorSpeeds(DualHBridgeMotor* dualHBridgeMotor, signed int hBridgeSpeed1, signed int hBridgeSpeed2) {
    dualHBridgeMotor->dualHBridgeMotorWriteValue(dualHBridgeMotor, hBridgeSpeed1, hBridgeSpeed2);
}