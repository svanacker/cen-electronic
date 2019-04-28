#include <stdbool.h>

#include "codersDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* getCodersDeviceName(void) {
    return "Hctl Coders";
}

int deviceCodersGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_CLEAR_CODERS) {
        // Same INPUT / OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("clear Coders");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_GET_WHEEL_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("coders Value", 0, 3);
            setResult(0, DEVICE_ARG_UNSIGNED_HEX_8, "left (pulse)");
            setResultSeparator(1);
            setResult(2, DEVICE_ARG_UNSIGNED_HEX_8, "right (pulse)");
        }
        return commandLengthValueForMode(mode, 0, 17);
    } else if (commandHeader == COMMAND_DEBUG_GET_WHEEL_POSITION) {
        // Same INPUT / OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("debug Coders Value");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_DEBUG_ACQUIRE_SAMPLE_WHEEL_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("acquire Sample for xx milliSec", 3, 0);
            setArgumentUnsignedHex4(0, "time in 1/1000 sec");
            setArgumentSeparator(1);
            setArgumentUnsignedHex4(2, "iteration count (max 1000)");
        }
        return commandLengthValueForMode(mode, 9, 0);
    } 
    else if (commandHeader == COMMAND_DEBUG_PRINT_SAMPLE_WHEEL_POSITION) {
        // Same INPUT / OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("print the sample previouly recorded");
        }
        return commandLengthValueForMode(mode, 0, 0);
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
