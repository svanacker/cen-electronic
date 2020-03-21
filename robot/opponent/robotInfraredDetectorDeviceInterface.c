#include "robotInfraredDetectorDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceRobotInfraredDetectorGetName() {
    return "RobotInfraredDetector";
}

unsigned int deviceRobotInfraredDetectorGetSoftwareRevision() {
    return 1;
}

int deviceRobotInfraredDetectorGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // command to ask
    if (commandHeader == COMMAND_INFRARED_DETECTOR_DETECTION) {
        if (fillDeviceArgumentList) {
            setFunction("infraredDetector", 1, 1);
            setArgumentUnsignedHex2(0, "backward/forward");
            setResultUnsignedHex2(0, "True/False");
        }
        return commandLengthValueForMode(mode, 2, 2);
    } else if (commandHeader == DETECTOR_ENABLE_NOTIFICATION_COMMAND) {
        if (fillDeviceArgumentList) {
            setFunction("enable Notification", 1, 0);
            setArgumentUnsignedHex2(0, "backward/forward");
        }
        return commandLengthValueForMode(mode, 2, 0);
    } else if (commandHeader == DETECTOR_DISABLE_NOTIFICATION_COMMAND) {
        if (fillDeviceArgumentList) {
            setFunction("disable Notification", 1, 0);
            setArgumentUnsignedHex2(0, "backward/forward");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }// Notification !
    else if (commandHeader == NOTIFY_INFRARED_DETECTOR_DETECTION) {
        if (fillDeviceArgumentList) {
            setFunction("notifyInfraredDetector", 0, 1);
            setResultUnsignedHex2(0, "backward/forward");
        }
        // TODO : Notification does not work like this
        return commandLengthValueForMode(mode, 0, 2);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceRobotInfraredDetectorGetName,
    .deviceHeader = ROBOT_INFRARED_DETECTOR_DEVICE_HEADER,
    .deviceGetInterface = &deviceRobotInfraredDetectorGetInterface
};

DeviceInterface* getRobotInfraredDetectorDeviceInterface() {
    return &deviceInterface;
}
