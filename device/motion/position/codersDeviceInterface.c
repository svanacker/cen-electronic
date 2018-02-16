#include <stdbool.h>

#include "codersDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* getCodersDeviceName(void) {
    return "Hctl Coders";
}

int deviceCodersGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_CLEAR_CODERS) {
        // Same INPUT / OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("clrCoders");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_GET_WHEEL_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("codersVal", 0, 3);
            setResult(0, DEVICE_ARG_UNSIGNED_HEX_8, "left");
            setResultSeparator(1);
            setResult(2, DEVICE_ARG_UNSIGNED_HEX_8, "right");
        }
        return commandLengthValueForMode(mode, 0, 17);
    } else if (commandHeader == COMMAND_DEBUG_GET_WHEEL_POSITION) {
        // Same INPUT / OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("dbgCodersVal");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_DEBUG_TIMER_GET_WHEEL_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("debugTimerCodersVal", 3, 0);
            setArgument(0, DEVICE_ARG_UNSIGNED_HEX_2, "time in 1/10 sec");
			setArgumentSeparator(1);
			setArgument(2, DEVICE_ARG_UNSIGNED_HEX_2, "iteration count");
        }
        return commandLengthValueForMode(mode, 0, 5);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = CODERS_DEVICE_HEADER,
    .deviceGetName = &getCodersDeviceName,
    .deviceGetInterface = &deviceCodersGetInterface
};

DeviceInterface* getCodersDeviceInterface(void) {
    return &deviceInterface;
}
