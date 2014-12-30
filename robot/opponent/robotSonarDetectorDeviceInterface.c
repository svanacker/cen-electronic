#include "robotSonarDetectorDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceRobotSonarDetectorGetName(void) {
    return "robotSonarDetector";
}

unsigned int deviceRobotSonarDetectorGetSoftwareRevision(void) {
    return 1;
}

int deviceRobotSonarDetectorGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_SET_SONAR_STATUS) {
        if (fillDeviceArgumentList) {
            setFunction("setSonarStatus", 1, 0);
            setArgumentUnsignedHex2(0, "false(00)/true(01)");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceRobotSonarDetectorGetName,
    .deviceHeader = ROBOT_SONAR_DETECTOR_DEVICE_HEADER,
//    .deviceGetSoftwareRevision = &deviceRobotSonarDetectorGetSoftwareRevision,
    .deviceGetInterface = &deviceRobotSonarDetectorGetInterface
};

DeviceInterface* getRobotSonarDetectorDeviceInterface() {
    return &deviceInterface;
}
