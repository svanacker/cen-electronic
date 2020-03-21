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
    } else if (commandHeader == COMMAND_TOF_LIST_CONFIG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("TOF List Config");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_TOF_LIST_NETWORK) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("TOF List Network");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_TOF_LIST_DETECTED) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("TOF List Detection");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_TOF_BEEP_ON) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("TOF Beep On");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_TOF_BEEP_OFF) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("TOF Beep Off");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_TOF_SEARCH_IF_COLLIDING) {
        if (fillDeviceArgumentList) {
            setFunction("Search If Colliding for x secs", 3, 0);
            setArgumentUnsignedHex2(0, "tofIndex, FF if we check all");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "Analysis length (seconds)");
        }
        return commandLengthValueForMode(mode, 5, 0);
    } else if (commandHeader == COMMAND_TOF_RESTART) {
        if (fillDeviceArgumentList) {
            setFunction("TOF Restart", 1, 1);
            setArgumentUnsignedHex2(0, "Tof Index");
            setResultUnsignedChar1(0, "0 = KO, 1 = Success");
        }
        return commandLengthValueForMode(mode, 2, 1);
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
