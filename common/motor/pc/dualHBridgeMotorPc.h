#ifndef DUAL_H_BRIDGE_MOTOR_PC_H
#define DUAL_H_BRIDGE_MOTOR_PC_H

#include "../dualHBridgeMotor.h"
#include "../../../common/io/pin.h"

/**
 * Init the DualHBridgeMotor for PC 
 */
void initDualHBridgeMotorPc(DualHBridgeMotor* dualHBridgeMotor, PinList* pinList);

#endif