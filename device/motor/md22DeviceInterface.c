#include <stdbool.h>

#include "md22DeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getMD22MotorDeviceName(void) {
    return "MD22_MOTOR";
}

int deviceMD22GetInterface(char header, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (header == COMMAND_MD22_MOVE) {
        if (fillDeviceArgumentList) {
            setFunction("runMotor", 2, 0);
            setArgumentSignedHex2(0, "left");
            setArgumentSignedHex2(1, "right");
        }
        return commandLengthValueForMode(mode, 4, 0);
    } else if (header == COMMAND_MD22_READ_VALUE) {
        if (fillDeviceArgumentList) {
            setFunction("readMotorValue", 0, 2);
            setResultSignedHex2(0, "left");
            setResultSignedHex2(1, "right");
        }
        return commandLengthValueForMode(mode, 0, 4);
    } else if (header == COMMAND_MD22_STOP) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("stopMotor");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = MD22_DEVICE_HEADER,
    .deviceGetName = &getMD22MotorDeviceName,
    .deviceGetInterface = &deviceMD22GetInterface
};

DeviceInterface* getMD22DeviceInterface(void) {
    return &deviceInterface;
}
