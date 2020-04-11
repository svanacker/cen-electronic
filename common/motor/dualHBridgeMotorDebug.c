#include "dualHBridgeMotorDebug.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "dualHBridgeMotor.h"

#define MOTOR_DEBUG_KEY_COLUMN_LENGTH				                          10
#define MOTOR_DEBUG_VALUE_COLUMN_LENGTH				                          30
#define MOTOR_DEBUG_LAST_COLUMN_LENGTH				                          50

unsigned int appendDualHBridgePinUsageTypeAsString(OutputStream* outputStream, enum DualHBridgePinUsageType usageType) {
    if (usageType == PIN_USAGE_TYPE_NO_USAGE) {
        return appendString(outputStream, "NO_USAGE");
    }
    else if (usageType == PIN_USAGE_TYPE_MOTOR_1_FORWARD_END) {
        return appendString(outputStream, "MOTOR_1_FORWARD_END");
    }
    else if (usageType == PIN_USAGE_TYPE_MOTOR_1_BACKWARD_END) {
        return appendString(outputStream, "MOTOR_1_BACKWARD_END");
    }
    else if (usageType == PIN_USAGE_TYPE_MOTOR_2_FORWARD_END) {
        return appendString(outputStream, "MOTOR_2_FORWARD_END");
    }
    else if (usageType == PIN_USAGE_TYPE_MOTOR_2_BACKWARD_END) {
        return appendString(outputStream, "MOTOR_2_BACKWARD_END");
    }
    else {
        append(outputStream, '?');
        return 1;
    }
    return 0;
}

unsigned int addDualHBridgePinUsageTypeTableData(OutputStream* outputStream, enum DualHBridgePinUsageType usageType, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendDualHBridgePinUsageTypeAsString(outputStream, usageType);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}

unsigned int appendDualHBridgePinStopEventTypeAsString(OutputStream* outputStream, enum DualHBridgePinStopEventType stopEventType) {
    if (stopEventType == PIN_STOP_EVENT_NO_ACTION) {
        return appendString(outputStream, "NO_ACTION");
    }
    else if (stopEventType == PIN_STOP_EVENT_LOW_STOP) {
        return appendString(outputStream, "LOW_STOP");
    }
    else if (stopEventType == PIN_STOP_EVENT_HIGH_STOP) {
        return appendString(outputStream, "HIGH_STOP");
    }
    else {
        append(outputStream, '?');
        return 1;
    }
    return 0;
}

unsigned int addDualDualHBridgePinStopEventTypeTableData(OutputStream* outputStream, enum DualHBridgePinStopEventType stopEventType, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendDualHBridgePinStopEventTypeAsString(outputStream, stopEventType);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}


/**
 * Private.
 */
void printMotorDebugHeader(OutputStream* outputStream) {
    appendTableHeaderSeparatorLine(outputStream);

    appendStringHeader(outputStream, "key", MOTOR_DEBUG_KEY_COLUMN_LENGTH);
    appendStringHeader(outputStream, "value", MOTOR_DEBUG_VALUE_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, MOTOR_DEBUG_LAST_COLUMN_LENGTH);

    appendTableHeaderSeparatorLine(outputStream);
}

void printMotorDebug(OutputStream* outputStream, const DualHBridgeMotor* dualHBridge) {
    // pin1UsageType
    appendStringTableData(outputStream, "pin1UsageType", MOTOR_DEBUG_KEY_COLUMN_LENGTH);
    appendDualHBridgePinUsageTypeAsString(outputStream, dualHBridge->pin1UsageType);
    appendEndOfTableColumn(outputStream, MOTOR_DEBUG_LAST_COLUMN_LENGTH);

    // pin2UsageType
    appendStringTableData(outputStream, "pin2UsageType", MOTOR_DEBUG_KEY_COLUMN_LENGTH);
    appendDualHBridgePinUsageTypeAsString(outputStream, dualHBridge->pin2UsageType);
    appendEndOfTableColumn(outputStream, MOTOR_DEBUG_LAST_COLUMN_LENGTH);

    // pin1StopEventType
    appendStringTableData(outputStream, "pin1StopEventType", MOTOR_DEBUG_KEY_COLUMN_LENGTH);
    appendDualHBridgePinStopEventTypeAsString(outputStream, dualHBridge->pin1StopEventType);
    appendEndOfTableColumn(outputStream, MOTOR_DEBUG_LAST_COLUMN_LENGTH);

    // pin2StopEventType
    appendStringTableData(outputStream, "pin2StopEventType", MOTOR_DEBUG_KEY_COLUMN_LENGTH);
    appendDualHBridgePinStopEventTypeAsString(outputStream, dualHBridge->pin2StopEventType);
    appendEndOfTableColumn(outputStream, MOTOR_DEBUG_LAST_COLUMN_LENGTH);

    appendTableHeaderSeparatorLine(outputStream);
}

