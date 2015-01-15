#include "startMatchDetectorDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getStartMatchDetectorDeviceName(void) {
    return "StartMatchDetector";
}

int deviceStartMatchDetectorGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_STEP_BY_STEP) {
        // same input / output
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("stepByStep");
        }
        return commandLengthValueForMode(mode, 0, 0);
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
    .deviceGetName = &getStartMatchDetectorDeviceName,
    .deviceHeader = START_MATCH_DETECTOR_DEVICE_HEADER,
    .deviceGetInterface = &deviceStartMatchDetectorGetInterface
};

DeviceInterface* getStartMatchDetectorDeviceInterface(void) {
    return &deviceInterface;
}
