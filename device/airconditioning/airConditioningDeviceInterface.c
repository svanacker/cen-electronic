#include "airConditioningDeviceInterface.h"

#include <stdlib.h>

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceAirConditioningGetName(void) {
    return "AirConditioningDevice";
}

int deviceAirConditioningGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (AIR_CONDITIONING_COMMAND_WRITE == commandHeader) {
        if (fillDeviceArgumentList) {
            setFunction("Write", 1, 0);
            setArgumentUnsignedHex2(0, "powerState");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    else if (AIR_CONDITIONING_COMMAND_ON == commandHeader) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("On");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (AIR_CONDITIONING_COMMAND_OFF == commandHeader) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Off");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = AIR_CONDITIONING_DEVICE_HEADER,
    .deviceGetName = &deviceAirConditioningGetName,
    .deviceGetInterface = &deviceAirConditioningGetInterface
};

DeviceInterface* getAirConditioningDeviceInterface() {
    return &deviceInterface;
}
