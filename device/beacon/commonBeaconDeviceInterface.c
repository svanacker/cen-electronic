#include "commonBeaconDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* commonBeaconDeviceGetName() {
    return "commonBeacon";
}

int commonBeaconDeviceGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // Redirection
    if (commandHeader == COMMAND_REDIRECT_TO_JENNIC) {
        // same output / input
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("redirectToJennic");
        }
        return 0;
    }
    else if (commandHeader == COMMAND_LOCAL_LIGHT) {
        if (fillDeviceArgumentList) {
            setFunction("localLight", 1, 2);
            setArgumentUnsignedHex2(2, "on/off");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    else if (commandHeader == COMMAND_SHOW_DATA_FROM_JENNIC) {
        // both input/output
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("showDataFromJennic");
        }
        return 0;
    }
    else if (commandHeader == COMMAND_RESET_JENNIC) {
        // both input/output
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("resetJennic");
        }
        return 0;
    }

    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = COMMON_BEACON_DEVICE_HEADER,
    .deviceGetName = &commonBeaconDeviceGetName,
    .deviceGetInterface = &commonBeaconDeviceGetInterface
};

DeviceInterface* getCommonBeaconDeviceInterface() {
    return &deviceInterface;
}
