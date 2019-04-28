#include "tofDeviceInterface.h"

#include <stdbool.h>

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceTofGetName(void) {
    return "tof";
}

int deviceTofGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_TOF_GET_DISTANCE) {
        if (fillDeviceArgumentList) {
            setFunction("TOF Get Distance", 1, 1);
            setArgumentUnsignedHex2(0, "Tof Index");
            setResultUnsignedHex4(0, "distance (mm)");
        }
        return commandLengthValueForMode(mode, 2, 4);
    }
    else if (commandHeader == COMMAND_TOF_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("TOF Debug List");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceTofGetName,
    .deviceHeader = TOF_DEVICE_HEADER,
    .deviceGetInterface = &deviceTofGetInterface
};

DeviceInterface* getTofDeviceInterface() {
    return &deviceInterface;
}
