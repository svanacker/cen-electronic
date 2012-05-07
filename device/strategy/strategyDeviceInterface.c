#include "strategyDeviceInterface.h"

#include "../../common/commons.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"

const char* getStrategyDeviceName(void) {
    return "STRATEGY";
}

unsigned int getStrategyVersion(void) {
    return 1;
}

int deviceStrategyGetInterface(char header, int mode, BOOL fillDeviceArgumentList) {
    if (header == COMMAND_SET_OPPONENT_ROBOT_POSITION) {
		if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("setOpponentRobotPos", 3);
				setArgumentUnsignedHex4(0, "x (mm)");
				setArgumentSeparator(1);
				setArgumentUnsignedHex4(2, "y (mm)");
            }
            return 9;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("setOpponentRobotPos");
            }
            return 0;
        }
	}
	else if (header == COMMAND_SET_CONFIG) {
		if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("setConfig", 1);
				setArgumentUnsignedHex4(0, "config");
            }
            return 4;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("setConfig");
            }
            return 0;
        }
	}
	return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &getStrategyDeviceName,
//    .deviceGetSoftwareRevision = &getStrategyVersion,
    .deviceGetInterface = &deviceStrategyGetInterface
};

DeviceInterface* getStrategyDeviceInterface() {
    return &deviceInterface;
}
