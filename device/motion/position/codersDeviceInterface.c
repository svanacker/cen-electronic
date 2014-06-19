#include "codersDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"

const char* getCodersDeviceName(void) {
    return "Hctl Coders";
}

int deviceCodersGetInterface(char commandHeader, int mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_CLEAR_CODERS) {
        // Same INPUT / OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("clrCoders");
        }
        return 0;
    } else if (commandHeader == COMMAND_GET_WHEEL_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("codersVal", 0, 3);
            setArgument(0, DEVICE_ARG_UNSIGNED_HEX_8, "left");
            setArgumentSeparator(1);
            setArgument(2, DEVICE_ARG_UNSIGNED_HEX_8, "right");
        }
        return commandLengthValueForMode(mode, 0, 17);
    } else if (commandHeader == COMMAND_DEBUG_GET_WHEEL_POSITION) {
        // Same INPUT / OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("dbgCodersVal");
        }
        return 0;
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = CODERS_DEVICE_HEADER,
    .deviceGetName = &getCodersDeviceName,
    .deviceGetInterface = &deviceCodersGetInterface
};

DeviceInterface* getCodersDeviceInterface() {
    return &deviceInterface;
}
