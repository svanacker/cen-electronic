#include <stdbool.h>

#include "pcDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceDebug.h"
#include "../../device/deviceConstants.h"

const char* devicePcGetName(void) {
    return "pc";
}

int devicePcGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // Pipe List
    if (commandHeader == COMMAND_PIPE_LIST) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("pipe List Table");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_LOAD_COMMAND_FILE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Load Command File");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = PC_DEVICE_HEADER,
    .deviceGetName = &devicePcGetName,
    .deviceGetInterface = &devicePcGetInterface
};

DeviceInterface* getPcDeviceInterface(void) {
    return &deviceInterface;
}
