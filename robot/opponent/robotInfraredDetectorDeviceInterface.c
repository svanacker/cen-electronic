#include "robotInfraredDetectorDeviceInterface.h"

#include "../../device/deviceInterface.h"

const char* deviceRobotInfraredDetectorGetName() {
    return "RobotInfraredDetector";
}

unsigned int deviceRobotInfraredDetectorGetSoftwareRevision() {
    return 1;
}

int deviceRobotInfraredDetectorGetInterface(char header, int mode, bool fillDeviceArgumentList ) {
    // command to ask
    if (header == COMMAND_INFRARED_DETECTOR_DETECTION) {
        if (fillDeviceArgumentList) {
            setFunction("infraredDetector", 1, 1);
            setArgumentUnsignedHex2(0, "backward/forward");
            setResultUnsignedHex2(0, "True/False");
        }
        return commandLengthValueForMode(mode, 2, 2);
    }
    // Notification !
    else if (header == NOTIFY_INFRARED_DETECTOR_DETECTION) {
        if (fillDeviceArgumentList) {
            setFunction("notifyInfraredDetector", 0, 1);
            setResultUnsignedHex2(0, "backward/forward");
        }
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
