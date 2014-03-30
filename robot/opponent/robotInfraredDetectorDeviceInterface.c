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
	    if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("infraredDetector", 1);
				setArgumentUnsignedHex2(0, "backward/forward");
            }
            return 2;
	    } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunction("infraredDetector", 1);
				setArgumentUnsignedHex2(0, "True/False");
            }
            return 2;
	    }
	}
	// Notification !
	else if (header == NOTIFY_INFRARED_DETECTOR_DETECTION) {
	    if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunction("notifyInfraredDetector", 1);
				setArgumentUnsignedHex2(0, "backward/forward");
            }
            return 2;
		// Input Mode is not used (notification)
	    } else if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("notifyInfraredDetector");
            }
            return 0;
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
