#include <stdbool.h>

#include "tofDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceTofGetName() {
    return "tof";
}

int deviceTofGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_TOF_GET_DISTANCE) {
        if (fillDeviceArgumentList) {
            setFunction("TOF Get Distance", 0, 1);
            setResultUnsignedHex4(0, "distance (mm)");
        }
        return commandLengthValueForMode(mode, 0, 4);
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
