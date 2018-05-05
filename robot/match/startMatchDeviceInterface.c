#include "startMatchDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getStartMatchDeviceName(void) {
    return "StartMatchDevice";
}

int deviceStartMatchGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_MATCH_IS_STARTED) {
        if (fillDeviceArgumentList) {
            setFunction("isStarted", 0, 1);
            setResultUnsignedHex2(0, "value");
        }
        return commandLengthValueForMode(mode, 0, 2);
    }
    else if (commandHeader == COMMAND_MATCH_SET_STARTED) {
        if (fillDeviceArgumentList) {
            setFunction("setStarted", 1, 0);
            setArgumentUnsignedHex2(0, "value");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &getStartMatchDeviceName,
    .deviceHeader = START_MATCH_DEVICE_HEADER,
    .deviceGetInterface = &deviceStartMatchGetInterface
};

DeviceInterface* getStartMatchDeviceInterface(void) {
    return &deviceInterface;
}
