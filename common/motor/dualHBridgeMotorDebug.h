#ifndef DUAL_H_BRIDGE_MOTOR_DEBUG
#define DUAL_H_BRIDGE_MOTOR_DEBUG

#include <stdbool.h>

#include "../../common/io/outputStream.h"

#include "dualHBridgeMotor.h"

/**
* Print the String equivalent value of DualHBridgePinUsageType in an outputStream.
*/
unsigned int appendDualHBridgePinUsageTypeAsString(OutputStream* outputStream, enum DualHBridgePinUsageType usageType);

/**
* Append in a table the usage of the IO Pin for Motor in an outputStream.
*/
unsigned int addDualHBridgePinUsageTypeTableData(OutputStream* outputStream, enum DualHBridgePinUsageType usageType, int columnSize);

/**
* Print the String equivalent value of DualHBridgePinStopEventType in an outputStream.
*/
unsigned int appendDualHBridgePinStopEventTypeAsString(OutputStream* outputStream, enum DualHBridgePinStopEventType stopEventType);

/**
* Append in a table the usage of the IO Pin for Motor in an outputStream.
*/
unsigned int addDualDualHBridgePinStopEventTypeTableData(OutputStream* outputStream, enum DualHBridgePinStopEventType stopEventType, int columnSize);

/**
* Print a table with the value of HBridge Value (especially pin Usage).
*/
void printMotorDebug(OutputStream* outputStream, const DualHBridgeMotor* dualHBridge);

#endif
