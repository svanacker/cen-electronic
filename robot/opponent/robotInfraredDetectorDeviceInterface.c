#include "robotInfraredDetectorDeviceInterface.h"

#include "../../device/deviceInterface.h"

const char* deviceRobotInfraredDetectorGetName() {
    return "RobotInfraredDetector";
}

unsigned int deviceRobotInfraredDetectorGetSoftwareRevision() {
    return 1;
}

int deviceRobotInfraredDetectorGetInterface(char header, int mode, BOOL fillDeviceArgumentList ) {
	if (header == COMMAND_INFRARED_DETECTOR_DETECTION) {
	    if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("infraredDetector");
            }
            return 0;
	    } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunction("infraredDetector", 1);
				setArgumentUnsignedHex2(0, "True/False");
            }
            return 2;
	    }
	}
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceRobotInfraredDetectorGetName,
    .deviceGetInterface = &deviceRobotInfraredDetectorGetInterface
};

DeviceInterface* getRobotInfraredDetectorDeviceInterface() {
    return &deviceInterface;
}
