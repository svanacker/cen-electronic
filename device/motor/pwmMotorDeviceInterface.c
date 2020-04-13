#include <stdbool.h>

#include "pwmMotorDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getPwmMotorDeviceName(void) {
    return "PWM_MOTOR";
}

int deviceMotorGetInterface(unsigned char header, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (header == COMMAND_MOVE_MOTOR) {
        if (fillDeviceArgumentList) {
            setFunction("runMotor", 2, 0);
            setArgumentSignedHex2(0, "motor 1 (left)");
            setArgumentSignedHex2(1, "motor 2 (right)");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
    else if (header == COMMAND_MOVE_MOTOR_LEFT) {
        if (fillDeviceArgumentList) {
            setFunction("Motor Left only", 1, 0);
            setArgumentSignedHex2(0, "motor 1 (left)");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    else if (header == COMMAND_MOVE_MOTOR_RIGHT) {
        if (fillDeviceArgumentList) {
            setFunction("Motor Right only", 1, 0);
            setArgumentSignedHex2(0, "motor 2 (right)");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    else if (header == COMMAND_SET_PIN_USAGE_MOTOR) {
        if (fillDeviceArgumentList) {
            setFunction("Set Motor Pin Usages", 7, 0);
            setArgumentUnsignedHex2(0, "Pin 1 Usage Type");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "Pin 2 Usage Type");
            setArgumentSeparator(3);
            setArgumentUnsignedHex2(4, "Pin 1 Stop Type");
            setArgumentSeparator(5);
            setArgumentUnsignedHex2(6, "Pin 2 Stop Type");
        }
        return commandLengthValueForMode(mode, 11, 0);
    } else if (header == COMMAND_READ_MOTOR_VALUE) {
        if (fillDeviceArgumentList) {
            setFunction("readMotorValue", 0, 2);
            setResultSignedHex2(0, "motor 1 (left)");
            setResultSignedHex2(1, "motor 2 (right)");
        }
        return commandLengthValueForMode(mode, 0, 4);
    } else if (header == COMMAND_STOP_MOTOR) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("stopMotor");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (header == COMMAND_SMALL_TEST_MOTOR) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("smallTestMotor");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (header == COMMAND_NORMAL_TEST_MOTOR) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("normalTestMotor");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (header == COMMAND_DEBUG_MOTOR) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("debug Motor");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // NOTIFICATION
    if (DEVICE_MODE_NOTIFY == mode) {
        if (header == NOTIFY_PIN_CHANGED) {
            if (fillDeviceArgumentList) {
                setNotification("Motor Pin Changed", 3);
                setArgumentUnsignedChar1(0, "pin 1");
                setArgumentSeparator(1);
                setArgumentUnsignedChar1(2, "pin 2");
            }
            return 3;
        }
    }

    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = MOTOR_DEVICE_HEADER,
    .deviceGetName = &getPwmMotorDeviceName,
    .deviceGetInterface = &deviceMotorGetInterface
};

DeviceInterface* getMotorDeviceInterface() {
    return &deviceInterface;
}
