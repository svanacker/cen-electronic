#include <stdbool.h>

#include "serialDebugDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceSerialDebugGetName(void) {
    return "serialDebug";
}

int deviceSerialDebugGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_SERIAL_INPUT_ALL_BUFFER) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("showSerialInputAllBuffer");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_SERIAL_INPUT_BUFFER) {
        if (fillDeviceArgumentList) {
            setFunction("showSerialInputBuffer", 1, 0);
            setArgumentUnsignedHex2(0, "serial Index");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    else if (commandHeader == COMMAND_SERIAL_CLEAR_INPUT_BUFFER) {
        if (fillDeviceArgumentList) {
            setFunction("clearSerialInputBuffer", 1, 0);
            setArgumentUnsignedHex2(0, "serial Index");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceSerialDebugGetName,
    .deviceHeader = SERIAL_DEBUG_DEVICE_HEADER,
    .deviceGetInterface = &deviceSerialDebugGetInterface
};

DeviceInterface* getSerialDebugDeviceInterface(void) {
    return &deviceInterface;
}
