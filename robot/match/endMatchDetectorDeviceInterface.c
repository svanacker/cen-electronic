#include "endMatchDetectorDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getEndMatchDetectorDeviceName(void) {
    return "EndMatchDetector";
}

unsigned int getEndMatchDetectorSoftwareRevision(void) {
    return 1;
}

int deviceEndMatchDetectorGetInterface(char header, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (header == COMMAND_GET_TIME_LEFT) {
        if (fillDeviceArgumentList) {
            setFunction("getTimeLeft", 0, 1);
            setResultUnsignedHex2(0, "timeLeft");
        }
        return commandLengthValueForMode(mode, 0, 2);
    }
    else if (mode == DEVICE_MODE_OUTPUT) {
        if (header == COMMAND_NOTIFY_MATCH_ENDED) {
            if (fillDeviceArgumentList) {
                setFunctionNoArgumentAndNoResult("notifyMatchEnd");
            }
            return commandLengthValueForMode(mode, 0, 0);
        }
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &getEndMatchDetectorDeviceName,
    .deviceHeader = END_MATCH_DETECTOR_DEVICE_HEADER,
//    .deviceGetSoftwareRevision = &getEndMatchDetectorSoftwareRevision,
    .deviceGetInterface = &deviceEndMatchDetectorGetInterface
};

DeviceInterface* getEndMatchDetectorDeviceInterface(void) {
    return &deviceInterface;
}
