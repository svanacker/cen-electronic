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

int deviceEndMatchDetectorGetInterface(unsigned char header, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // DEBUG
    if (header == COMMAND_END_MATCH_DETECTOR_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("End Match Debug");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (header == COMMAND_SHOW_MATCH_ENDED) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("show Match End");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// Getters
    else if (header == COMMAND_GET_TIME_LEFT) {
        if (fillDeviceArgumentList) {
            setFunction("get Time Left", 0, 1);
            setResultUnsignedHex2(0, "timeLeft");
        }
        return commandLengthValueForMode(mode, 0, 2);
    }// Setters
    else if (header == COMMAND_SET_CURRENT_TIME_IN_SECOND) {
        if (fillDeviceArgumentList) {
            setFunction("set Current Time", 1, 0);
            setArgumentUnsignedHex2(0, "new current Time (second)");
        }
        return commandLengthValueForMode(mode, 2, 0);
    } else if (header == COMMAND_SET_MATCH_DURATION) {
        if (fillDeviceArgumentList) {
            setFunction("set Match Duration", 1, 0);
            setArgumentUnsignedHex2(0, "new match Duration (second)");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }// Notifications
    else if (mode == DEVICE_MODE_OUTPUT) {
        if (header == COMMAND_SHOW_MATCH_ENDED) {
            if (fillDeviceArgumentList) {
                setFunctionNoArgumentAndNoResult("notify Match End");
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
