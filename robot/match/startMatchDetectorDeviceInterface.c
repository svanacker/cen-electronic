#include "startMatchDetectorDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"

const char* getStartMatchDetectorDeviceName() {
    return "StartMatchDetector";
}

unsigned int getStartMatchDetectorSoftwareRevision() {
    return 1;
}

int deviceStartMatchDetectorGetInterface(char header, int mode,
        bool fillDeviceArgumentList) {
    if (header == COMMAND_STEP_BY_STEP) {
        // same input / output
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("stepByStep");
        }
        return 0;
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
                    return 0;
            }
    }
     */
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &getStartMatchDetectorDeviceName,
    .deviceHeader = START_MATCH_DETECTOR_DEVICE_HEADER,
//    .deviceGetSoftwareRevision = &getStartMatchDetectorSoftwareRevision,
    .deviceGetInterface = &deviceStartMatchDetectorGetInterface
};

DeviceInterface* getStartMatchDetectorDeviceInterface() {
    return &deviceInterface;
}
