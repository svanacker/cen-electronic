#include "serialDebugDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceSerialDebugGetName(void) {
    return "serialDebug";
}

int deviceSerialDebugGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_SERIAL_INPUT_BUFFERS) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("showSerialInputBuffers");
        }
        return 0;
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
