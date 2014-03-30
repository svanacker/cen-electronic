#include "robotSonarDetectorDeviceInterface.h"

#include "../../device/deviceInterface.h"

const char* deviceRobotSonarDetectorGetName(void) {
    return "robotSonarDetector";
}

unsigned int deviceRobotSonarDetectorGetSoftwareRevision(void) {
    return 1;
}

int deviceRobotSonarDetectorGetInterface(char header, int mode, bool fillDeviceArgumentList) {
    if (header == COMMAND_SET_SONAR_STATUS) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("setSonarStatus", 1);
				setArgumentUnsignedHex2(0, "false(00)/true(01)");
            }
            return 2;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("setSonarStatus");
            }
            return 0;
        }
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceRobotSonarDetectorGetName,
//    .deviceGetSoftwareRevision = &deviceRobotSonarDetectorGetSoftwareRevision,
    .deviceGetInterface = &deviceRobotSonarDetectorGetInterface
};

DeviceInterface* getRobotSonarDetectorDeviceInterface() {
    return &deviceInterface;
}
