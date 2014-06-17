#include "endMatchDetectorDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"

const char* getEndMatchDetectorDeviceName() {
    return "EndMatchDetector";
}

unsigned int getEndMatchDetectorSoftwareRevision() {
    return 1;
}

int deviceEndMatchDetectorGetInterface(char header, int mode,
        bool fillDeviceArgumentList) {
    if (mode == DEVICE_MODE_OUTPUT) {
        if (header == COMMAND_NOTIFY_MATCH_ENDED) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgumentAndNoResult("notifyMatchEnd");
            }
            return 0;
        }
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &getEndMatchDetectorDeviceName,
//    .deviceGetSoftwareRevision = &getEndMatchDetectorSoftwareRevision,
    .deviceGetInterface = &deviceEndMatchDetectorGetInterface
};

DeviceInterface* getEndMatchDetectorDeviceInterface() {
    return &deviceInterface;
}
