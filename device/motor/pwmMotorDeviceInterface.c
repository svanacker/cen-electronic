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
            setArgumentSignedHex2(0, "left");
            setArgumentSignedHex2(1, "right");
        }
        return commandLengthValueForMode(mode, 4, 0);
    } else if (header == COMMAND_SET_PIN_USAGE_MOTOR) {
        if (fillDeviceArgumentList) {
            setFunction("Set Motor ++-Pin Usages", 4, 0);
            setArgumentSignedHex2(0, "Pin 1 Usage Type");
            setArgumentSeparator(1);
            setArgumentSignedHex2(2, "Pin 2 Stop Type");
            setArgumentSeparator(3);
            setArgumentSignedHex2(4, "Pin 1 Usage Type");
            setArgumentSeparator(5);
            setArgumentSignedHex2(6, "Pin 2 Stop Type");
        }
        return commandLengthValueForMode(mode, 11, 0);
    } else if (header == COMMAND_READ_MOTOR_VALUE) {
        if (fillDeviceArgumentList) {
            setFunction("readMotorValue", 0, 2);
            setResultSignedHex2(0, "left");
            setResultSignedHex2(1, "right");
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
