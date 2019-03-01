#include <stdbool.h>

#include "servoDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceServoGetName(void) {
    return "servo";
}

int deviceServoGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // WRITE FUNCTIONS
    if (commandHeader == SERVO_COMMAND_WRITE) {
        if (fillDeviceArgumentList) {
            setFunction("updateServoAllParams", 5, 0);
            setArgumentUnsignedHex2(0, "ServoIdx");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "speed");
            setArgumentSeparator(3);
            setArgumentUnsignedHex4(4, "value");
        }
        return commandLengthValueForMode(mode, 10, 0);
    }
    else if (commandHeader == SERVO_COMMAND_WRITE_COMPACT) {
        if (fillDeviceArgumentList) {
            setFunction("updateAllServoCompact", 1, 0);
            setArgumentUnsignedHex4(0, "value");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
    else if (commandHeader == SERVO_COMMAND_ENABLE_DISABLE) {
        if (fillDeviceArgumentList) {
            setFunction("enable/disab. Servo", 3, 0);
            setArgumentUnsignedHex2(0, "ServoIdx");
            setArgumentSeparator(1);
            setArgumentUnsignedChar1(2, "enabl.(1) / dis.(0)");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
    else if (commandHeader == SERVO_COMMAND_ENABLE_DISABLE_ALL) {
        if (fillDeviceArgumentList) {
            setFunction("enable/disab. All Servo", 1, 0);
            setArgumentUnsignedChar1(0, "enabl.(1) / dis.(0)");
        }
        return commandLengthValueForMode(mode, 1, 0);
    }
    // READ_FUNCTIONS
    else if (commandHeader == SERVO_COMMAND_GET_COUNT) {
        if (fillDeviceArgumentList) {
            setFunction("servoCount", 0, 1);
            setResultUnsignedHex2(0, "ServoCount");

        }
        return commandLengthValueForMode(mode, 0, 2);
    }
    else if (commandHeader == SERVO_COMMAND_READ) {
        if (fillDeviceArgumentList) {
            setFunction("servoRead", 1, 9);
            setArgumentUnsignedHex2(0, "ServoIdx");
            setResultUnsignedHex2(0, "ServoIdx");
            setResultSeparator(1);
            setResultUnsignedChar1(2, "Enabled (1) / Dis.(0)");
            setResultSeparator(3);
            setResultUnsignedHex2(4, "Speed");
            setResultSeparator(5);
            setResultUnsignedHex4(6, "Current Position");
            setResultSeparator(7);
            setResultUnsignedHex4(8, "Target Position");

        }
        return commandLengthValueForMode(mode, 2, 17);
    }
    else if (commandHeader == SERVO_COMMAND_READ_SPEED) {
        if (fillDeviceArgumentList) {
            setFunction("servoReadSpeed", 1, 1);
            setArgumentUnsignedHex2(0, "ServoIdx");
            setResultUnsignedHex2(0, "Speed");
        }
        return commandLengthValueForMode(mode, 2, 2);
    }
    else if (commandHeader == SERVO_COMMAND_READ_CURRENT_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("servoReadCurrentPosition", 1, 1);
            setArgumentUnsignedHex2(0, "ServoIdx");
            setResultUnsignedHex4(0, "Current Position");
        }
        return commandLengthValueForMode(mode, 2, 4);
    }
    else if (commandHeader == SERVO_COMMAND_READ_TARGET_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("servoReadTargetPosition", 1, 1);
            setArgumentUnsignedHex2(0, "ServoIdx");
            setResultUnsignedHex4(0, "Target Position");
        }
        return commandLengthValueForMode(mode, 2, 4);
    }
    // DEBUG FUNCTIONS
    else if (commandHeader == SERVO_COMMAND_TEST) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("servoTestAlls");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // DEBUG
    else if (commandHeader == SERVO_COMMAND_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("servoDebugAlls");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = SERVO_DEVICE_HEADER,
    .deviceGetName = &deviceServoGetName,
    .deviceGetInterface = &deviceServoGetInterface
};

DeviceInterface* getServoDeviceInterface(void) {
    return &deviceInterface;
}
