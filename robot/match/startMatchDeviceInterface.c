#include "startMatchDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getStartMatchDeviceName(void) {
    return "StartMatchDevice";
}

int deviceStartMatchGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_STEP_BY_STEP) {
        // same input / output
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("stepByStep");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_START_MATCH_GET_INITIAL_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("getInitialPosition", 1, 7);
            setArgumentUnsignedHex2(0, "side");
            setResultUnsignedHex2(0, "side");
            setResultSeparator(1);
            setResultUnsignedHex4(2, "x (mm)");
            setResultSeparator(3);
            setResultUnsignedHex4(4, "y (mm)");
            setResultSeparator(5);
            setResultUnsignedHex4(6, "angle (mm)");
        }
        return commandLengthValueForMode(mode, 2, 17);
    }
    else if (commandHeader == COMMAND_START_MATCH_SET_INITIAL_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("setInitialPosition", 7, 0);
            setArgumentUnsignedHex2(0, "side");
            setArgumentSeparator(1);
            setArgumentUnsignedHex4(2, "x (mm)");
            setArgumentSeparator(3);
            setArgumentUnsignedHex4(4, "y (mm)");
            setArgumentSeparator(5);
            setArgumentUnsignedHex4(6, "angle (mm)");
        }
        return commandLengthValueForMode(mode, 17, 0);
    }

    /*
    if (mode == DEVICE_MODE_OUTPUT) {
            if (header == COMMAND_NOTIFY_MATCH_STARTED) {
                    if (fillDeviceArgumentList) {
                            deviceArgumentList->functionName = "notifyMatchStarted";
                            deviceArgumentList->size = 1;
                            deviceArgumentList->args[0].type = DEVICE_ARG_UNSIGNED_CHAR_3;
                            deviceArgumentList->args[0].name = "XyY";
                    }
                    return commandLengthValueForMode(mode, 0, 0);
            }
    }
     */
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
